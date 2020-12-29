#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <database/DatabaseDefinitions.h>

class DatabaseController : public QObject
{
	Q_OBJECT
	public:
		explicit DatabaseController(QObject *parent = nullptr);
		virtual ~DatabaseController() override = default;

		bool open();
		bool load();
		bool close();

		bool getReaderIdByMacAddress(QString aMacAddress, uint32_t & aReaderId);
		bool getCardUidByCardId(QString aCardId, uint32_t & aCardUid);
		bool getVersionByComponent(QString aComponent, uint32_t & aVersion);
		bool getFilenameByCombinationId(uint32_t aCombinationId, QString & aFilename);

		ReaderDefinitionList * getReaderDefinitionList();
		CardDefinitionList * getCardDefinitionList();
		FileDefinitionList * getFileDefinitionList();
		CombinationMatrix * getCombinationMatrix();

	private:
		QSqlDatabase mDatabase;
		VersionDefinitionList mVersionDefinitionList;
		ReaderDefinitionList mReaderDefinitionList;
		CardDefinitionList mCardDefinitionList;
		FileDefinitionList mFileDefinitionList;
		CombinationMatrix mCombinationMatrix;

		bool loadVersionDefinitions();
		bool loadReaderDefinitions();
		bool loadCardDefinitions();
		bool loadFileDefinitions();
		bool loadCombinationMatrix();

};

#endif // DATABASECONTROLLER_H
