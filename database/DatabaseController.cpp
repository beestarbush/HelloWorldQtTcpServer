#include "DatabaseController.h"
#include <QSqlQuery>
#include <QDebug>

DatabaseController::DatabaseController(QObject *parent) : QObject(parent)
{

}

bool DatabaseController::open()
{
	// Open database.
	mDatabase = QSqlDatabase::addDatabase("QSQLITE", "connection");
	mDatabase.setDatabaseName("/home/randy/Development/C++/HelloWorldQtTcpServer/database.db");

	if (!mDatabase.open())
	{
		qDebug() << "Failed to open database.";
		return false;
	}

	if (!loadReaderDefinitions() ||
		!loadCardDefinitions() ||
		!loadFileDefinitions())
	{
		return false;
	}

	return true;
}

bool DatabaseController::close()
{
	if (!mDatabase.isOpen())
	{
		return false;
	}

	qDebug() << "closing database";
	mDatabase.close();
	QSqlDatabase::removeDatabase("connection");

	return true;
}

bool DatabaseController::queryReaderId(QString aMacAddress, uint32_t &aReaderId)
{
	for (auto lDefinition : mReaderDefinitionList)
	{
		if (lDefinition.mMacAddress.compare(aMacAddress) == 0)
		{
			aReaderId = lDefinition.mUid;
			return true;
		}
	}

	return false;
}

bool DatabaseController::queryCardId(QString aCardId, uint32_t &aCardUid)
{
	for (auto lDefinition : mCardDefinitionList)
	{
		if (lDefinition.mCardId.compare(aCardId) == 0)
		{
			aCardUid = lDefinition.mUid;
			return true;
		}
	}

	return false;
}

bool DatabaseController::loadReaderDefinitions()
{
	QSqlQuery lSelectQuery(mDatabase);
	lSelectQuery.prepare("SELECT uid, mac_address, description FROM ReaderDefinitions");
	if (!lSelectQuery.exec())
	{
		qDebug() << "Unable to execute query.";
		return false;
	}
	while (lSelectQuery.next())
	{
		ReaderDefinition lDefinition = { lSelectQuery.value("uid").toUInt(),
										 lSelectQuery.value("mac_address").toString(),
										 lSelectQuery.value("description").toString() };
		mReaderDefinitionList.push_back(lDefinition);
	}

	if (mReaderDefinitionList.empty())
	{
		qDebug() << "Failed to load ReaderDefinitions from database.";
		return false;
	}

	return true;
}

bool DatabaseController::loadCardDefinitions()
{
	QSqlQuery lSelectQuery(mDatabase);
	lSelectQuery.prepare("SELECT uid, card_id, description FROM CardDefinitions");
	if (!lSelectQuery.exec())
	{
		qDebug() << "Unable to execute query.";
		return false;
	}
	while (lSelectQuery.next())
	{
		CardDefinition lDefinition = { lSelectQuery.value("uid").toUInt(),
										 lSelectQuery.value("card_id").toString(),
										 lSelectQuery.value("description").toString() };
		mCardDefinitionList.push_back(lDefinition);
	}

	if (mCardDefinitionList.empty())
	{
		qDebug() << "Failed to load CardDefinitions from database.";
		return false;
	}

	return true;
}

bool DatabaseController::loadFileDefinitions()
{
	QSqlQuery lSelectQuery(mDatabase);
	lSelectQuery.prepare("SELECT uid, combination_id, filename FROM FileDefinitions");
	if (!lSelectQuery.exec())
	{
		qDebug() << "Unable to execute query.";
		return false;
	}
	while (lSelectQuery.next())
	{
		FileDefinition lDefinition = { lSelectQuery.value("uid").toUInt(),
										 lSelectQuery.value("combination_id").toUInt(),
										 lSelectQuery.value("filename").toString() };
		mFileDefinitionList.push_back(lDefinition);
	}

	if (mFileDefinitionList.empty())
	{
		qDebug() << "Failed to load FileDefinitions from database.";
		return false;
	}

	return true;
}
