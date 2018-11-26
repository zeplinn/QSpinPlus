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
		color: QsStyle.general.foreground

    }

    ScrollBar.vertical: QsScrollBar {
        id:vScrollBar

    }
}
