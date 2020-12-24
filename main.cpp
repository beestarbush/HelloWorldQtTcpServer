#include <QCoreApplication>
#include <communication/tcp/TcpController.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	TcpController lController;
	lController.start();

	return a.exec();
}
