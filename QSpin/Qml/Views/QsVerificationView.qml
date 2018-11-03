import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QtQml.Models 2.3
Item {

	id: verifySettings
	property int codeAreaWidth: 500
	property int codeAreaHeight: 250

	QsVerifyHandler{
		id:verifyHandlerId
		currentIndex: configSelectorId.currentIndex
	}
	MouseArea{
		anchors.fill: currentVerifyConfigId

		onWheel:{
			if(wheel.angleDelta.y<0)
				settingsScrollbarId.increase()
			else settingsScrollbarId.decrease()
		}
	}

	QsVerifySettingsGroup{
		id:currentVerifyConfigId
		y:-settingsScrollbarId.position *height
		active:  verifyHandlerId.currentConfiguration
		onItemRemoved: verifyHandlerId.removeConfiguration(item)
	}
	ScrollBar{
		id:settingsScrollbarId
		hoverEnabled: true
		active: hovered || pressed
		orientation: Qt.Vertical
		size: verifySettings.height / currentVerifyConfigId.height
		anchors.left: currentVerifyConfigId.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		policy: ScrollBar.AlwaysOn

	}

	// list of configurations
	ColumnLayout{
		id:farLeftColumnId
		anchors{
			right: parent.right
			bottom: parent.bottom
			top: parent.top
			left: settingsScrollbarId.right
			leftMargin: 4
		}


		QsDivider{
			oritentation: Qt.Horizontal
			Layout.fillWidth: true
			color: QsStyle.general.border
		}

		ListView{
			id: configSelectorId
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			Layout.fillWidth: true
			Layout.preferredHeight: contentHeight
			topMargin: 5
			header:QsHeader{
				text: qsTr("Configurations")

			}
			model:visualModelId
		}

		Item{
			id:addConfigurationId
			Layout.fillWidth: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			implicitHeight: 32
			TextInput{
				readonly property string defaultVal: qsTr("Add new Configuration")
				property bool canceling: false
				anchors.centerIn: parent
				anchors.margins: 4
				selectByMouse: true

				onActiveFocusChanged: {
					if(activeFocus) selectAll();
					else{
						text = defaultVal
						focus = false
					}
				}
				font.family: "candara"
				font.pointSize: 12
				onAccepted: {
					if(!canceling){
						verifyHandlerId.addConfiguration(text)
						verifyHandlerId.setCurrentIndex(configSelectorId.count-1)
					}
					canceling =false
					text = defaultVal
					activeFocus =false
				}
				Keys.onEscapePressed: {
					canceling = true
					focus= false
				}

				color: QsStyle.general.foreground
				text: defaultVal
			}
			QsDivider{
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: parent.bottom
				anchors.bottomMargin: 1
				oritentation: Qt.Horizontal
				color: QsStyle.general.border
			}
		}
		Item{
			Layout.fillHeight: true
		}
	}
	//vertical seperator
	QsDivider{
		anchors.left: farLeftColumnId.left
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		oritentation: Qt.Vertical
		color: QsStyle.general.border
	}
	// list model Components
	Component{
		id:listViewDelegateId
		Item{
			id:listItemId
			implicitHeight: 40
			anchors.left: parent.left
			anchors.right: parent.right
			property int idx: index
			property int visualIdx: listItemId.DelegateModel.itemsIndex// listItemId.DelegateModel.itemsIndex
			Component.onCompleted: console.debug("config list-> idx: "+idx+", visualIdx: "+visualIdx)
			RowLayout{
				//implicitHeight: 45
				id:itemLayoutId
				anchors.fill: parent
				anchors.leftMargin: 8
				anchors.rightMargin: 8
				//anchors.left: parent.left
				//anchors.right: parent.right

				spacing: 8
				TextInput{
					Layout.fillWidth: true
					padding: 5
					//leftPadding: 10
					activeFocusOnPress: false
					//background: null
					property bool canceling: false
					id: txtDelegateId
					text: model.name_role
					color: QsStyle.button.foreground
					font.pointSize: 12
					readOnly: false
					Keys.onEscapePressed:{
						canceling = true
						focus = false
					}
					onEditingFinished: {
						if(canceling)
							text = model.name_role
						else{
							model.name_role = text
							focus = false
						}
						canceling =false
					}


					MouseArea{
						id:itemSelId
						enabled: !parent.activeFocus
						visible: enabled
						acceptedButtons: Qt.LeftButton | Qt.LeftButton
						anchors.fill: parent
						onClicked:{
							listItemId.ListView.view.currentIndex =listItemId.idx
						}
						onDoubleClicked: {
							parent.forceActiveFocus()
							parent.selectAll()
						}

					}
				}

				Image {
					id:modeTypeIconId
					property int size: 24
					Layout.preferredWidth: size
					Layout.preferredHeight:size
					Layout.maximumHeight: size
					Layout.maximumWidth: size

					source: "qrc:/icons/close.png"
					state: model.verifyMode_role
					states:[
						State {	name: Arg.SafetyMode;	PropertyChanges { target: modeTypeIconId; source:"qrc:/icons/Safty.png" }},
						State {name: Arg.ProgressMode;	PropertyChanges { target: modeTypeIconId; source:"qrc:/icons/Progress.png" }},
						State {name: Arg.AccepanceMode;	PropertyChanges { target: modeTypeIconId; source:"qrc:/icons/Acceptance.png" }}
					]
					//onStateChanged: console.debug("state changed")
					//Component.onCompleted: console.debug(model.saftyMode_role)
					Connections{
						target: model.saftyMode_role
					}
				}

			}
			QsDivider{
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: parent.bottom
				anchors.bottomMargin: 1
				color: QsStyle.general.border
			}

		}

	}

	DelegateModel{
		id:visualModelId
		model: verifyHandlerId
		delegate: listViewDelegateId
	}
}
