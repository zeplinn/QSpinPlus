import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Shapes 1.11
import QtQuick.Layouts 1.11

SpinBox {
	id: control
	property int spinHeight: 20
	property alias label: btnTxt.text
	property int minimumInputWidth: 150
	property alias checked: btnCheck.checked
	property string toolTip: ""
	property bool useToolTip: false
	opacity: enabled ? 1 : 0.1;
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
		//spacing: 8
		Button {
			id:btnCheck
			Layout.fillWidth: true
			ToolTip.visible: hovered  && control.useToolTip
			ToolTip.text: control.toolTip
			ToolTip.delay: 500
			text:qsTr("not yet filled")
			highlighted: false
			padding: 5
			checkable:true
			height: parent.height

			contentItem: QsText{
				id:btnTxt
				property bool isHovering: false
				text: parent.text
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignHCenter
				color: hovered ? QsStyle.general.hovered : QsStyle.button.foreground


			}

			background: null

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
			font:btnTxt.font
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
			width: btnCheck.width
			id:selectionColor
			color: btnCheck.checked ? QsStyle.spinbox.pressed : "transparent"
		}

		QsDivider{
			x:btnCheck.width
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			oritentation: Qt.Vertical
			color: QsStyle.spinbox.border
		}
	}

}


