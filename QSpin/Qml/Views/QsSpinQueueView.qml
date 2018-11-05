import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQml.Models 2.4 as Qm
import QtQuick.Layouts 1.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
Item {

	ListView{
		anchors.fill: parent
		id:spinListId
		clip: true
		spacing: 4
		boundsBehavior: Flickable.StopAtBounds
		headerPositioning: ListView.OverlayHeader
		header: ItemDelegate{
			anchors.left: parent.left
			anchors.right: parent.right
			z:5
			implicitHeight: 24
			padding: 0
			background: Rectangle{
				gradient: Gradient{
					GradientStop{ position: 0; color: QsStyle.general.menubarGradiant0 }
					GradientStop{ position: 1; color: QsStyle.general.menubarGradiant1 }
				}

				QsDivider{
					anchors.left : parent.left
					anchors.right: parent.right
					anchors.bottom: parent.bottom
					anchors.bottomMargin: 1
					color: QsStyle.general.border
				}
			}
			RowLayout{
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.leftMargin: 8
				anchors.rightMargin: 8
				anchors.verticalCenter: parent.verticalCenter
				spacing: 8
				QsText{	Layout.preferredWidth: 128; text: qsTr("Name")}
				QsText{	Layout.preferredWidth: 128; text: qsTr("Created at") }
				QsText{	Layout.preferredWidth: 128; text: qsTr("Started at") }
				QsText{	Layout.preferredWidth: 128; text: qsTr("Status") }

			}

		}

		model: visualModelId

//		QsScrollBar.vertical: QsScrollBar{
//			id:vBarId
//			parent: spinListId.parent
//			anchors.top: spinListId.top
//			anchors.bottom: spinListId.bottom
//			anchors.left: spinListId.right
//			anchors.leftMargin: 8
//			policy: QsScrollBar.AlwaysOn
//			//implicitWidth: 35
//		}
	}
//	QsSpinQueueHandler{
//		id:handlerId
//	}

	Component{
		id:rowDelegateId
		Item{
			anchors.left: parent.left
			anchors.right: parent.right
			implicitHeight: 24

		RowLayout{
			anchors.fill: parent
			id:rowId
			anchors.leftMargin: 8
			anchors.rightMargin: 8
			spacing: 8
			property int preWidth: 128
			QsText{
				Layout.fillWidth: true
				text: model.name_role
			}
			QsText{
				Layout.preferredWidth: rowId.preWidth
				text: model.createdTime_role
			}
			QsText{
				Layout.preferredWidth: rowId.preWidth
				text: model.startTime_role
			}
			QsText{
				Layout.preferredWidth: rowId.preWidth
				text: model.status_role
			}
			QsButton{
				text: qsTr("suspend");
			}

			QsToolButton{
				implicitHeight: 18
				implicitWidth: 18
				imageSource: "qrc:/icons/close.png"
			}
		}
		QsDivider{
			opacity: 0.1
			oritentation: Qt.Horizontal
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			color: QsStyle.general.hovered
			//anchors.margins: 1
		}
		}

	}
	Qm.DelegateModel{
		id:visualModelId
		delegate: rowDelegateId
		//model: handlerId
		model: dummyModelId
	}
	ListModel{
		id:dummyModelId
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}
		ListElement{
			name_role: "some name"
			createdTime_role: "created at"
			status_role: "some status"
			startTime_role : "started at"
		}

	}
}
