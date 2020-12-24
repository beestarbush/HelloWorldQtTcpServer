#ifndef TCPHANDLER_H
#define TCPHANDLER_H

#include <QThread>
#include <QTcpSocket>
#include <MessageParser.h>

class TcpHandler : public QThread
{
		Q_OBJECT
		Q_PROPERTY(bool qIsConnected READ getIsConnected NOTIFY isConnectedChanged)

	public:
		TcpHandler(unsigned short aId, QObject * aParent = nullptr);
		void run() override;

		bool getIsConnected() const;
		void setIsConnected(bool aIsConnected);

		QString getUid() const;
		void setUid(const QString & aUid);

	public slots:
		void readyRead();
		void disconnected();

	signals:
		void error(QTcpSocket::SocketError aError);
		void isConnectedChanged();
		void uidChanged();

	private:
		MessageParser mParser;
		QTcpSocket * mSocket;
		int mSocketDescriptor;
		bool mIsConnected;

		QString mUid;
};

#endif // TCPHANDLER_H
