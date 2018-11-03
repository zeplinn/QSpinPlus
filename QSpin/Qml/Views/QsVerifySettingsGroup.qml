import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
QsPane {
	id: rootId
	property VerificationConfiguration active: null
	background: null
	signal itemRemoved(VerificationConfiguration item)

	property int hSpacing: 15
	ColumnLayout{
		enabled: rootId.active !== null
//		anchors.fill: parent
		id:layout
		spacing: 10

		RowLayout{
			Image {
				id: titleIconId
				Layout.preferredHeight: 48
				Layout.preferredWidth: 48
				source: "qrc:/icons/close.png"
				state: modeRowId.checkedMode
				states:[
					State {	name: Arg.SafetyMode;	PropertyChanges { target: titleIconId; source:"qrc:/icons/Safty2x.png" }},
					State {	name: Arg.ProgressMode;	PropertyChanges { target: titleIconId; source:"qrc:/icons/Progress2x.png" }},
					State {	name: Arg.AccepanceMode;PropertyChanges { target: titleIconId; source:"qrc:/icons/Acceptance2x.png" }}
				]
			}

			QsHeader{
				id:headerId
				text: rootId.active.name

			}
			Item {
				id: emptySpace
				Layout.fillWidth: true
			}
			QsToolButton{
				imageSource: "qrc:/icons/close.png"
				onClicked: rootId.itemRemoved(rootId.active)
			}

		}


		// verfication Modes #########################
		Item{
			id:verificationModeId
			implicitWidth: childrenRect.width
			implicitHeight: childrenRect.height
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
			ButtonGroup{
				id:btnModeGroupId
			}

			Row{
				id:modeRowId
				spacing: 8
				readonly property int sharedWidth: 150
				property int checkedMode: Arg.SafetyMode
				Repeater{
					property alias c: rootId.active
					model: [c.safetyMode
						,c.progressMode
						,c.acceptanceMode]

					QsButton{
						id:saftyModeId
						checkable: true
						//readonly property bool selected:modeRowId.checkedMode === modelData.command
						checked: modelData.checked
						onCheckedChanged: if(checked){
											  modeRowId.checkedMode = modelData.command
											  rootId.active.updateSelectedVerifyMode(modelData.command)
										  }
						implicitWidth: 150
						text: modelData.name
						ButtonGroup.group: btnModeGroupId
//						onClicked:{
//							modeRowId.checkedMode = modelData.command
////							modelData.checked = modeRowId.checkedMode === modelData.command
//						}
					}
				}
			}
		}

		// memory compression ############################
		QsComboBox{
			Layout.fillWidth: true
			property alias c: rootId.active
			model: ["no memory compression","Collapse","HC 0","HC 1","HC 2","HC 3"]
		}


		// spin optimazations -o[1..7] #####################
		RowLayout{
			id:optimizationGroupId
			QsText{
				Layout.fillWidth: true
				text: qsTr("Optimizations")
			}
			Repeater{
				property alias c: rootId.active
				model: [c.o1, c.o2, c.o3, c.o4, c.o5, c.o6 ]
				QsButtonSquare{
					checked: modelData.checked
					checkable: true
					useToolTip: true
					toolTip: modelData.name

					text: qsTr("%1").arg(1+index)
				}
			}

			/*			QsButtonSquare{
				checkable: true
				text: qsTr("1")
			}
			QsButtonSquare{
				checkable: true
				text: qsTr("2")
			}
			QsButtonSquare{
				checkable: true
				text: qsTr("3")
			}
			QsButtonSquare{
				checkable: true
				text: qsTr("4")
			}
			QsButtonSquare{
				checkable: true
				text: qsTr("5")
			}
			QsButtonSquare{
				checkable: true
				text: qsTr("6")
			}*/
			//			QsButtonSquare{
			//				checkable: true
			//				text: qsTr("7")
			//			}
		}

		// first checkbox section #################
		GridLayout{
			columns: 2
			rowSpacing: 8
			columnSpacing: 8
			Repeater{
				property alias c: rootId.active
				model:[c.safety, c.sfh, c.weakFairness, c.noFair, c.noReduce
					, c.space, c.np, c.bfs, c.bfs_disk]
				QsButton{
					Layout.fillWidth: true
					checkable: true
					checked: modelData.checked
					text:modelData.name
				}
			}

			/*			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("Optimize safety")
			}

			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("SFH")
			}

			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("Weak fairness")
			}



			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("Remove Weak fairnes code")
			}



			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("No partial reduction algorithm")
			}



			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("Optimize for Space")
			}

			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("Non-progress cycles")
			}

			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("Breadth First Search (BFS)")
			}



			QsButton{
				Layout.fillWidth: true
				checkable: true
				text:qsTr("BFS disk")
			}
		*/
		}

		// first spin box section ##########################
		Repeater{
			property alias c: rootId.active
			model: [c.bfs_disk_limit, c.bfs_limit, c.memLimit, c.vectorSZV, c.hashSize, c.searchDepth, c.timeLimit]
			QsSpinBox{
				Layout.fillWidth: true
				label: modelData.name
				value: modelData.commandValue
				from:0
				to: 2000000000

			}
		}

//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("BFS disk limit")

//		}


//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("BFS limit")

//		}


//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("Maximum memory used")

//		}


//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("State vector size")
//		}



//		QsSpinBox{
//			id: hashValueId
//			Layout.fillWidth: true
//			label: qsTr("Hash value")

//		}
//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("Search depth")

//		}
//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("Maximum memory usage")

//		}
//		QsSpinBox{
//			Layout.fillWidth: true
//			label: qsTr("Time limit")

//		}
		QsText{
			text: qsTr("LTL:"); color: QsStyle.general.foreground
		}
		// QsDivider{Layout.fillWidth: true; color: QSpinStyle.highlightColor}
		Rectangle{
			Layout.fillWidth: true
			Layout.minimumHeight: 100

			Layout.fillHeight: true
			color: "transparent"
			border.color: QsStyle.general.border
			border.width: 1
			radius: 3
			QsTextEdit{
				id:ltlId
				anchors.fill: parent
			}

		}
		// QsDivider{Layout.fillWidth: true; color: QSpinStyle.highlightColor}
		//        }




		QsDivider{
			Layout.fillWidth: true
		}

		QsHeader{
			Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
			text: qsTr("Comments")
			Layout.fillWidth: true
		}
		Rectangle{

			Layout.fillWidth: true
			Layout.minimumHeight: 200
			border.color: QsStyle.general.border
			border.width: 1
			radius: 3
			color: "transparent"

		}

	}
}
