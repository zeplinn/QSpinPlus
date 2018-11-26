import QtQuick 2.0
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Dialogs 1.3 as Fd
Dialog{
	id: rootId
	z:5
	property alias folder: handlerId.destination
	readonly property alias name: handlerId.name
	QsCreateNewProjectHandler{
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
				enabled: handlerId.canAccept
				text: qsTr("Create")
				implicitWidth: 70
				onClicked: rootId.accept()
			}
			QsButton{
				text: qsTr("Cancel")
				implicitWidth: 70
				onClicked: rootId.reject()
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
			text: handlerId.name
			onAccepted: handlerId.name =text
			background: Rectangle{
				id:txtFieldBackgroundId
				color: QsStyle.general.background
				border.color: QsStyle.general.border
				border.width: 1
			}
			states:State{
				when:handlerId.isValidName
				PropertyChanges {
					target: txtFieldBackgroundId
					border.color: "red"

				}
			}
		}
		/*
		RowLayout{

			CheckBox {
				id: checkBox
				checked: handlerId.useExistingPml
			}
			QsText{
				text: qsTr("use Existing promela file")
			}
		}
		RowLayout{
			visible: checkBox.checked
			enabled: visible
			spacing: 8
			QsText{
				id:lblPromPath
				text: qsTr("Path:")
			}
			QsText{
				id:promelaFilePathId
				Layout.minimumWidth: 500
				Layout.maximumWidth: 500
				Layout.fillWidth: true
				text: handlerId.promelaPath
				states:State{
					when: !handlerId.isValidPromelaFile
					PropertyChanges {
						target: lblPromPath
						color :"red"
					}
				}
			}
			QsButton{
				text: qsTr("browse")
				onClicked: promelaFileId.open()
			}
		}
*/
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
				text: handlerId.destination
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
		folder: handlerId.destination
		onAccepted: handlerId.setDestination(folder)
		selectFolder: true
	}


}
