#include "ApplicationData.h"
#include <QDebug>

ApplicationData::ApplicationData(QObject *parent) :
	QObject(parent),
	mCombinations(),
	mActiveCombinationId(0),
	mActiveFilename("empty.jpg"),
	mUnknownIds()
{

}

void ApplicationData::dump()
{
	qDebug() << "Active combination ID: " << mActiveCombinationId;
	qDebug() << "Active filename: " << mActiveFilename;
	qDebug() << "RID:" << "\t" << "CID:";
	for (auto lCombination : mCombinations)
	{
		qDebug() << lCombination.mReaderUid << "\t" << lCombination.mCardUid;
	}
}

uint32_t ApplicationData::getActiveCombinationId() const
{
	return mActiveCombinationId;
}

void ApplicationData::setActiveCombinationId(const uint32_t & aId)
{
	if (mActiveCombinationId != aId)
	{
		mActiveCombinationId = aId;
		emit activeCombinationIdChanged();
	}
}

QString ApplicationData::getActiveFilename() const
{
	return mActiveFilename;
}

void ApplicationData::setActiveFilename(const QString & aFilename)
{
	if (mActiveFilename.compare(aFilename) != 0)
	{
		mActiveFilename = aFilename;
		emit activeFilenameChanged();
	}
}

void ApplicationData::addCombination(Combination aCombination)
{
	mCombinations.push_back(aCombination);
	emit combinationsChanged();
}

void ApplicationData::setCombination(uint32_t aReaderUid, uint32_t aCardUid)
{
	mCombinations[aReaderUid].mReaderUid = aReaderUid;
	mCombinations[aReaderUid].mCardUid = aCardUid;
	emit combinationsChanged();
}

Combinations * ApplicationData::getCombinations()
{
	return &mCombinations;
}

Combination ApplicationData::getCombinationByIndex(uint32_t aIndex)
{
	return mCombinations[aIndex];
}

void ApplicationData::addUnknownId(QString aType, QString aId)
{
	mUnknownIds += (aType + ": " + aId + "\n");
	emit unknownIdsChanged();
}

void ApplicationData::setUnknownIds(QString aIds)
{
	mUnknownIds = aIds;
	emit unknownIdsChanged();
}

QString ApplicationData::getUnknownIds()
{
	return mUnknownIds;
}
