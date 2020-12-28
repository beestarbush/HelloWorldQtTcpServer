#include "communication/tcp/TcpController.h"
#include "communication/tcp/TcpHandler.h"
#include <QTimer>

#define TCP_PORT 2222

TcpController::TcpController(ReaderDataCallback * aCallback, QObject * aParent) :
	QTcpServer(aParent),
	mCheckConnectionTimer(new QTimer()),
	mConnectionList(),
	mCallback(aCallback)
{

}

void TcpController::start()
{
	connect(mCheckConnectionTimer, SIGNAL(timeout()), this, SLOT(checkConnections()));
	mCheckConnectionTimer->setInterval(1000);
	mCheckConnectionTimer->setSingleShot(false);
	mCheckConnectionTimer->start();

	if (!listen(QHostAddress::AnyIPv4, TCP_PORT))
	{
		qDebug() << "Could not start server!";
		return;
	}

	qDebug() << "Listening to port: " << TCP_PORT;
}

QVariantList TcpController::getConnectionList()
{
	return mConnectionList;
}

void TcpController::checkConnections()
{
	for(QVariantList::iterator lIterator = mConnectionList.begin(); lIterator != mConnectionList.end(); lIterator++)
	{
		auto lObject = qvariant_cast<QObject *>(*lIterator);
		auto lHandler = dynamic_cast<TcpHandler*>(lObject);
		Q_ASSERT(lHandler != nullptr);

		if (!lHandler->getIsConnected())
		{
			mConnectionList.erase(lIterator);
			emit connectionListChanged();
			return;
		}
	}
}

void TcpController::incomingConnection(qintptr aSocketDescriptor)
{
	qDebug() << aSocketDescriptor << " Connecting...";

	TcpHandler * lHandler = new TcpHandler(aSocketDescriptor, this);
	lHandler->registerReaderDataCallback(mCallback);
	connect(lHandler, SIGNAL(finished()), lHandler, SLOT(deleteLater()));
	lHandler->start();

	mConnectionList.push_back(QVariant::fromValue<TcpHandler*>(lHandler));
	emit connectionListChanged();
}
