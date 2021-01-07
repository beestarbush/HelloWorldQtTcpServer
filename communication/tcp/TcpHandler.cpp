#include "communication/tcp/TcpHandler.h"
#include <dataobjects/RfidReaderDataObject.h>
#include <ReaderDataCallback.h>
#include <QDebug>

TcpHandler::TcpHandler(unsigned short aId, QObject * aParent) :
	QThread(aParent),
	mParser(),
	mSocket(nullptr),
	mSocketDescriptor(aId),
	mIsConnected(false),
	mExpectKeepAliveAnswer(false),
	mNodeInfoData(new NodeInfoDataObject),
	mRfidReaderData(new RfidReaderDataObject),
	mCallback(nullptr)
{
	mParser.registerDataObject(MessageType::NODE_INFO_MESSAGE_TYPE, mNodeInfoData);
	mParser.registerDataObject(MessageType::RFID_READER_MESSAGE_TYPE, mRfidReaderData);
}

TcpHandler::~TcpHandler()
{
	delete mSocket;
	delete mNodeInfoData;
	delete mRfidReaderData;
	mCallback = nullptr;
}

void TcpHandler::run()
{
	qDebug() << "Thread started";

	mSocket = new QTcpSocket();
	mSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!mSocket->setSocketDescriptor(mSocketDescriptor))
	{
		emit error(mSocket->error());
		return;
	}

	// connect socket and signal
	// note - Qt::DirectConnection is used because it's multithreaded
	//        This makes the slot to be invoked immediately, when the signal is emitted.

	connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
	connect(mSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));

	// We'll have multiple clients, we want to know which is which
	qDebug() << mSocketDescriptor << " Client connected";
	setIsConnected(true);

	// make this thread a loop,
	// thread will stay alive so that signal/slot to function properly
	// not dropped out in the middle when thread dies

	exec();
}

void TcpHandler::registerReaderDataCallback(ReaderDataCallback * aCallback)
{
	mCallback = aCallback;
}

void TcpHandler::sendKeepAlive()
{
	if (mExpectKeepAliveAnswer)
	{
		if (mKeepAliveAnswerNotReceivedCount < 5)
		{
			qWarning() << mSocketDescriptor << " Keep-alive has not been answered (count: " << QString::number(mKeepAliveAnswerNotReceivedCount) << ")";
			mKeepAliveAnswerNotReceivedCount++;
		}
		else
		{
			qWarning() << mSocketDescriptor << " Connection is not alive, marking as disconnected.";
			disconnected();
		}
		return;
	}

	mExpectKeepAliveAnswer = true;
	mSocket->write("?", 1);
	mSocket->flush();
	mSocket->waitForBytesWritten();
}

bool TcpHandler::getIsConnected() const
{
	return mIsConnected;
}

void TcpHandler::setIsConnected(bool aIsConnected)
{
	if (mIsConnected != aIsConnected)
	{
		mIsConnected = aIsConnected;
		emit isConnectedChanged();
	}
}

int TcpHandler::getSocketDescriptor()
{
	return mSocketDescriptor;
}

void TcpHandler::readyRead()
{
	// get the information
	QByteArray lData = mSocket->readAll();

	qDebug() << mSocketDescriptor << " Data in: " << lData;

	// Handle keep alive messages.
	if (mExpectKeepAliveAnswer)
	{
		if (lData.toStdString().compare("!") == 0)
		{
			mExpectKeepAliveAnswer = false;
			mKeepAliveAnswerNotReceivedCount = 0;
			return;
		}
	}

	// Handle other messages.
	if (!mParser.parse(((uint8_t*)lData.data()), lData.count()))
	{
		qDebug() << "Unable to parse data.";
		mSocket->write("0", 1);
		mSocket->flush();
		mSocket->waitForBytesWritten();
		return;
	}

	mSocket->write("1", 1);
	mSocket->flush();
	mSocket->waitForBytesWritten();

	if (!mNodeInfoData->getMacAddressString().isEmpty() &&
		!mRfidReaderData->isCardIdEmpty())
	{
		mCallback->onReaderDataAvailable(mNodeInfoData->getMacAddressString(), mRfidReaderData->getCardIdString());
	}
}

void TcpHandler::disconnected()
{
	qDebug() << mSocketDescriptor << " Disconnected";
	setIsConnected(false);
}
