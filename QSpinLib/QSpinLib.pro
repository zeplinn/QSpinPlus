#-------------------------------------------------
#
# Project created by QtCreator 2018-08-03T17:47:05
#
#-------------------------------------------------

QT       += qml quick gui concurrent

TARGET = QSpinLib
TEMPLATE = lib
CONFIG += staticlib c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
unix:DEFINES += QS_OS_UNIX
win: DEFINES += QS_OS_WIN
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cppView/QsDivider.cpp \
    src/cppView/TextGutterArea.cpp \
    src/models/Arg.cpp \
    src/models/QsVerificationResults.cpp \
    src/viewModels/EventAggregator.cpp \
    src/viewModels/QsCodeEditorHandler.cpp \
    src/viewModels/QsError.cpp \
    src/viewModels/QsStyle.cpp \
    src/viewModels/QsVerifyHandler.cpp \
    src/viewModels/QsVerifyResultHandler.cpp \
    src/QmlImportNames.cpp \
    src/Qs.cpp \
    src/errors/QsJsonErrc.cpp \
    src/viewModels/QSpinMain.cpp \
    src/viewModels/QsCreateProjectHandler.cpp \
    src/viewModels/ColorScheme.cpp \
    src/models/QsVerificationConfiguration.cpp \
    src/models/QsItemConfiguration.cpp \
    src/viewModels/QsVerifySettingsGroupHandler.cpp \
    src/viewModels/QsTableHandler.cpp \
    src/viewModels/QsSpinQueueHandler.cpp \
    src/viewModels/QsItemConfigStateNotifier.cpp \
    src/models/QsPromelaSyntaxHighlighter.cpp \
    src/models/jsonQspinPlusSchemeIds.cpp \
    src/viewModels/QsTopToolbarHandler.cpp \
    src/viewModels/QsPromelaHandler.cpp \
    src/viewModels/QsConsoleHandler.cpp \
    src/viewModels/QsCreateNewProjectHandler.cpp \
    src/models/Configurations.cpp \
    src/models/QSpinPlus.cpp \
    src/models/VerificationQueue.cpp \
    src/models/QueuedVerification.cpp \
    src/models/QsSpinRunner.cpp \
    src/models/SpinCommands.cpp \
    src/QObjectBase.cpp \
    src/models/VerificationResultContainer.cpp \
    src/EventObjects.cpp \
    src/QObjectListBase.cpp

HEADERS += \
    hpp/qspin/cppView/QsDivider.h \
    hpp/qspin/cppView/TextGutterArea.h \
    hpp/qspin/models/Arg.h \
    hpp/qspin/models/IQsSerialization.h \
    hpp/qspin/models/QsVerificationResults.h \
    hpp/qspin/viewModels/EventAggregator.h \
    hpp/qspin/viewModels/QsCodeEditorHandler.h \
    hpp/qspin/viewModels/QsError.h \
    hpp/qspin/viewModels/QsStyle.h \
    hpp/qspin/viewModels/QsVerifyHandler.h \
    hpp/qspin/viewModels/QsVerifyResultHandler.h \
    hpp/qspin/QmlImportNames.h \
    hpp/qspin/Qs.h \
    hpp/qspin/errors/QsJsonErrc.h \
    hpp/qspin/qsErrors.h \
    hpp/qspin/viewModels/QSpinMain.h \
    hpp/qspin/viewModels/QsCreateProjectHandler.h \
    hpp/qspin/viewModels/ColorScheme.h \
    hpp/qspin/models/QsVerificationConfiguration.h \
    hpp/qspin/models/QsItemConfiguration.h \
    hpp/qspin/viewModels/QsVerifySettingsGroupHandler.h \
    hpp/qspin/viewModels/QsTableHandler.h \
    hpp/qspin/QpropertyHelper.h \
    hpp/qspin/viewModels/QsSpinQueueHandler.h \
    hpp/qspin/models/QsItemConfigStateNotifier.h \
    hpp/qspin/models/QsPromelaSyntaxHighlighter.h \
    hpp/qspin/models/jsonQspinPlusSchemeIds.h \
    hpp/qspin/viewModels/QsTopToolbarHandler.h \
    hpp/qspin/viewModels/QsPromelaHandler.h \
    hpp/qspin/viewModels/QsConsoleHandler.h \
    hpp/qspin/viewModels/QsCreateNewProjectHandler.h \
    hpp/qspin/models/Configurations.h \
    hpp/qspin/models/QSpinPlus.h \
    hpp/qspin/models/SpinCommands.h \
    hpp/qspin/models/VerificationQueue.h \
    hpp/qspin/models/QueuedVerification.h \
    hpp/qspin/models/QsSpinRunner.h \
    hpp/qspin/QObjectBase.h \
    hpp/qspin/EventObjects.h \
    hpp/qspin/models/VerificationResultContainer.h \
    hpp/qspin/QObjectListBase.h
INCLUDEPATH+=\
    $$PWD/hpp

DESTDIR += $$PWD/bin

unix {
    target.path = /usr/lib
    INSTALLS += target
}

