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
	qDebug() << "closing database";
	mDatabase.close();
	QSqlDatabase::removeDatabase("connection");
}

bool ApplicationLogic::setup()
{
	// Open database.
	mDatabase = QSqlDatabase::addDatabase("QSQLITE", "connection");
	mDatabase.setDatabaseName("/home/bijstr/workspace/HelloTcpWorld/database.db");

	if (!mDatabase.open())
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

	QSqlQuery lSelectQuery(mDatabase);
	lSelectQuery.prepare("SELECT uid FROM ReaderDefinitions WHERE mac_address=:macaddress");
	lSelectQuery.bindValue(":macaddress", lMacAddress);
	if (!lSelectQuery.exec())
	{
		qDebug() << "Unable to execute query.";
		return;
	}
	if (!lSelectQuery.next())
	{
		qDebug() << "Unable to retrieve key from query.";
		return;
	}

	qDebug() << "Reader ID: " << lSelectQuery.value("uid").toString();
}
