#ifndef TCPHANDLER_H
#define TCPHANDLER_H

#include <QThread>
#include <QTcpSocket>
#include <communication/MessageParser.h>
#include <dataobjects/RfidReaderDataObject.h>
#include <dataobjects/NodeInfoDataObject.h>

class TcpHandler : public QThread
{
		Q_OBJECT
		Q_PROPERTY(bool qIsConnected READ getIsConnected NOTIFY isConnectedChanged)
		Q_PROPERTY(NodeInfoDataObject * qNodeInfoData MEMBER mNodeInfoData CONSTANT)
		Q_PROPERTY(RfidReaderDataObject * qRfidReaderData MEMBER mRfidReaderData CONSTANT)

	public:
		TcpHandler(unsigned short aId, QObject * aParent = nullptr);
		void run() override;

		bool getIsConnected() const;
		void setIsConnected(bool aIsConnected);

	public slots:
		void readyRead();
		void disconnected();

	signals:
		void error(QTcpSocket::SocketError aError);
		void isConnectedChanged();

	private:
		MessageParser mParser;
		QTcpSocket * mSocket;
		int mSocketDescriptor;
		bool mIsConnected;

		NodeInfoDataObject * mNodeInfoData;
		RfidReaderDataObject * mRfidReaderData;
};

#endif // TCPHANDLER_H
