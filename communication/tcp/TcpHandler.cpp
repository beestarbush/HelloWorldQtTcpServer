#include "communication/tcp/TcpHandler.h"
#include <dataobjects/RfidReaderDataObject.h>
#include <QDebug>

TcpHandler::TcpHandler(unsigned short aId, QObject * aParent) :
	QThread(aParent),
	mParser(),
	mSocketDescriptor(aId),
	mIsConnected(false),
	mNodeInfoData(new NodeInfoDataObject),
	mRfidReaderData(new RfidReaderDataObject)
{
	mParser.registerDataObject(MessageType::NODE_INFO_MESSAGE_TYPE, mNodeInfoData);
	mParser.registerDataObject(MessageType::RFID_READER_MESSAGE_TYPE, mRfidReaderData);
}

void TcpHandler::run()
{
	qDebug() << "Thread started";

	mSocket = new QTcpSocket();

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

	// will write on server side window
	qDebug() << mSocketDescriptor << " Data in: " << lData;

	if (!mParser.parse(((uint8_t*)lData.data()), lData.count()))
	{
		qDebug() << "Unable to parse data.";
		mSocket->write("NACK");
		return;
	}

	mSocket->write("ACK");
}

void TcpHandler::disconnected()
{
	qDebug() << mSocketDescriptor << " Disconnected";

	mSocket->deleteLater();
	setIsConnected(false);
}


