#include "qspin/viewModels/QSpinMain.h"

void QSpinMain::registerAllQmlTypes(){
    const char space[] = "QSpin.CppItems";
    qmlRegisterUncreatableType<Arg>(space,1,0,"Arg","Uncreatable enum type only");
    qmlRegisterType<QsHandler>(space,1,0,"QsHandler");
    qmlRegisterType<QsError>(space,1,0,"QsError");
    qmlRegisterType<QsCodeEditorHandler>(space,1,0,"QsCodeEditorHandler");
    qmlRegisterType<QsVerifyHandler>(space,1,0,"QsVerifyHandler");

    qmlRegisterUncreatableType<ItemConfiguration>(space,1,0,"ItemConfiguration","ItemConfiguration can only be instantiated from a view model");
    qmlRegisterUncreatableType<ItemValueConfiguration>(space,1,0,"ItemValueConfiguration","ItemConfiguration can only be instantiated from a view model");
    qmlRegisterUncreatableType<ItemChoiceConfiguration>(space,1,0,"ItemChoiceConfiguration","ItemConfiguration can only be instantiated from a view model");
    qmlRegisterUncreatableType<VerificationConfiguration>(space,1,0,"VerificationConfiguration","VerificationConfiguration can only be instantiated from a view model");

    qmlRegisterType<QsVerifySettingsGroupHandler>(space,1,0,"QsVerifySettingsGroupHandler");
    qmlRegisterType<QsVerifyResultHandler>(space,1,0,"QsVerifyResultHandler");
    qmlRegisterUncreatableType<QsStyle>(space,1,0,"QsStyle","is an attached object only");

    qmlRegisterType<QsTableColumn>(space,1,0,"QsTableColumn");
    qmlRegisterType<QsTableHandler>(space,1,0,"QsTableHandler");
    qmlRegisterType<QsSpinQueueHandler>(space,1,0,"QsSpinQueueHandler");
    qmlRegisterType<QsDivider>(space,1,0,"QsDivider");
    qmlRegisterType<TextGutterArea>(space,1,0,"QsTextGutterArea");
}

void QSpinMain::loadColorScheme(const QString filename){
    Qs::instance().colorScheme().open(filename);
}

QSpinMain::QSpinMain(QObject *parent, EventAggregator& msgService)
    : QObject(parent), msgService(msgService)
{
}

qsProject_ptr QSpinMain::createNewProject(const QString &name, const QUrl filePath){
    Q_UNUSED(name)
    QFile f(filePath.toLocalFile());
    QFileInfo fInfo(f);
    if(!fInfo.dir().exists())
        fInfo.dir().mkdir(fInfo.absoluteDir().path());

    return qsProject_ptr(nullptr);
}
