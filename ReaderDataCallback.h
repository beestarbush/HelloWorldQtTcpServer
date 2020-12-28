#ifndef READERDATACALLBACK_H
#define READERDATACALLBACK_H

#include <QObject>

class ReaderDataCallback: public QObject
{
	Q_OBJECT
	public slots:
		virtual void onReaderDataAvailable(QString aMacAddress, QString aCardId) = 0;
};

#endif // READERDATACALLBACK_H
