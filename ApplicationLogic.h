#ifndef APPLICATIONLOGIC_H
#define APPLICATIONLOGIC_H

#include <ReaderDataCallback.h>
#include <QMutex>
#include <QQueue>
#include <QtSql/QSqlDatabase>

class ApplicationLogic : public ReaderDataCallback
{
		Q_OBJECT
	public:
		explicit ApplicationLogic();
		virtual ~ApplicationLogic();

		bool setup();

	signals:
		void processData();

	public slots:
		void onReaderDataAvailable(QString aMacAddress, QString aCardId) override;
		void onProcessData();

	private:
		QQueue<QString> mMacAddressesQueue;
		QQueue<QString> mCardIdsQueue;
		QMutex mMutex;

		QSqlDatabase mDatabase;

};

#endif // APPLICATIONLOGIC_H
