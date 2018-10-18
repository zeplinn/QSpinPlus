QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_qspintesting.cpp \
    QsProjectTesting.cpp \
    QsSpinRunTesting.cpp \
    QsSpinConfigurationTesting.cpp \
    TestSuite.cpp \
    SpinRunnerTests/RunSpinConfigurationTests.cpp \
    SpinConfiguratisonTests/GenerateRunDataTests.cpp \
    QsProjectTesting/QsProjectCreationTesting.cpp


include( $$PWD/../QSpinLibInclude.pri ) # required
HEADERS += \
    QsProjectTesting.h \
    QsSpinRunTesting.h \
    EmptyTest.h \
    QsSpinConfigurationTesting.h \ # \
    TestSuite.h \
    #../Precompiled.h
    SpinRunnerTests/RunSpinConfigurationTests.h \
    SpinConfiguratisonTests/GenerateRunDataTests.h \
    QsProjectTesting/QsProjectCreationTesting.h

RESOURCES += \
    files.qrc



