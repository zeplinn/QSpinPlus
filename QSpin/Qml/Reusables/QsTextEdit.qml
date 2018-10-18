import QtQuick 2.11
import QtQuick.Controls 2.3
import QSpin.CppItems 1.0
Flickable {

    property bool isScrolling: false
    interactive: true
    id: flickable
    leftMargin: 2
    boundsBehavior: Flickable.StopAtBounds
    flickableDirection: Flickable.VerticalFlick
    property alias text: textArea.text
    property alias padding: textArea.padding

    //onMovingVerticallyChanged: {console.debug("moving vertically changed")}

    TextArea.flickable: TextArea {
        id: textArea
        //scale: 0.01
        renderType: Text.NativeRendering
        textFormat: Qt.PlainText
        wrapMode: TextArea.WordWrap
        selectByMouse: true
        persistentSelection: true
        font.family: "Consolas"
        font.pointSize: 10
        // Different styles have different padding and background
        // decorations, but since this editor is almost taking up the
        // entire window, we don't need them.
        padding: 5
        background: null
        color: QsStyle.textColor

    }

    ScrollBar.vertical: QsScrollBar {
        id:vScrollBar
        //onPressedChanged: {pressed ? console.debug("scrollBar started") :console.debug("scollbar stopped")}

    }
}
