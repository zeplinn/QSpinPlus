import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QtQml.Models 2.3
Item {

    id: verifySettings
    property int codeAreaWidth: 500
    property int codeAreaHeight: 250
//    QsVerifyResults{
//        id:resultsId
//        anchors.left: parent.left
//        anchors.bottom: parent.bottom
//    }
    property var configs: ["config 1","config 2","config 3","config 4"]
    ListView{
        id:configDisplay

        anchors.right:configSelectorId.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        snapMode: ListView.SnapOneItem
        boundsBehavior: Flickable.StopAtBounds
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: 0
        preferredHighlightEnd: 0
        highlightMoveDuration: 0
        interactive: false
        currentIndex: configSelectorId.currentIndex
        model:configs
        delegate: Flickable{
            visible: ListView.isCurrentItem
            enabled: visible
            boundsBehavior: Flickable.StopAtBounds
            id:rootDelegate
            width: configDisplay.width
            height: verifySettings.height
//            anchors.left: parent.left
//            anchors.right: parent.right
//            height: spinConfig.height
            //contentWidth: spinConfig.width
            contentHeight: spinConfig.height
            QsVerifySettingsGroup{
                id:spinConfig
                bottomPadding: 15
                rightPadding: 20
                anchors.right: parent.right
                anchors.left: parent.left
//                anchors.top: parent.top
//                anchors.bottom: verifyResultsId.top
                //anchors.left: parent.left
                //anchors.right: parent.right
                header: modelData
                isSelected: rootDelegate.ListView.isCurrentItem

                Component.onCompleted: console.debug("settings group content height "+ spinConfig.height)
            }
            Component.onCompleted: console.debug("flick content height "+ rootDelegate.contentHeight)
//			QsDivider{
//				anchors.left: parent.left
//				anchors.right: parent.right
//				anchors.bottom: parent.bottom
//				color: QsStyle.borderBackground
//			}

            ScrollBar.vertical: QsScrollBar {
                id:vScrollBar
                //onPressedChanged: {pressed ? console.debug("scrollBar started") :console.debug("scollbar stopped")}

            }

        }
    }
    ListView{
        id: configSelectorId
        implicitWidth: 150
        topMargin: 5
        header:QsHeader{
            text: qsTr("Configurations")

        }

        anchors{
            right: parent.right
            bottom: parent.bottom
            top: parent.top
        }
        model: configs
        delegate: QsText{
            padding: 5
            leftPadding: 10

            property int l_index: index
            anchors.left: parent.left
            anchors.right: parent.right
            id: txtDelegateId
            text: modelData
            color: ListView.isCurrentItem ? QsStyle.highlightColor : QsStyle.textColor
            font.pointSize: 12
            MouseArea{
                anchors.fill: parent
                onClicked: txtDelegateId.ListView.view.currentIndex =txtDelegateId.l_index
            }
            QsDivider{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }
    }

    QsDivider{
        anchors.left: configSelectorId.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        oritentation: Qt.Vertical
        color: QsStyle.borderBackground
    }
}
