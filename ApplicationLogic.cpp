#include "ApplicationLogic.h"
#include <ApplicationData.h>
#include <QDebug>

ApplicationLogic::ApplicationLogic(ApplicationData * aData) :
	ReaderDataCallback(),
	mMacAddressesQueue(),
	mCardIdsQueue(),
	mMutex(),
	mDatabaseController(),
	mApplicationData(aData)
{
}

bool ApplicationLogic::setup()
{
	if (!mDatabaseController.open())
	{
		qDebug() << "Failed to open database.";
		return false;
	}

	if (!mDatabaseController.load())
	{
		qDebug() << "Failed to load data from database.";
		return false;
	}

	if (!mDatabaseController.close())
	{
		qDebug() << "Failed to close database.";
		return false;
	}

	// Check amount of readers.
	for (auto lReader : *mDatabaseController.getReaderDefinitionList())
	{
		Combination lCombination = { lReader.mUid,
									 0 };
		mApplicationData->addCombination(lCombination);
	}

	// Start processing data.
	connect(mApplicationData, SIGNAL(combinationsChanged()), this, SLOT(onCombinationsChanged()), Qt::ConnectionType::QueuedConnection);
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

	uint32_t lReaderUid = 0;
	if (!mDatabaseController.getReaderIdByMacAddress(lMacAddress, lReaderUid))
	{
		qDebug() << "Failed to lookup reader ID:" << lMacAddress;
		mApplicationData->addUnknownId("Node", lMacAddress);
		return;
	}

	uint32_t lCardUid = 0;
	if (!mDatabaseController.getCardUidByCardId(lCardId, lCardUid))
	{
		qDebug() << "Failed to lookup card UID:" << lCardId;
		mApplicationData->addUnknownId("Card", lCardId);
		return;
	}

	mApplicationData->setCombination(lReaderUid, lCardUid);
}

void ApplicationLogic::onCombinationsChanged()
{
	QMutexLocker lLocker(&mMutex);

	mApplicationData->dump();

	if (!determineActiveCombination())
	{
		qDebug() << "Failed to determine active combination.";
		return;
	}

	QString lFilename;
	if (!mDatabaseController.getFilenameByCombinationId(mApplicationData->getActiveCombinationId(), lFilename))
	{
		qDebug() << "Failed to retrieve filename for active combination ID: " << mApplicationData->getActiveCombinationId();
		return;
	}

	mApplicationData->setActiveFilename(lFilename);
}

bool ApplicationLogic::determineActiveCombination()
{
	for (auto lCombinationIds : *mDatabaseController.getCombinationMatrix())
	{
		uint32_t lCombinationsFound = 0;
		uint32_t lCombinationCount = mApplicationData->getCombinations()->size();
		for (uint32_t i = 0; i < lCombinationCount; i++)
		{
			std::vector<Combination>* lCombinationList = lCombinationIds.second;

			Combination lActiveCombination = mApplicationData->getCombinationByIndex(i);
			Combination lDefinedCombination = (*lCombinationList)[i];

			if (lActiveCombination.mReaderUid == lDefinedCombination.mReaderUid &&
				lActiveCombination.mCardUid == lDefinedCombination.mCardUid)
			{
				lCombinationsFound++;
			}
		}
		if (lCombinationsFound == lCombinationCount)
		{
			mApplicationData->setActiveCombinationId(lCombinationIds.first);
			return true;
		}
	}

	return false;
}
