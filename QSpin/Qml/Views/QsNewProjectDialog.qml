import QtQuick 2.0
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Dialogs 1.3 as Fd
Dialog{
	id: rootId
	parent:ApplicationWindow.window.contentItem
	x: (parent.width-width)*0.5
	y: (parent.height-height)*0.5
	z:5
	//	property alias folder: handlerId.destination
	//	readonly property alias name: handlerId.name
	property alias filepath: handlerId.absolutePath
	//	QsCreateNewProjectHandler{
	//		id:handlerId
	//	}
	QsCreateProjectHandler{
		id:handlerId
	}

	title: qsTr("Create new Project")
	padding: 8
	header: QsText{
		padding: 8
		font.pointSize: 14
		text: rootId.title
	}
	footer: Item{
		implicitHeight: childrenRect.height
		implicitWidth: childrenRect.width
		Row{
			anchors.right: parent.right


			spacing: 8
			QsButton{
				enabled: handlerId.isValidName && handlerId.isValidFolder
				text: qsTr("Create")
				implicitWidth: 70
				onClicked: {
					rootId.accept()
					projectNameId.text=""
				}
			}
			QsButton{
				text: qsTr("Cancel")
				implicitWidth: 70
				onClicked:{

					rootId.reject()
					projectNameId.text=""
				}
			}
		}
	}

	modal: true
	closePolicy: Popup.NoAutoClose | Popup.CloseOnEscape
	background: Rectangle{
		color: QsStyle.general.background
		border.color: QsStyle.general.border
		border.width: 1
	}

	ColumnLayout{
		id:rootLayoutId
		anchors.fill: parent
		spacing: 20

		TextField{
			id:projectNameId
			Layout.fillWidth: true
			color: QsStyle.general.foreground
			placeholderText: "enter file name"
			onTextChanged:{
				handlerId.name = text
			}

			background: Rectangle{
				id:txtFieldBackgroundId
				color: QsStyle.general.background
				border.color: QsStyle.general.border
				border.width: 1
			}
			states:State{
				when:!handlerId.isValidName
				PropertyChanges {
					target: projectNameId
					color: "red"

				}
			}
		}

		RowLayout{
			spacing: 8
			QsText{
				id:lblFolderPath
				text: qsTr("Path:")
			}
			QsText{
				id:absolutePathId
				Layout.minimumWidth: 500
				Layout.maximumWidth: 500
				text: handlerId.absolutePath
				Layout.fillWidth: true
				states:State{
					when: !handlerId.isValidFolder
					PropertyChanges {
						target: lblFolderPath
						color :"red"
					}
				}
			}

			QsButton{
				text: qsTr("Browse")
				onClicked: folderExplorerId.open()
			}

		}
		Item {
			Layout.fillHeight: true
			Layout.fillWidth: true

		}


	}
	Fd.FileDialog{
		id:folderExplorerId
		folder: shortcuts.home
		onAccepted:{
			handlerId.folder = folder

		}
		selectFolder: true
	}
	Component.onCompleted: handlerId.folder = folderExplorerId.shortcuts.home

}
