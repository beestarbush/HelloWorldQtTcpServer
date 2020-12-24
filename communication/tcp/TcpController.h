#ifndef TCPCONTROLLER_H
#define TCPCONTROLLER_H

#include <QTcpServer>
#include <QVariantList>

class TcpHandler;
class QTimer;

class TcpController : public QTcpServer
{
		Q_OBJECT
		Q_PROPERTY(QVariantList qConnectionList READ getConnectionList NOTIFY connectionListChanged)
	public:
		TcpController(QObject * aParent = nullptr);
		void start();

		QVariantList getConnectionList();

	public slots:
		void checkConnections();

	signals:
		void connectionListChanged();

	protected:
		void incomingConnection(qintptr aSocketDescriptor) override;

	private:
		QTimer * mCheckConnectionTimer;
		QVariantList mConnectionList;
};

#endif // TCPCONTROLLER_H
