import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QtQml.Models 2.3
QsPane {
    padding: 0
    id: verifySettings
    property int codeAreaWidth: 500
    property int codeAreaHeight: 250
    QsVerifyHandler{
        id:verifyHandlerId
		currentIndex: configSelectorId.currentIndex
	}

	RowLayout{
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.margins: 0
		spacing: 0
		QsVerifySettingsGroup{
			Layout.fillHeight: true
			Layout.minimumWidth: implicitWidth
			id:currentVerifyConfigId
			active: dummyConfigId
			enabled:false
			onItemRemoved: verifyHandlerId.removeConfiguration(item)
			states:State{
				when: verifyHandlerId.isProjectOpen && configSelectorId.count !== 0
				PropertyChanges {
					target: currentVerifyConfigId
					active:  verifyHandlerId.currentConfiguration
					enabled: true
				}
            }
            VerificationConfiguration{
                id:dummyConfigId
            }
        }
        QsDivider{
            oritentation: Qt.Vertical
            Layout.fillHeight: true
            color: QsStyle.general.border
        }
        ColumnLayout{
            id:farLeftColumnId
			spacing: 4
			Item{
				height: btnQueueId.height
				Layout.fillWidth: true
			QsButton{
				id:btnQueueId
				enabled: verifyHandlerId.isProjectOpen
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.leftMargin: 4
				anchors.rightMargin: 4
				text: qsTr("Add toQueue")
				onClicked: verifyHandlerId.queueVerification(verifyHandlerId.currentConfiguration)
				Layout.fillWidth: true
			}
			}

			QsDivider{
				oritentation: Qt.Horizontal
				Layout.fillWidth: true;
				color: QsStyle.general.border
			}

            ListView{
                id: configSelectorId
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                implicitWidth: 250
                boundsBehavior: Flickable.StopAtBounds
                Layout.preferredHeight: contentHeight+5
                highlight: highlightId
                highlightFollowsCurrentItem: true
                topMargin: 5
                header:QsHeader{
                    text: qsTr("Configurations")
                }
				model:visualModelId
            }
            // ################# begin add configuration #################
            Item{
                id:addConfigurationId
				enabled: verifyHandlerId.isProjectOpen
				opacity: enabled ? 1 : 0.2
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
                    font.pointSize: 10
                    onAccepted: {
                        if(!canceling){
							verifyHandlerId.addConfiguration(text)
							verifyHandlerId.setCurrentIndex(configSelectorId.count-1)
                        }
                        canceling =false
                        text = defaultVal
                       // focus =false
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
            //############## end add configuration ###################
            // filler to push avoid vertical centering of objects
            Item{
                Layout.fillHeight: true
            }
        }

    }
    // ####### begin components #####################################################
    Component {
        id: highlightId
        Rectangle {

            opacity: 0.2
            //width: configSelectorId.currentItem.width;
            width: configSelectorId.width
            height:40// configSelectorId.currentItem.height
            color: QsStyle.general.hovered;
            //y: configSelectorId.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }
    Component{
        id:listViewDelegateId
        Item{
            id:listItemId

            implicitHeight: 40
            implicitWidth: 250
            property int idx: index
            property int visualIdx: listItemId.DelegateModel.itemsIndex
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

                    font.pointSize: 10
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
                    Connections{
                        target: model.saftyMode_role
                    }
                }
            }
            QsDivider{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
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

