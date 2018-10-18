#ifndef QSPINMAIN_H
#define QSPINMAIN_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/Qs.h"
#include "qspin/models/QsProject.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"
#include "qspin/viewModels/QsStyle.h"
#include "qspin/viewModels/QsVerifyHandler.h"
#include "qspin/viewModels/QsVerifyResultHandler.h"
#include "qspin/cppView/QsDivider.h"
#include "qspin/cppView/TextGutterArea.h"
#include "qspin/viewModels/QsHandler.h"
class QSpinMain : public QObject
{
		Q_OBJECT
		EventAggregator& msgService;
	public:
		static void registerAllQmlTypes(){
			const char space[] = "QSpin.CppItems";

			qmlRegisterType<QsHandler>(space,1,0,"QsHandler");
			qmlRegisterType<QsError>(space,1,0,"QsError");
			qmlRegisterType<QsCodeEditorHandler>(space,1,0,"QsCodeEditorHandler");
			qmlRegisterType<QsVerifyHandler>(space,1,0,"QsVerifyHandler");
			qmlRegisterType<QsVerifyResultHandler>(space,1,0,"QsVerifyResultHandler");
			qmlRegisterUncreatableType<QsStyle>(space,1,0,"QsStyle","is an attached object only");

			qmlRegisterType<QsDivider>(space,1,0,"QsDivider");
			qmlRegisterType<TextGutterArea>(space,1,0,"QsTextGutterArea");
		}
		explicit QSpinMain(QObject *parent = nullptr,EventAggregator& msgService = Qs::instance().msgService());
		Q_INVOKABLE qsProject_ptr createNewProject(const QString& name,const QUrl filePath){
			QFile f(filePath.toLocalFile());
			QFileInfo fInfo(f);
			if(!fInfo.dir().exists())
				fInfo.dir().mkdir(fInfo.absoluteDir().path());

			return qsProject_ptr(nullptr);
		}
	signals:

	public slots:
};

#endif // QSPINMAIN_H
