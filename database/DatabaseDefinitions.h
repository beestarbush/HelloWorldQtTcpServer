#ifndef DATABASEDEFINITIONS_H
#define DATABASEDEFINITIONS_H

#include <stdint.h>
#include <QString>
#include <vector>
#include <map>

typedef struct  {
	uint32_t mUid;
	QString mComponent;
	uint32_t mVersion;
} VersionDefinition;

typedef std::vector<VersionDefinition> VersionDefinitionList;

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

typedef struct {
	uint32_t mReaderUid;
	uint32_t mCardUid;
} Combination;

typedef std::map<uint32_t, std::vector<Combination>*> CombinationMatrix;


#endif // DATABASEDEFINITIONS_H
