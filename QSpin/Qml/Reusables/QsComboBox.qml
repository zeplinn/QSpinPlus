import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
ComboBox {
    id: control
	property color backgroundColor: QsStyle.combobox.background
	property color textColor: QsStyle.combobox.foreground
    height: 32
    model: ["First", "Second", "Third"]

	delegate: ItemDelegate {
		//width: control.width
		anchors.left: parent.left
		anchors.right: parent.right
//		anchors.leftMargin: 8
//		anchors.rightMargin: 8
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
					color:QsStyle.general.hovered
                }
            }

        }
        MouseArea{
            id:mouseDetection
			anchors.fill: parent
			hoverEnabled: true
			onClicked: {currentIndex = index; popupId.close()}
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
			context.fillStyle = QsStyle.combobox.icon// control.pressed ? QsStyle.combobox.pressed : QsStyle.combobox.background;
            context.fill();
        }
    }

    contentItem: QsText {
		leftPadding: 16

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
		color: QsStyle.combobox.background
		border.color: QsStyle.combobox.border
        border.width: control.visualFocus ? 2 : 1
        radius: 2
    }

    popup: Popup {
		id:popupId
        y: control.height - 1
        width: control.width
		implicitHeight: contentItem.implicitHeight
		padding: 8
		contentItem: ListView {
            clip: true
			interactive: false
			implicitHeight: contentHeight+10
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
//            delegate: QsText{
//                text: modelData
//            }

			//ScrollIndicator.vertical: ScrollIndicator { }
		}

        background: Rectangle {
            //border.color: "#21be2b"
			border.color: QsStyle.combobox.border
			color: QsStyle.combobox.background
            radius: 2

			MouseArea{
				anchors.fill: parent
				hoverEnabled: true
				onExited:{

					if(mouseX<4 || mouseX>popupId.width-4)
						popupId.close()
					else if (mouseY<4 || mouseY>popupId.height-4)
						popupId.close()
						console.debug("popup exited")
				}

			}
		}
	}

}
