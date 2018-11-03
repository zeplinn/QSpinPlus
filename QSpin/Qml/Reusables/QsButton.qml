import QtQuick 2.11
import QtQuick.Controls 2.3
import QSpin.CppItems 1.0
Button {
    id:control
    text:qsTr("not yet filled")
    highlighted: true
    height: 32
    padding: 5
    property alias textColor: btnTxt.color
	property color borderColor: QsStyle.button.border
	property bool useToolTip: false
	property string toolTip: ""
    contentItem: QsText{
		ToolTip.visible: useToolTip  && hovered
		ToolTip.text: toolTip
		ToolTip.delay: 500
        id:btnTxt
        property bool isHovering: false
        text: parent.text
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
		color: hovered ? QsStyle.general.hovered : QsStyle.button.foreground


    }

    background: Rectangle{
        id:background
		color: checked ? QsStyle.button.pressed : "transparent"
        border.color: control.borderColor
        border.width: 1
        radius: 3
//        MouseArea{
//            hoverEnabled: true
//            anchors.fill: parent
//            onEntered: btnTxt.isHovering =true
//            onExited: btnTxt.isHovering = false
//            onClicked: {mouse.accepted=false}
//        }
    }

}
