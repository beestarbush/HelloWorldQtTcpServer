#ifndef APPLICATIONLOGIC_H
#define APPLICATIONLOGIC_H

#include <ReaderDataCallback.h>
#include <QMutex>
#include <QQueue>
#include <database/DatabaseController.h>

class ApplicationData;

class ApplicationLogic : public ReaderDataCallback
{
	Q_OBJECT

	public:
		explicit ApplicationLogic(ApplicationData * aData);
		virtual ~ApplicationLogic() override = default;

		bool setup();

	signals:
		void processData();
		void combinationsChanged();

	public slots:
		void onReaderDataAvailable(QString aMacAddress, QString aCardId) override;
		void onProcessData();
		void onCombinationsChanged();

	private:
		QQueue<QString> mMacAddressesQueue;
		QQueue<QString> mCardIdsQueue;
		QMutex mMutex;

		DatabaseController mDatabaseController;
		ApplicationData * mApplicationData;

		bool determineActiveCombination();
};

#endif // APPLICATIONLOGIC_H
