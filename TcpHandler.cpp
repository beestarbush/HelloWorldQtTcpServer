#include "TcpHandler.h"
#include <RfidReaderMessage.h>
#include <QDebug>

TcpHandler::TcpHandler(unsigned short aId, QObject * aParent) :
	QThread(aParent),
	mParser(),
	mSocketDescriptor(aId),
	mIsConnected(false),
	mUid("<UNKNOWN>")
{

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
	mIsConnected = true;

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

QString TcpHandler::getUid() const
{
	return mUid;
}

void TcpHandler::setUid(const QString & aUid)
{
	if (mUid.compare(aUid) != 0)
	{
		mUid = aUid;
		emit uidChanged();
	}
}

void TcpHandler::readyRead()
{
	// get the information
	QByteArray Data = mSocket->readAll();

	// will write on server side window
	qDebug() << mSocketDescriptor << " Data in: " << Data;

	if (!mParser.parse(((uint8_t*)Data.data()), Data.count()))
	{
		qDebug() << "Error: cannot parse.";
		return;
	}

	mSocket->write(Data);
}

void TcpHandler::disconnected()
{
	qDebug() << mSocketDescriptor << " Disconnected";

	mSocket->deleteLater();
	mIsConnected = false;
}


