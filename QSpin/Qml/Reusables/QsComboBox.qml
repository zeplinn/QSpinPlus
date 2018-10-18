import QtQuick 2.11
import QtQuick.Controls 2.3
import QSpin.CppItems 1.0
ComboBox {
    id: control
	property color backgroundColor: QsStyle.panelBackground
	property color textColor: QsStyle.textColor
    height: 32
    model: ["First", "Second", "Third"]

    delegate: ItemDelegate {
        width: control.width
        contentItem: QsText {
            id:txtDisplay
            text: modelData
            //color: "#21be2b"
            //font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            states: State{
                when: mouseDetection.containsMouse
                PropertyChanges {
                    target: txtDisplay
                    color:"blue"
                }
            }

        }
        MouseArea{
            id:mouseDetection
            anchors.fill: parent
            hoverEnabled: true

        }

        //highlighted: control.highlightedIndex === index

    }

    //dropdown selection arrow
    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: control
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            //context.fillStyle = control.pressed ? "#17a81a" : "#21be2b";
			context.fillStyle = control.pressed ? "#17a81a" : QsStyle.borderBackground;
            context.fill();
        }
    }

    contentItem: QsText {
        leftPadding: 10

        rightPadding: 5
        text: control.displayText
        //font: control.font
        //color: control.pressed ? "#17a81a" : "#21be2b"
        //color: QSpinStyle.textColor

        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: control.height
        //border.color: control.pressed ? "#17a81a" : "#21be2b"
		color: QsStyle.panelBackground
		border.color: QsStyle.borderBackground
        border.width: control.visualFocus ? 2 : 1
        radius: 2
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            delegate: QsText{
                text: modelData
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            //border.color: "#21be2b"
			border.color: QsStyle.borderBackground
			color: QsStyle.panelBackground
            radius: 2
        }
    }
}
