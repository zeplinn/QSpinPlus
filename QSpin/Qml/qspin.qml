
import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
//import Qt.labs.platform 1.0
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QSpin.Qml.Views 1.0
ApplicationWindow {
	id:qspinAppId
	visible: true
	//flags:  Qt.Window | Qt.FramelessWindowHint
	width: 1400
	height: 764
	minimumHeight: 1024
	minimumWidth: 1280
	visibility: Window.Maximized
	title: qsTr("QSpin+")
	background: Rectangle{
		color: QsStyle.general.background
		border.color: QsStyle.general.background
		border.width: 1

	}
onClosing:promelaHandlerId.closeExistingDocumet()

	//################## begin menu bars ################################

	header: QsTopToolBar{
		id:topToolBarId
		isProjectOpen: promelaHandlerId.isOpen
		undoButton{
			enabled: codeEditiorId.documentHandler.canUndo;
			onClicked: codeEditiorId.documentHandler.undo()
		}
		redoButton{
			enabled: codeEditiorId.documentHandler.canRedo;
			onClicked: codeEditiorId.documentHandler.redo()
		}
		onOpenProject: {
			promelaHandlerId.openDocument(fileUrl)
		}
		onSaveProject: {
			promelaHandlerId.saveDocument(fileUrl)
		}
		onCreateProject: promelaHandlerId.createDocument(filepath)
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
		QsTabBar{
			id:footerTabsId
			anchors.verticalCenter: parent.verticalCenter
			QsTabButton{
				text: qsTr("Verification queue")
			}
			QsTabButton{
				text: qsTr("Console")
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
		Item{

			Layout.fillHeight: true
			Layout.fillWidth: true
			ColumnLayout{
				id:leftHalfWindowId
				anchors.fill: parent
				spacing: 0

				QsPromelaHandler{
					id:promelaHandlerId
					editor: codeEditiorId.documentHandler
					onInValidPromelaFile: {
						msgDialog.text= filepath
						msgDialog.open()
					}
				}
				QsCodeEditor{
					enabled: promelaHandlerId.isOpen
					readonly: !promelaHandlerId.isEditable
					id: codeEditiorId
					Layout.fillHeight: true
					Layout.fillWidth: true
					Layout.minimumWidth: 150
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


				QsSpinQueueView{
					id:tabBtn
					visible: footerTabsId.currentIndex === 0
					Layout.fillWidth: true
					Layout.preferredHeight: height

				}
				QsConsoleView{
					Layout.preferredHeight: 400
					Layout.fillWidth: true
					visible: footerTabsId.currentIndex === 1
				}

			}

		}
		QsDivider{
			oritentation: Qt.Vertical
			Layout.fillHeight: true
			color:  QsStyle.general.border
		}

		// right hand tabs
		QsVerificationView{
			id:verifyViewId
			Layout.fillHeight: true
			visible: topToolBarId.isVerifyTabSelected
			readonly property string header: "Verification"
		}
		QsSimulationView{
			id:simulationViewId
			readonly property string header: "Simulation"
			Layout.fillHeight: true
			visible: topToolBarId.isSimulationTabSelected
			//			visible: toolsTabId.currentIndex===1
		}
		QsVerificationResultView{
			id:verifyResultViewId
			readonly property string header: "Verification Results"
			Layout.fillHeight: true
			visible: topToolBarId.isVerifyResultTabSelected
			//			visible: toolsTabId.currentIndex===2
		}
		// end right hand tab size

	}

	// Shortcuts
	Item{


		Shortcut{
			enabled: codeEditiorId.documentHandler.canUndo
			sequence: StandardKey.Undo
			onActivated: codeEditiorId.documentHandler.undo()
		}
		Shortcut{
			enabled: codeEditiorId.documentHandler.canRedo
			sequence: StandardKey.Redo
			onActivated: codeEditiorId.documentHandler.redo()
		}

		Shortcut{
			enabled: codeEditiorId.documentHandler.canUndo
			sequence: "Ctrl+s"
			onActivated:{
				console.debug("am save hit")
				promelaHandlerId.saveExistingDocument()
			}
		}

		Shortcut {
			id: hotkeyVerifyId
			sequence: "Ctrl+1"
			onActivated: footerTabsId.currentIndex===0 ? footerTabsId.currentIndex =-1 : footerTabsId.currentIndex =0
		}
		Shortcut {
			id:hotkeyConsoleId
			sequence: "Ctrl+2"
			onActivated: footerTabsId.currentIndex===1 ? footerTabsId.currentIndex =-1 : footerTabsId.currentIndex =1
		}




	}
	Dialog{
		id:msgDialog
		property alias text: msgtextLable.text
		x: (parent.width-width)*0.5
		y: (parent.height-height)*0.5
		padding: 0
		Rectangle{
			implicitWidth: childrenRect.width
			implicitHeight: childrenRect.height
			color: QsStyle.general.background
			border.color: QsStyle.general.border
			border.width: 2
			ColumnLayout{
				implicitWidth: 400
				QsText{
					padding: 5
					id:msgtextLable; Layout.fillWidth: true
				}
				QsButton{
					text: qsTr("close")
					Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
					onClicked: close();
				}
			}

		}
		onVisibleChanged: if(!visible) text=""
	}

}
