
import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import Qt.labs.platform 1.0
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QSpin.Qml.Views 1.0
import QtQuick.Dialogs 1.3
ApplicationWindow {
	id:qspinAppId
	visible: true
	//flags:  Qt.Window | Qt.FramelessWindowHint
	width: 1600
	height: 900
	minimumHeight: 764
	minimumWidth: 1024
	visibility: Window.Maximized
	title: qsTr("QSpin+")
	background: Rectangle{
		color: QsStyle.general.background
		border.color: QsStyle.general.background
		border.width: 1

	}

	//################## begin menu bars ################################

	header:Rectangle{
		implicitHeight: 32
		anchors.left: parent.left
		anchors.right: parent.right
		border.color: QsStyle.general.border
		border.width: 1
		gradient: Gradient{
			id: g
			GradientStop{ position: 0; color: QsStyle.general.menubarGradiant0 }
			GradientStop{ position: 1; color: QsStyle.general.menubarGradiant1}
		}
		//tool bar content
		RowLayout{
			id:toolbarId
			anchors{
				fill: parent
				leftMargin: 10
				rightMargin: 10
				//left: parent.left
				//right: parent.right
				//top: parent.top

			}
			spacing: 8

			// selection tabs
			Item{
				Layout.fillWidth: true
			}
			// ############ begin tool view tabs "#######################
			QsTabBar{
				id: toolsTabId
				Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
				QsTabButton{
					text:verifyViewId.header
				}

				QsTabButton{
					text:simulationViewId.header
				}
				QsTabButton{
					text: verifyResultViewId.header
				}
				// ############ end tool view tabs "#######################
			}


		}
	}

	footer: ToolBar{
		id:footerBarId
		implicitHeight: 32
		anchors.left: parent.left
		anchors.right: parent.right
		leftPadding:8
		rightPadding: 8
		background: Rectangle{
			gradient: Gradient{
				GradientStop{ position: 0; color: QsStyle.general.menubarGradiant0 }
				GradientStop{ position: 1; color: QsStyle.general.menubarGradiant1}
			}
			border.color: QsStyle.general.border
			border.width: 1
		}
		Row{
			anchors.fill: parent
			QsTabBar{
				id:footerTabsId
				anchors.verticalCenter: parent.verticalCenter
				implicitHeight: 24
				property int checkedMode:0
				property bool anyChecked: false
				spacing: 8
				Repeater{
					model:["Verification status","Console", "Interactive Choices"]
					QsTabButton{
						implicitHeight: 24
						checkable: true
						text: qsTr(modelData)

					}
				}
			}
		}
	}
	// ############### end menu bars

	// ####### begin worspace
	RowLayout{
		id: worskpaceLayoutId
		anchors.fill: parent
		spacing: 0
		// text editor area
		ColumnLayout{
			id:leftHalfWindowId

			spacing: 0

			QsCodeEditor{
				id: codeEditiorId
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.minimumHeight: 500
				Layout.minimumWidth: 300
				syntaxHighlighter: promelaHighlighterId
				tabIndentSize: QsStyle.promelaEditor.tabIndents
				foreground: QsStyle.promelaEditor.foreground
				background: QsStyle.promelaEditor.background
				font{
					family: QsStyle.promelaEditor.fontFamily
					pointSize: QsStyle.promelaEditor.pointSize
				}

				QsPromelaSyntaxHighlighter{
					id:promelaHighlighterId
					colors: QsStyle.promelaEditor.syntaxHighlighter
				}

			}

			// popup menu
			QsToolViews{
				Layout.fillWidth: true
				implicitHeight: 200
				selectedTabIndex: footerTabsId.currentIndex
				QsSpinQueueView{

				}

				QsButton{
					text: "Console"
				}
				QsButton{
					text: "Interactive"
				}
				QsButton{
					text: "Interactive"
				}
			}

		}
		QsDivider{
			oritentation: Qt.Vertical
			Layout.fillHeight: true
			color:  QsStyle.general.border
		}
		QsVerificationView{
			id:verifyViewId
			Layout.fillHeight: true
			visible: toolsTabId.currentItem.text === header
			readonly property string header: "Verification"
		}
		QsSimulationView{
			id:simulationViewId
			readonly property string header: "Simulation"
			Layout.fillHeight: true
			visible: toolsTabId.currentItem.text === header
			//			visible: toolsTabId.currentIndex===1
		}
		QsInteractiveView{
			id:verifyResultViewId
			readonly property string header: "Verification Results"
			Layout.fillHeight: true
			visible: toolsTabId.currentItem.text === header
			//			visible: toolsTabId.currentIndex===2
		}

	}

	// dialogs
	QsNewProjectDialog{
		id: newProjectDialogId
		x: ( qspinAppId.width - width ) *0.5
		y: (qspinAppId.height -height ) *0.5
		onAccepted: console.debug("implement create project")
	}
	FileDialog{
		id:openProjectDialogId
		title: qsTr("Open project")
		onAccepted: console.debug("implement open project")
	}
	FileDialog{
		id:saveProjectDialogId
		title: qsTr("Save project")
		selectExisting: false
		onAccepted: console.debug("implement save project")
	}
}
