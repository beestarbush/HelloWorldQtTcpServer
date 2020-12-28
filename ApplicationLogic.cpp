#include "ApplicationLogic.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QtSql>

ApplicationLogic::ApplicationLogic() :
	ReaderDataCallback(),
	mMacAddressesQueue(),
	mCardIdsQueue(),
	mMutex()
{
}

ApplicationLogic::~ApplicationLogic()
{
}

bool ApplicationLogic::setup()
{
	if (!mDatabaseController.open())
	{
		qDebug() << "Failed to open database.";
		return false;
	}

	// Check amount of readers.

	// Start processing data.
	connect(this, SIGNAL(processData()), this, SLOT(onProcessData()), Qt::ConnectionType::QueuedConnection);

	return true;
}

void ApplicationLogic::onReaderDataAvailable(QString aMacAddress, QString aCardId)
{
	QMutexLocker lLocker(&mMutex);
	mMacAddressesQueue.enqueue(aMacAddress);
	mCardIdsQueue.enqueue(aCardId);
	emit processData();
}

void ApplicationLogic::onProcessData()
{
	QMutexLocker lLocker(&mMutex);

	if (mMacAddressesQueue.size() <= 0 || mCardIdsQueue.size() <= 0)
	{
		return;
	}

	QString lMacAddress = mMacAddressesQueue.dequeue();
	QString lCardId = mCardIdsQueue.dequeue();
	qDebug() << "MAC: " << lMacAddress;
	qDebug() << "CID: " << lCardId;

	uint32_t lReaderId = 0;
	if (!mDatabaseController.queryReaderId(lMacAddress, lReaderId))
	{
		qDebug() << "Failed to query reader ID.";
		return;
	}

	uint32_t lCardUid = 0;
	if (!mDatabaseController.queryCardId(lCardId, lCardUid))
	{
		qDebug() << "Failed to query card UID.";
		return;
	}

	qDebug() << "Reader ID:" << lReaderId;
	qDebug() << "Card UID: " << lCardUid;
}
