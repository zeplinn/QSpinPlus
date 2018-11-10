#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qspin/cppView/TextGutterArea.h"
#include "qspin/viewModels/QsStyle.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"
#include "qspin/viewModels/QsError.h"
#include "qspin/viewModels/QsHandler.h"
#include "qspin/viewModels/QsVerifyHandler.h"
#include "qspin/cppView/QsDivider.h"
#include "qspin/QmlImportNames.h"
#include "qspin/viewModels/QsVerifyResultHandler.h"
#include "qspin/viewModels/QSpinMain.h"
#include "qspin/Qs.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
//    QsCodeEditorHandler::registerAsQml();
//    QsStyle::registerAsQml();
//    QsError::registerAsQml();
//    QsHandler::registerAsQml();
//    QsVerifyHandler::registerAsQml();

//	const char space[] = "QSpin.CppItems";

//	qmlRegisterType<QsHandler>(space,1,0,"QsHandler");
//	qmlRegisterType<QsError>(space,1,0,"QsError");
//	qmlRegisterType<QsCodeEditorHandler>(space,1,0,"QsCodeEditorHandler");
//	qmlRegisterType<QsVerifyHandler>(space,1,0,"QsVerifyHandler");
//	qmlRegisterType<QsVerifyResultHandler>(space,1,0,"QsVerifyResultHandler");
//	qmlRegisterUncreatableType<QsStyle>(space,1,0,"QsStyle","is an attached object only");

//	qmlRegisterType<QsDivider>(space,1,0,"QsDivider");
//	qmlRegisterType<TextGutterArea>(space,1,0,"QsTextGutterArea");

	//TextGutterArea::registerAsQml();
	QSpinMain::registerAllQmlTypes();
    EventAggregator& a =Qs::instance().msgService();
	QSpinMain qspin;
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
