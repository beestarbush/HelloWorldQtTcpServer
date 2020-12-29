#include <QCoreApplication>
#include <communication/tcp/TcpController.h>
#include <ApplicationLogic.h>
#include <ApplicationData.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ApplicationData lData;
	ApplicationLogic lLogic(&lData);
	lLogic.setup();

	TcpController lController;
	lController.registerReaderDataCallback(&lLogic);
	lController.start();

	return a.exec();
}
