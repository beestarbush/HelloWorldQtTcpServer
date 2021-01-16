#include "DatabaseController.h"
#include <QSqlQuery>
#include <QDebug>

#define DATABASE_VERSION	(1)
//#define DATABASE_LOCATION	("/home/bijstr/workspace/HelloTcpWorld/database.db")
#define DATABASE_LOCATION	("/Users/NaomivanderVeen/Desktop/ProjectTafel/HelloWorldQtTcpServer/database.db")
//#define DATABASE_LOCATION	("/home/randy/Development/C++/HelloWorldQtTcpServer/database.db")


DatabaseController::DatabaseController(QObject *parent) :
	QObject(parent),
	mDatabase(),
	mVersionDefinitionList(),
	mReaderDefinitionList(),
	mCardDefinitionList(),
	mFileDefinitionList(),
	mCombinationMatrix()
{
}

bool DatabaseController::open()
{
	// Open database.
	mDatabase = QSqlDatabase::addDatabase("QSQLITE", "connection");
	mDatabase.setDatabaseName(DATABASE_LOCATION);

	if (!mDatabase.open())
	{
		qDebug() << "Failed to open database.";
		return false;
	}

	uint32_t lDatabaseVersion = 0;
	if (!loadVersionDefinitions() ||
		!getVersionByComponent("database", lDatabaseVersion))
	{
		return false;
	}

	if (lDatabaseVersion != DATABASE_VERSION)
	{
		qDebug() << "Incorrect database version.";
		return false;
	}

	return true;
}

bool DatabaseController::load()
{
	if (!loadReaderDefinitions() ||
		!loadCardDefinitions() ||
		!loadFileDefinitions() ||
		!loadCombinationMatrix())
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

	mDatabase.close();

	mDatabase = QSqlDatabase::database();
	QSqlDatabase::removeDatabase("connection");

	return true;
}

bool DatabaseController::getReaderIdByMacAddress(QString aMacAddress, uint32_t &aReaderId)
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

bool DatabaseController::getCardUidByCardId(QString aCardId, uint32_t &aCardUid)
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

bool DatabaseController::getVersionByComponent(QString aComponent, uint32_t & aVersion)
{
	for (auto lDefinition : mVersionDefinitionList)
	{
		if (lDefinition.mComponent.compare(aComponent) == 0)
		{
			aVersion = lDefinition.mVersion;
			return true;
		}
	}

	return false;
}

bool DatabaseController::getFilenameByCombinationId(uint32_t aCombinationId, QString & aFilename)
{
	for (auto lDefinition : mFileDefinitionList)
	{
		if (lDefinition.mCombinationId == aCombinationId)
		{
			aFilename = lDefinition.mFilename;
			return true;
		}
	}

	return false;
}

ReaderDefinitionList * DatabaseController::getReaderDefinitionList()
{
	return &mReaderDefinitionList;
}

CardDefinitionList * DatabaseController::getCardDefinitionList()
{
	return &mCardDefinitionList;
}

FileDefinitionList * DatabaseController::getFileDefinitionList()
{
	return &mFileDefinitionList;
}

CombinationMatrix * DatabaseController::getCombinationMatrix()
{
	return &mCombinationMatrix;
}

bool DatabaseController::loadVersionDefinitions()
{
	QSqlQuery lSelectQuery(mDatabase);
	lSelectQuery.prepare("SELECT uid, component, version FROM VersionDefinitions");
	if (!lSelectQuery.exec())
	{
		qDebug() << "Unable to execute query.";
		return false;
	}
	while (lSelectQuery.next())
	{
		VersionDefinition lDefinition = { lSelectQuery.value("uid").toUInt(),
										  lSelectQuery.value("component").toString(),
										  lSelectQuery.value("version").toUInt() };
		mVersionDefinitionList.push_back(lDefinition);
	}

	if (mVersionDefinitionList.empty())
	{
		qDebug() << "Failed to load VersionDefinitions from database.";
		return false;
	}

	return true;
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

bool DatabaseController::loadCombinationMatrix()
{
	QSqlQuery lSelectQuery(mDatabase);
	lSelectQuery.prepare("SELECT uid, combination_id, reader_uid, card_uid FROM CombinationMatrix");
	if (!lSelectQuery.exec())
	{
		qDebug() << "Unable to execute query.";
		return false;
	}
	while (lSelectQuery.next())
	{
		uint32_t lCombinationId = lSelectQuery.value("combination_id").toUInt();
		if (mCombinationMatrix.find(lCombinationId) == mCombinationMatrix.end())
		{
			mCombinationMatrix.insert(std::pair<uint32_t, std::vector<Combination>*>(lCombinationId, new std::vector<Combination>));
		}

		Combination lCombination =	 {  lSelectQuery.value("reader_uid").toUInt(),
										lSelectQuery.value("card_uid").toUInt() };
		mCombinationMatrix[lCombinationId]->push_back(lCombination);
	}

	if (mCombinationMatrix.empty())
	{
		qDebug() << "Failed to load CombinationMatrix from database.";
		return false;
	}

	return true;
}
