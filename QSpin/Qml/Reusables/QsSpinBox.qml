import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Shapes 1.11
import QtQuick.Layouts 1.11

SpinBox {
	id: control

	property int spinHeight: 20
	property alias label: labelId.text
	property int minimumInputWidth: 150
	property alias checked: buttonStateId.checked

	value: 0
	editable: true
	implicitHeight: 32
	padding: 5
	font.pointSize: 10

	contentItem:
		RowLayout{
		//anchors.horizontalCenter: control.horizontalCenter
//		implicitHeight: childrenRect.height
//		implicitWidth: childrenRect.width
		spacing: 8

			QsText{
				Layout.fillWidth: true
//				anchors.left: parent.left
//				anchors.verticalCenter: parent.verticalCenter
				id:labelId
				text: qsTr("default")
				color: QsStyle.spinbox.foreground
				MouseArea{
					id: buttonStateId
					property bool checked: false
					hoverEnabled: true
					anchors.fill: parent
					cursorShape: Qt.ArrowCursor
					onClicked: checked = !checked
				}
				states: State{
					when: buttonStateId.containsMouse
					PropertyChanges {
						target: labelId
						color: QsStyle.general.hovered

					}
				}
			}


			TextInput {
				id:inputId
				//Layout.fillWidth: true
				rightPadding: 8
				Layout.minimumWidth: control.minimumInputWidth
				z: 2
				selectByMouse: true
				onFocusChanged: if(focus) selectAll()
				text:control.value
				font:labelId.font
				color: QsStyle.spinbox.input
				selectionColor: "#21be2b"
				selectedTextColor: "#ffffff"
				horizontalAlignment: Text.AlignRight
				verticalAlignment: Text.AlignVCenter
				//verticalAlignment: Qt.AlignVCenter

				readOnly: !control.editable
				validator: control.validator
				inputMethodHints: Qt.ImhFormattedNumbersOnly
			}
		}

	property int indicatorsPadding: 4
	property int indicatorSize: 8
	property color indicatorColor: QsStyle.spinbox.spinner
	property int indicatorThickness: 3
	up.indicator: Shape{
		id:upIndicatorId
		anchors.right: parent.right
		anchors.rightMargin: 3
		anchors.top: parent.top
		height: control.height *0.5
		width: height
		readonly property int half: height *0.5
		ShapePath{
			startX: indicatorsPadding
			startY: upIndicatorId.half
			strokeColor: control.indicatorColor
			strokeWidth: control.indicatorThickness
			PathLine{
				x:upIndicatorId.width - indicatorsPadding
				y: upIndicatorId.half
			}
			PathMove{
				x: upIndicatorId.half
				y: indicatorsPadding
			}
			PathLine{
				x: upIndicatorId.half
				y: upIndicatorId.height - indicatorsPadding
			}
		}

	}
	down.indicator: Shape{
		id:downIndicatorId
		anchors.right: parent.right
		anchors.rightMargin: 3
		anchors.bottom: parent.bottom
		height: control.height *0.5
		width: height
		readonly property int half: height *0.5
		ShapePath{
			startX: indicatorsPadding
			startY: downIndicatorId.half
			strokeColor: control.indicatorColor
			strokeWidth: control.indicatorThickness
			PathLine{
				x:downIndicatorId.width - indicatorsPadding
				y: downIndicatorId.half
			}
		}

	}
	background:
		Rectangle {
		border.width: 1
		border.color: QsStyle.spinbox.border
		color: "transparent"
		radius:2
		Rectangle{
			x:1
			anchors.top:parent.top
			anchors.topMargin: 1
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 1
			width: labelId.width
			id:selectionColor
			color: buttonStateId.checked ? QsStyle.spinbox.pressed : "transparent"
		}

		QsDivider{
			x:labelId.width
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			oritentation: Qt.Vertical
			color: QsStyle.spinbox.border
		}
	}

}


