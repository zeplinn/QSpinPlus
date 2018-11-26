import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
Item{
    id:textEditor
	property alias readonly: textArea.readOnly
    property alias font: textArea.font
    property int tabIndentSize: 4
    property alias foreground: textArea.color
    property alias background: backgroundId.color
    property alias fileUrl: docHandler.fileUrl
    property alias editorBackground: editorBackground.color
    readonly property alias documentHandler: docHandler // need better encapsulation to only expose what is needed to the outside
    property alias syntaxHighlighter: docHandler.syntaxHighlighter
    readonly property var saveDocument: docHandler.saveAs
    readonly property var openDocument: docHandler.open
    readonly property var append: textArea.append
    property alias canUndo: textArea.canUndo
    property alias canRedo: textArea.canRedo
    readonly property var undo: textArea.undo
    Rectangle{
        anchors.fill: parent
        id: editorBackground
        color : Qt.hsla(0,0,0.18,1)
    }
    QsCodeEditorHandler{
        id:docHandler
        textDocument: textArea.textDocument
    }
FontMetrics{
    id: fontMetricsId
font: textArea.font
}
    Flickable {

        property bool isScrolling: false
        interactive: true
        id: flickable
        anchors{
            left:gutterArea.right
            right: parent.right
            top:parent.top
            bottom: parent.bottom
        }
        leftMargin: 2
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.VerticalFlick
        onContentYChanged: {
            gutterArea.documentViewportVerticalupdate(contentY,contentY+height,vScrollBar.active)
        }

        TextArea.flickable: TextArea {
            id: textArea
			implicitHeight: 300
			implicitWidth: 500
            tabStopDistance: fontMetricsId.averageCharacterWidth+textEditor.tabIndentSize
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
            leftPadding: 0
            rightPadding: 6
            topPadding: 0
            bottomPadding: 0
            background: Rectangle{ id:backgroundId; color: QsStyle.general.background}
            color: QsStyle.general.foreground

        }

        states: [
            State {
                when: textEditor.width< 300
                PropertyChanges {
                    target: flickable
                    width: 300 - gutterArea.width

                }
                AnchorChanges{
                    target: flickable
                    anchors.right: undefined
                }
            }
        ]
        ScrollBar.vertical: QsScrollBar {
            id:vScrollBar

        }
	}
    QsTextGutterArea{
        id:gutterArea
        anchors{
            left:parent.left
            top:parent.top
            bottom: parent.bottom
        }

        textDocument: textArea.textDocument
        textColor: QsStyle.general.foreground// textEditor.textColor
        font: textEditor.font
        visibleTop: flickable.contentY
        scrollViewHeight: flickable.height
        width: gutterareaWidth.advanceWidth("9999")+rightMargin*2
        rightMargin: 15
        height: textArea.contentHeight
    }
    FontMetrics{
        id:gutterareaWidth
        font{
            family: textArea.font.family
            pointSize: textArea.font.pointSize
        }
    }
}
