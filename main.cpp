#include <QCoreApplication>
#include <communication/tcp/TcpController.h>
#include <ApplicationLogic.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ApplicationLogic lLogic;
	lLogic.setup();
	//TcpController lController(&lLogic);
	//lController.start();

	lLogic.onReaderDataAvailable("AABBCCDD", "123456");

	return a.exec();
}
