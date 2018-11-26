import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
QsButton {
	id:btnId
	property int itemIndex: -1
	property bool alwaysOne: false
	opacity: enabled ? 1 : 0.2
	implicitWidth: 150
	implicitHeight: 24
	height: 24
	leftPadding: 4
	rightPadding: 4

	background: Rectangle{
		color: checked ? QsStyle.button.pressed : "transparent"
		border.width:  checked ? 1 : 0
		border.color:  QsStyle.button.border
		radius: 2

		states:State {
			when: btnId.itemIndex === parent.currentIndex
			PropertyChanges {
				target: btnId
				checkable:true
				checked :true
				opacity: parent.enabled ? 1 : 0.2
			}
		}
	}
	onClicked:{
		if ("tabBarName" === parent.objectName)
			if(parent.currentIndex !== itemIndex)	parent.currentIndex = itemIndex
			else 					parent.currentIndex =-1
	}
}
