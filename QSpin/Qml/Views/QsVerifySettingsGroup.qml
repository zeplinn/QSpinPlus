import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
Item {
	id: rootId
	property alias active: itemRefId.reference
	implicitHeight: 800
	implicitWidth: childrenRect.width
	signal itemRemoved(VerificationConfiguration item)
	property int hSpacing: 15
	QsVerifySettingsGroupHandler{
		id: itemRefId
	}
	// configurations


	//########### begin Configuration section ######################
	Row{
		spacing: 8
		padding: 4
		anchors.top: parent.top
		anchors.bottom: commentSectionId.top
		Item{
			enabled: active !== null
			id:configSecId
			clip: true
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			implicitWidth: childrenRect.width
			MouseArea{
				anchors.fill: layout
				onWheel: {
					if	(wheel.angleDelta.y<0)		configVbarID.increase()
					else if(wheel.angleDelta.y>0)	configVbarID.decrease()

				}
			}
			ColumnLayout{
				id:layout
				y: -configVbarID.position*height
				//enabled: rootId.active !== null
				//		anchors.fill: parent
				spacing: 10
				// ########### header section ############# row 1
				RowLayout{
					Image {
						id: titleIconId
						Layout.preferredHeight: 48
						Layout.preferredWidth: 48
						source: "qrc:/icons/close.png"
						state: modeTabBarId.checkedMode
						states:[
							State {	name: Arg.SafetyMode;
								PropertyChanges { target: titleIconId; source:"qrc:/icons/Safty2x.png" }
								PropertyChanges {target: itemRefId; item.safetyMode.checked: true}
							},
							State {	name: Arg.ProgressMode;
								PropertyChanges { target: titleIconId; source:"qrc:/icons/Progress2x.png" }
								PropertyChanges {target: itemRefId; item.progressMode.checked: true}
							},

							State {	name: Arg.AccepanceMode;
								PropertyChanges { target: titleIconId; source:"qrc:/icons/Acceptance2x.png" }
								PropertyChanges {target: itemRefId; item.acceptanceMode.checked: true}
							}
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
				// ############# verfication Modes ######################## row 2
				TabBar{
					id:modeTabBarId
					opacity: enabled ? 1: 0.2
					readonly property int sharedWidth: 150
					property int checkedMode: Arg.SafetyMode
					currentIndex: 0
					onCurrentIndexChanged: {
						var item = currentIndex;
						switch(currentIndex){
						case 0: item = Arg.SafetyMode; break
						case 1: item = Arg.ProgressMode; break
						case 2: item = Arg.AccepanceMode; break
						}
						checkedMode = item
						itemRefId.item.updateSelectedVerifyMode(item)
					}
					background: null
					Repeater{
						model: [itemRefId.item.safetyMode
							,itemRefId.item.progressMode
							,itemRefId.item.acceptanceMode]
						TabButton {
							id:btnId
							//implicitWidth: childrenRect.width
							implicitWidth: 150
							implicitHeight: 24
							leftPadding: 4
							rightPadding: 4
							text: modelData.name
							contentItem: QsText{
								id: txtId
								text: btnId.text
								verticalAlignment: Text.AlignVCenter
								horizontalAlignment: Text.AlignHCenter
								color: hovered ? QsStyle.general.hovered: QsStyle.button.foreground

							}

							background: Rectangle{
								property color selcolor: selColorF()
								function selColorF(){
									var c = 47/256
									return Qt.rgba(c,c,c,1)
								}

								color: checked ? QsStyle.button.pressed : "transparent"
								border.width:  checked ? 1 : 0
								border.color:  QsStyle.button.border
								radius: 2

							}
						}
					}
				}

				QsDivider{
					oritentation: Qt.Horizontal
					Layout.fillWidth: true
					color: QsStyle.general.border
				} // group begin
				QsText{
					leftPadding: 4; text: qsTr("Custom settings")
					MouseArea{anchors.fill: parent; onClicked: customVerifySetings.visible = !customVerifySetings.visible}
				}
				ColumnLayout{
					id:customVerifySetings
					readonly property int offset: 4
					visible: true
					QsButton{
						text:qsTr("check verification Strings")
						Layout.fillWidth: true
						onClicked: {
							var cmds = itemRefId.item.getCurrentCommandsAsStrings();
							// list [] = {spin, gcc, pan } // need fixing for a more robust solution later
							argumentViewerId.spin = cmds[0]
							argumentViewerId.gcc = cmds[1]
							argumentViewerId.pan = cmds[2]
						}
					}

						Dialog{
							id: argumentViewerId
							property string spin: ""
							property string gcc: ""
							property string pan: ""
							modal:true
							Rectangle{
								color: QsStyle.general.background
								border.color: QsStyle.general.border
								border.width: 2
								implicitHeight: childrenRect.height
								implicitWidth: childrenRect.width

								ColumnLayout{
									QsText{	text: "spin: " + argumentViewerId.spin; Layout.fillWidth: true}
									QsText{	text: "gcc:  " + argumentViewerId.gcc; Layout.fillWidth: true}
									QsText{	text: "pan:  " + argumentViewerId.spin; Layout.fillWidth: true}
									QsButton{text: qsTr("Close"); Layout.fillWidth: true; onClicked: argumentViewerId.close()}
							}
								Keys.onEscapePressed: close()
							}
						}

						RowLayout{
							spacing:8
							QsText{leftPadding: 4;text: qsTr("spin:")}
							Rectangle{
								Layout.fillWidth: true
								color: Qt.darker(QsStyle.general.background,1.1)
								implicitHeight: 24
								TextInput{
									anchors.fill: parent
									selectByMouse: true

									onActiveFocusChanged: {
										if(activeFocus) selectAll();
										else{
											focus = false
										}
									}
									font.family: "candara"
									font.pointSize: 10
									onAccepted: {
										canceling =false
										text = defaultVal
										// focus =false
									}
									Keys.onEscapePressed: {
										canceling = true
										focus= false
									}

									color: QsStyle.general.foreground
								}
							}
						}
						RowLayout{
							QsText{leftPadding: 4;text: qsTr("gcc:")}
							spacing: 9
							Rectangle{
								Layout.fillWidth: true
								color: Qt.darker(QsStyle.general.background,1.1)
								implicitHeight: 24
								TextInput{
									anchors.fill: parent
									selectByMouse: true

									onActiveFocusChanged: {
										if(activeFocus) selectAll();
										else{
											focus = false
										}
									}
									font.family: "candara"
									font.pointSize: 10
									onAccepted: {
										canceling =false
										text = defaultVal
										// focus =false
									}
									Keys.onEscapePressed: {
										canceling = true
										focus= false
									}

									color: QsStyle.general.foreground
								}
							}
						}
						RowLayout{
							QsText{leftPadding: 4;text: qsTr("pan:")}
							spacing: 9
							Rectangle{
								Layout.fillWidth: true
								color: Qt.darker(QsStyle.general.background,1.1)
								implicitHeight: 24
								TextInput{
									anchors.fill: parent
									selectByMouse: true

									onActiveFocusChanged: {
										if(activeFocus) selectAll();
										else{
											focus = false
										}
									}
									font.family: "candara"
									font.pointSize: 10
									onAccepted: {
										canceling =false
										text = defaultVal
										// focus =false
									}
									Keys.onEscapePressed: {
										canceling = true
										focus= false
									}

									color: QsStyle.general.foreground
								}
							}
						}

					}
					QsDivider{
						oritentation: Qt.Horizontal
						Layout.fillWidth: true
						color: QsStyle.general.border
					} // group end

					// spin optimazations -o[1..6] ##################### row 3
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
					}
					// begin checkbox section #################
					GridLayout{
						columns: 2
						rowSpacing: 8
						columnSpacing: 8
						Repeater{
							property alias c: rootId.active
							model:[c.safety, c.sfh, c.weakFairness, c.noFair, c.noReduce
								, c.space, c.np, c.collapse,c.bfs, c.bfs_disk]
							QsButton{
								Layout.fillWidth: true
								useToolTip: true
								toolTip: modelData.argument()
								enabled: modelData.enabled
								onCheckedChanged: modelData.setChecked(checked)
								checkable: true
								checked: modelData.checked
								text:modelData.name
							}
						}

					}
					// ############ end checkbox section ########################################

					// ########### begin spin boxsection ##########################
					Repeater{
						model: [itemRefId.item.bfs_disk_limit, itemRefId.item.bfs_limit,
							itemRefId.item.hc, itemRefId.item.memLimit, itemRefId.item.vectorSZV,
							itemRefId.item.hashSize, itemRefId.item.searchDepth, itemRefId.item.timeLimit]
						QsSpinBox{
							Layout.fillWidth: true
							useToolTip: true
							toolTip: modelData.argument()
							enabled: modelData.enabled
							checked: modelData.checked
							onCheckedChanged: modelData.setChecked(checked)
							label: modelData.name
							value: modelData.commandValue
							from:modelData.minValue
							to: modelData.maxValue

						}
					}
					// ########### end spin box section

					// ##########ltl text area begin ###############

					ColumnLayout{
						id: ltlSectionId
						QsText{
							text: qsTr("LTL:"); color: QsStyle.general.foreground
							Layout.fillWidth: true
						}

						Rectangle{
							id: ltlTxtborderId
							Layout.fillWidth: true
							Layout.minimumHeight:  150

							Layout.fillHeight: true
							color: "transparent"
							border.color: QsStyle.general.border
							border.width: 1
							radius: 3
							QsCodeEditor{
								id:ltlId
								anchors.fill: parent
								anchors.margins: 2
							}

						}
					}
					// ############# end ltl TextArea ###############
				}
			}


			// ######### begin scrollbar #################################
			QsScrollBar{
				id:configVbarID
				anchors.top: parent.top
				hoverEnabled: true
				active: hovered || pressed
				anchors.bottom: parent.bottom
				size: configSecId.height/layout.height > 1? 1 : configSecId.height/layout.height
				orientation: Qt.Vertical
				policy: QsScrollBar.AlwaysOn
			}
			// ############## end ScrollBar ####################################

		}
		// ########## end Configurations section #########################


		// ############ begin comment section #############################
		Item{
			id:commentSectionId
			anchors.left: parent.left
			anchors.bottom: parent.bottom
			anchors.rightMargin: 8
			//implicitWidth: parent.implicitWidth
			anchors.right: parent.right
			anchors.margins: 4
			implicitHeight: childrenRect.height
			height: commentHeaderId.height+commmentAreaId.height




			QsHeader{
				id:commentHeaderId
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: commmentAreaId.top
				//anchors.top: parent.top
				text: qsTr("Comments")
			}

			Rectangle{
				id: commmentAreaId
				implicitHeight: 150
				visible: false
				height: visible ?150 : 0
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: parent.bottom
				border.color: QsStyle.general.border
				border.width: 1
				radius: 3
				color: "transparent"
				QsCodeEditor{
					anchors.fill: parent
					anchors.margins: 2
				}


			}
			MouseArea{
				anchors.fill: commentHeaderId
				onClicked: commmentAreaId.visible = !commmentAreaId.visible
			}
		}
		QsDivider{
			anchors.left: parent.left
			anchors.right: parent.right
			oritentation: Qt.Horizontal
			anchors.top: commentSectionId.top
			anchors.topMargin: 3
			color: QsStyle.general.border
		}
		// ################ end comment section ############################

	}
