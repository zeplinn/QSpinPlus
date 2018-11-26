#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qspin/viewModels/QSpinMain.h"
#include "qspin/Qs.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	//TextGutterArea::registerAsQml();
	QSpinMain::registerAllQmlTypes();
	QSpinMain qspin;
    Qs& e =qspin.qs();
    qspin.loadColorScheme(":/misc/dark.scheme");
	//QsDivider::registerAsQml();
	QQmlApplicationEngine engine;
	auto ctx = engine.rootContext();
	ctx->setContextProperty("qspin",&qspin);
	engine.addImportPath(QStringLiteral(PROJECT_IMPORTS));
	engine.load(QUrl(QStringLiteral("qrc:/qspin.qml")));
#if QS_DEBUG
	QStringList paths = engine.importPathList();
	qDebug() <<" import path list:"<<paths.count();
	for( int i =0; i< paths.count();i++){
		qDebug()<< "path "<< i<<paths[i];
	}
#endif
	if (engine.rootObjects().isEmpty())
		return -1;

//	QsProject pro("testPro");
//	pro.addNewConfiguration("newConfig1");
//	QsProject::saveAs(pro,"testPro.json");
//	QsProject::open(pro,"testPro.json");

	return app.exec();
}
