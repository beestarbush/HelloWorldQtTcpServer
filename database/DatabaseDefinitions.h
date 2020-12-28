#ifndef DATABASEDEFINITIONS_H
#define DATABASEDEFINITIONS_H

#include <stdint.h>
#include <QString>
#include <vector>

typedef struct  {
	uint32_t mUid;
	QString mMacAddress;
	QString mDescription;
} ReaderDefinition;

typedef std::vector<ReaderDefinition> ReaderDefinitionList;

typedef struct  {
	uint32_t mUid;
	QString mCardId;
	QString mDescription;
} CardDefinition;

typedef std::vector<CardDefinition> CardDefinitionList;

typedef struct  {
	uint32_t mUid;
	uint32_t mCombinationId;
	QString mFilename;
} FileDefinition;

typedef std::vector<FileDefinition> FileDefinitionList;


#endif // DATABASEDEFINITIONS_H
