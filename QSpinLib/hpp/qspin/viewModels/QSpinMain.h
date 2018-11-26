#ifndef QSPINMAIN_H
#define QSPINMAIN_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
//#include "qspin/viewModels/EventAggregator.h"
//#include "qspin/Qs.h"
#include "qspin/QObjectBase.h"
#include "qspin/viewModels/QsPromelaHandler.h"
#include "qspin/models/Arg.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"
#include "qspin/viewModels/QsVerifyResultHandler.h"
#include "qspin/viewModels/QsCreateNewProjectHandler.h"
#include "qspin/viewModels/QsVerifySettingsGroupHandler.h"
#include "qspin/viewModels/QsVerifyHandler.h"
#include "qspin/viewModels/QsSpinQueueHandler.h"
#include "qspin/viewModels/QsTableHandler.h"
#include "qspin/viewModels/QsTopToolbarHandler.h"
//#include "qspin/viewModels/QsHandler.h"
#include "qspin/viewModels/QsConsoleHandler.h"
#include "qspin/viewModels/QsStyle.h"
#include "qspin/models/QsPromelaSyntaxHighlighter.h"
#include "qspin/cppView/QsDivider.h"
#include "qspin/cppView/TextGutterArea.h"
#include "qspin/models/Configurations.h"
#include "qspin/models/QsVerificationConfiguration.h"
class QSpinMain : public QObjectBase
{
        Q_OBJECT

protected:
	public:
		static void registerAllQmlTypes();

		void loadColorScheme(const QString filename);
        using QObjectBase::QObjectBase;
	signals:

	public slots:
};

#endif // QSPINMAIN_H
