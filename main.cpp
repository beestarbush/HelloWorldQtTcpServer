#include <QCoreApplication>
#include <TcpController.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	std::vector<QByteArray> lInputBuffer;

	TcpController lController;
	lController.start();



	return a.exec();
}
