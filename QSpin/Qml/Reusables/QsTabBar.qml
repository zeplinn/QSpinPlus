import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0

Container {
	id:rootId
	spacing: 8
	currentIndex: -1
	contentItem:Row{
		id: rowId
		objectName: qsTr("tabBarName");
		property alias currentIndex: rootId.currentIndex
		spacing:  rootId.spacing
		Repeater{
			id:layoutId

			model: rootId.contentModel

			//onModelChanged:  setIndex()
		}
	}
	function setIndex(){
		for(var i=0;i< rootId.count; i++ )
			rootId.itemAt(i).itemIndex=i
	}
	Component.onCompleted:setIndex()
}
