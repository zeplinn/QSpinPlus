import QtQuick 2.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
Item {
    id: rootId
    implicitHeight: consoleId.implicitHeight
    implicitWidth: consoleId.implicitWidth

    QsConsoleHandler{

    }

    QsCodeEditor{
    id: consoleId
        anchors.fill: parent
        anchors.margins: 4
    }
}
