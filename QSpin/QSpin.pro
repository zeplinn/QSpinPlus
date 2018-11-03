QT += quick qml gui quickcontrols2
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
PROJECT_IMPORTS=\\\"$${PWD}/../\\\"

debug:DEFINES += QS_DEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



RESOURCES += \
    #qml/reusables/reusables.qrc \
    Qml/qml.qrc \
    icons/icons.qrc\
    misc.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += \
    $$PWD/../

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH += \
    $$PWD/../

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../QSpinLib/hpp
DEPENDPATH +=  $$PWD/../QSpinLib
LIBS += -L$$PWD/../QSpinLib/bin -lQSpinLib

SOURCES += \
    main.cpp
#PRECOMPILED_HEADER = ../Precompiled.h
#HEADERS += \
#    ../Precompiled.h


