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
#include "qspin/viewModels/ColorScheme.h"
#include "qspin/models/QsVerificationConfiguration.h"
#include "qspin/models/Arg.h"
#include "qspin/viewModels/QsVerifySettingsGroupHandler.h"
#include "qspin/viewModels/QsTableHandler.h"
#include "qspin/viewModels/QsSpinQueueHandler.h"
#include "qspin/models/QsPromelaSyntaxHighlighter.h"
class QSpinMain : public QObject
{
		Q_OBJECT
		EventAggregator& msgService;
	public:
        static void registerAllQmlTypes();

        void loadColorScheme(const QString filename);

		explicit QSpinMain(QObject *parent = nullptr,EventAggregator& msgService = Qs::instance().msgService());
        Q_INVOKABLE qsProject_ptr createNewProject(const QString& name,const QUrl filePath);
	signals:

	public slots:
};

#endif // QSPINMAIN_H
