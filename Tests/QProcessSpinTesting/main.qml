import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.3
import QtQml.Models 2.3
import Handler 1.0
Window {
	visible: true
	width: 600
	height: 1000
	title: qsTr("Hello World")
	QProcessHandler{
		id:qpHahndler

	}
	ColumnLayout{
		anchors.fill: parent
		ToolBar{
			Layout.fillWidth: true
			Flow{

				ToolButton{
					text: qsTr("open project")
				onClicked: openDialog.open()

				}
				ToolButton{
					text: qsTr("test msg system")
				}
				ToolButton{
					text:qsTr("currentDir")
					onClicked: qpHahndler.currentDir()
				}
				ToolButton{
					text: qsTr("run spin")
					onClicked: qpHahndler.runSpin()
				}
				ToolButton{
					text: qsTr("run pan")
					onClicked: qpHahndler.runPan()
				}

			}

		}
		Rectangle{
			border.color: "black"
			radius: 1
			Layout.fillHeight: true
			Layout.fillWidth: true

			//			Container{
			//				id:msgId
			//				anchors.fill: parent

			//				contentItem:ListView{
			//					id:msgChildId
			//					model: msgId.contentModel
			//					delegate: Text {
			//						id: delegateId
			//						text:modelData
			//						Component.onCompleted: console.debug("text: "+modelData)
			//					}
			//					onCountChanged: console.debug("count changed: "+count)
			//				}
			//			}
			ListView{
				anchors.fill: parent
				id: listId
				model: listModel
			}
		}
	}

	FileDialog{
		id:openDialog
		title: "open"
		selectExisting: true
		onAccepted: {

			qpHahndler.openProject(fileUrl)

		}
	}
	DelegateModel{
		id:listModel
		model: qpHahndler
		delegate: Text{
			text: msg_role
		}
	}

	Component{
		id: cmdText
		Text{

		}
	}

}
