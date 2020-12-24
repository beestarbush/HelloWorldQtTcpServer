#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <communication/tcp/TcpController.h>
#include <ApplicationLogic.h>
#include <ApplicationData.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication lApplication(argc, argv);
	QGuiApplication::setApplicationName("helloapp");
	QGuiApplication::setOrganizationName("flup");

	QQmlApplicationEngine lEngine;
	const QUrl url(QStringLiteral("qrc:/MainScreen.qml"));
	QObject::connect(&lEngine, &QQmlApplicationEngine::objectCreated,
					 &lApplication, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

	ApplicationData lData;
	ApplicationLogic lLogic(&lData);
	lLogic.setup();

	TcpController lController;
	lEngine.rootContext()->setContextProperty("qController", &lController);
	lEngine.load(url);

	lController.registerReaderDataCallback(&lLogic);
	lController.start();

	return lApplication.exec();
}
