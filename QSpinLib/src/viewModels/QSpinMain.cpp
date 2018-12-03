#include "qspin/viewModels/QSpinMain.h"


void QSpinMain::registerAllQmlTypes(){
    qRegisterMetaType<QsSpinRunner::Status>("QsSpinRunner::Status");
    qRegisterMetaType<VerificationResultFileChanged::Status>("VerificationResultFileChanged::Status");
    const char space[] = "QSpin.CppItems";
    qmlRegisterUncreatableType<Arg>(space,1,0,"Arg","Uncreatable enum type only");
    //	qmlRegisterType<QsHandler>(space,1,0,"QsHandler");
    qmlRegisterType<QsError>(space,1,0,"QsError");
    qmlRegisterType<QsCodeEditorHandler>(space,1,0,"QsCodeEditorHandler");
    qmlRegisterType<QsVerifyHandler>(space,1,0,"QsVerifyHandler");

    qmlRegisterType<VerificationQueue>(space,1,0,"VerificationQueue");
    qmlRegisterUncreatableType<ItemConfiguration>(space,1,0,"ItemConfiguration","ItemConfiguration can only be instantiated from a view model");
    qmlRegisterUncreatableType<ItemValueConfiguration>(space,1,0,"ItemValueConfiguration","ItemConfiguration can only be instantiated from a view model");
    qmlRegisterUncreatableType<ItemLTLConfiguration>(space,1,0,"ItemChoiceConfiguration","ItemConfiguration can only be instantiated from a view model");
    //qmlRegisterUncreatableType<VerificationConfiguration>(space,1,0,"VerificationConfiguration","VerificationConfiguration can only be instantiated from a view model");
    qmlRegisterType<VerificationConfiguration>(space,1,0,"VerificationConfiguration");
    qmlRegisterUncreatableType<Configurations>(space,1,0,"Configurations","verifycofig list");
    qmlRegisterType<QsVerifySettingsGroupHandler>(space,1,0,"QsVerifySettingsGroupHandler");
    qmlRegisterType<QsVerifyResultHandler>(space,1,0,"QsVerifyResultHandler");
    qmlRegisterUncreatableType<QsStyle>(space,1,0,"QsStyle","is an attached object only");

    qmlRegisterType<QsTableColumn>(space,1,0,"QsTableColumn");
    qmlRegisterType<QsTableHandler>(space,1,0,"QsTableHandler");
    qmlRegisterType<QsSpinQueueHandler>(space,1,0,"QsSpinQueueHandler");
    qmlRegisterType<QsDivider>(space,1,0,"QsDivider");
    qmlRegisterType<TextGutterArea>(space,1,0,"QsTextGutterArea");
    qmlRegisterType<PromelaSyntaxHighlighter>(space,1,0,"QsPromelaSyntaxHighlighter");
    //qmlRegisterType<QsQSpinMainHandler>(space,1,0,"QsMainHandler");
    qmlRegisterType<QsPromelaHandler> (space,1,0,"QsPromelaHandler");
    qmlRegisterType<QsConsoleHandler>(space,1,0,"QsConsoleHandler");
    qmlRegisterType<QsCreateNewProjectHandler>(space,1,0,"QsCreateNewProjectHandler");
    qmlRegisterType<QsCreateProjectHandler>(space,1,0,"QsCreateProjectHandler");

    qmlRegisterUncreatableType<FullStateSpaceFor>(space,1,0,"FullStateSpaceFor","FullStateSpaceFor usage cannot be created");
    qmlRegisterUncreatableType<FullStateSpaceSpecifications>(space,1,0,"FullStateSpaceSpecifications","FullStateSpaceSpecifications cannot be created");
    qmlRegisterUncreatableType<MemoryUsage>(space,1,0,"MemoryUsage","Memory usage cannot be created");
    qmlRegisterType<VerificationResults>(space,1,0,"VerificationResults");
    qmlRegisterType<QsVerifyResultReportHandler>(space,1,0,"QsVerifyResultReportHandler");
    qmlRegisterUncreatableType<VerificationResultContainer>(space,1,0,"VerificationResultContainer","VerificationResultContainer cannot be created");
    qmlRegisterUncreatableType<QsVerifyResultList>(space,1,0,"QsVerifyResultList","QsVerifyResultList cannot be created");
    qmlRegisterUncreatableType<QsVerifyResultListItem>(space,1,0,"QsVerifyResultListItem","QsVerifyResultListItem cannot be created");

}

void QSpinMain::loadColorScheme(const QString filename){
    qs().colorScheme()->open(filename);
}



