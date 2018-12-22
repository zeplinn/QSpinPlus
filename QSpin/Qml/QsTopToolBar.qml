import QtQuick 2.11
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Dialogs 1.3
import QSpin.Qml.Views 1.0
ToolBar{
	id: rootId
	property bool isProjectOpen: false
	readonly property alias undoButton: btnUndoId
	readonly property alias redoButton: btnRedoId
	readonly property alias saveButton: saveProjectId
	readonly property alias isVerifyTabSelected: verifyTabId.checked
	readonly property alias isVerifyResultTabSelected:verifyResultTabId.checked
	readonly property alias isSimulationTabSelected: simulationTabId.checked
	readonly property alias isUiLocked: toolbarId.isUiLocked
	property alias toolViewsTabBar: toolsTabId
	signal saveProject(url fileUrl)
	signal openProject(url fileUrl)
	signal createProject(string filepath)


	implicitHeight: 32
	background:Rectangle{
		id: g

		//implicitHeight: 32
		border.color: QsStyle.general.border
		border.width: 1
		gradient: Gradient{
			GradientStop{ position: 0; color: QsStyle.general.menubarGradiant0 }
			GradientStop{ position: 1; color: QsStyle.general.menubarGradiant1}
		}
		//tool bar content
		RowLayout{
			id:toolbarId
			property bool isUiLocked: true
			anchors{
				fill: parent
				leftMargin: 8
				rightMargin: 8
			}
			QsToolButton{
				id:btnUndoId
				imageSource: "qrc:/icons/undoRedo.png"
			}
			QsToolButton{
				id:btnRedoId
				imageRotation: 180
				imageSource: "qrc:/icons/undoRedo.png"
			}

			QsToolButton{
				id:newProjectId
				implicitHeight: 24
				imageSource: "qrc:/icons/File Icon.png"
				onClicked: newProjectDialogId.open()
				useTooltip: true
				tooltip: qsTr("Create new project")
			}
			QsToolButton{
				id:openProjectId
				implicitHeight: 24
				imageSource: "qrc:/icons/open.png"
				onClicked: openProjectDialogId.open()
				useTooltip: true
				tooltip: qsTr("Open project")
			}
			QsToolButton{
				enabled: rootId.isProjectOpen
				id:saveProjectId
				implicitHeight: 24
				imageSource: "qrc:/icons/save.png"
				onClicked: saveProjectDialogId.open()
				useTooltip: true
				tooltip: qsTr("Save project")
			}

			spacing: 8
			Item{
				Layout.fillWidth: true
			}
			// ############ begin tool view tabs "#######################
			QsTabBar{
				implicitHeight: 24
				id: toolsTabId
				Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
				currentIndex: 0
				QsTabButton{
					id:verifyTabId
					text:qsTr("Verification")
					toolTip: hotkeyVerifyId.sequence
					useToolTip: true
				}

				QsTabButton{
					id:verifyResultTabId
					text:qsTr("VerificationResults")
					toolTip: hotkeyVerifyResutId.sequence
					useToolTip: true
				}
				QsTabButton{
					id:simulationTabId
					text: qsTr("Simulation")
					toolTip: hotkeySimId.sequence
					useToolTip: true
				}
				// ############ end tool view tabs "#######################
			}
		}

	}
	QsNewProjectDialog{
		id: newProjectDialogId
		x: ( qspinAppId.width - width ) *0.5
		y: (qspinAppId.height -height ) *0.5
		onAccepted: rootId.createProject(filepath)
	}
	FileDialog{
		id:openProjectDialogId
		title: qsTr("Open project")
		onAccepted: rootId.openProject(fileUrl)
		nameFilters: ["Promela (*.pml)"]
	}
	FileDialog{
		id:saveProjectDialogId
		title: qsTr("Save project")
		selectExisting: false
		nameFilters: ["Promela (*.pml)"]
		onAccepted: rootId.saveProject(fileUrl)
	}
	Shortcut{
		sequence: StandardKey.SaveAs
		onActivated: saveProjectDialogId.open()
	}
	Shortcut{
		sequence: StandardKey.Open
		onActivated: openProjectDialogId.open()
	}
	Shortcut{
		sequence: StandardKey.New
		onActivated: newProjectDialogId.open()
	}
	Shortcut {
		id: hotkeyVerifyId
		sequence: "Ctrl+8"
		onActivated: verifyTabId.checked ? toolsTabId.currentIndex =-1 : toolsTabId.currentIndex =0
		}
	Shortcut {
		id:hotkeyVerifyResutId
		sequence: "Ctrl+9"
		onActivated: verifyResultTabId.checked ? toolsTabId.currentIndex =-1 : toolsTabId.currentIndex =1
		}
	Shortcut {
		id:hotkeySimId
		sequence: "Ctrl+0"
		onActivated: simulationTabId.checked ? toolsTabId.currentIndex =-1 : toolsTabId.currentIndex =2
	}
	Shortcut{
		sequence: "Ctrl+Tab"
		onActivated: toolsTabId.currentIndex = (toolsTabId.currentIndex +1) %3
	}


}
