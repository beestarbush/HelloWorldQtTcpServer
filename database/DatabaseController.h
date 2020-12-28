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

		bool open();
		bool close();

		bool queryReaderId(QString aMacAddress, uint32_t & aReaderId);
		bool queryCardId(QString aCardId, uint32_t & aCardUid);


	signals:

	private:
		QSqlDatabase mDatabase;
		ReaderDefinitionList mReaderDefinitionList;
		CardDefinitionList mCardDefinitionList;
		FileDefinitionList mFileDefinitionList;

		bool loadReaderDefinitions();
		bool loadCardDefinitions();
		bool loadFileDefinitions();

};

#endif // DATABASECONTROLLER_H
