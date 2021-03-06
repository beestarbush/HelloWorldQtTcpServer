#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QObject>
#include <database/DatabaseDefinitions.h>

typedef std::vector<Combination> Combinations;

class ApplicationData : public QObject
{
	Q_OBJECT
	Q_PROPERTY(unsigned int qActiveCombinationId READ getActiveCombinationId WRITE setActiveCombinationId NOTIFY activeCombinationIdChanged)
	Q_PROPERTY(QString qActiveFilename READ getActiveFilename WRITE setActiveFilename NOTIFY activeFilenameChanged)
	Q_PROPERTY(QString qUnknownIds READ getUnknownIds WRITE setUnknownIds NOTIFY unknownIdsChanged)

	public:
		explicit ApplicationData(QObject *parent = nullptr);

		void dump();

		uint32_t getActiveCombinationId() const;
		void setActiveCombinationId(const uint32_t & aId);

		QString getActiveFilename() const;
		void setActiveFilename(const QString & aFilename);

		void addCombination(Combination aCombination);
		void setCombination(uint32_t aReaderUid, uint32_t aCardUid);
		Combinations * getCombinations();
		Combination getCombinationByIndex(uint32_t aIndex);

		void addUnknownId(QString aType, QString aId);
		void setUnknownIds(QString aIds);
		QString getUnknownIds();

	signals:
		void combinationsChanged();
		void activeCombinationIdChanged();
		void activeFilenameChanged();
		void unknownIdsChanged();

	private:
		Combinations mCombinations;
		uint32_t mActiveCombinationId;
		QString mActiveFilename;
		QString mUnknownIds;
};

#endif // APPLICATIONDATA_H
