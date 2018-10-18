import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
QsPane {
    id: spinConfig
    property alias header: headerId.text
    property alias hashValue: hashValueId.value
    property alias searchBy: searchById.currentIndex // go away from combobox
    property alias searchDepth: searchDepthId.value
    property alias isWeakFairness: btnWeakFairnessId.pressed
    property bool isSelected: false

    property int hSpacing: 15
    property bool maximized: true

    ColumnLayout{
        anchors.fill: parent
        id:layout
        spacing: 10

        RowLayout{

            QsHeader{
                id:headerId
                text: "some configuration"
                textColor: spinConfig.isSelected ? QsStyle.highlightColor : QsStyle.headerColor
            }
            Item {
                id: emptySpace
                Layout.fillWidth: true
            }
            QsButtonSquare{
                Layout.minimumWidth: height
                id:btnCollapseableId
                opacity: 0.7
                text: maximized ?"_" : "[]"
                onClicked: maximized = !maximized
            }
            QsButtonSquare{
                Layout.minimumWidth: height
                id: btnDestroyId
                opacity: 0.7
                text: "X"
            }

        }
        RowLayout{
            visible: maximized
            id:row2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: hSpacing
            QsComboBox{
                id:basedOn
                Layout.minimumWidth: 180
            }
            QsRadioIconButtons{
                id:verificationType
                currentIndex: 2
                model:["A","L","S"]
            }
            QsRadioIconButtons{
                id:searchById
                model: ["DFS","BFS"]
            }
            QsButton{
                id:btnWeakFairnessId
                enabled: verificationType.currentIndex!==2
                checkable: true
                checked: true
                text: qsTr("Weak fairnes")
                opacity: enabled ? 1: 0
                Layout.minimumHeight: searchById.height
            }
            Item{//space filler
                Layout.fillWidth: true
            }
        }


        GridLayout{
            visible: maximized
            id:row3
            columns: 3
            rows:2
            // search by 1



            //row 1
            QsText{
                id:txtSearchDepth
                text: qsTr("Search depth"); color: QsStyle.smallHeaderColor
            }
            QsText{
                id:txtHashValue
                text:qsTr("Hash value"); color: QsStyle.smallHeaderColor
            }
            QsText{
                id:txtMemCompression
                text:qsTr("Memory compression"); color: QsStyle.smallHeaderColor
            }
            // row 2
            QsSpinBox{
                id:searchDepthId
                Layout.fillWidth: true
            }



            // hash value 3

            QsSpinBox{
                id:hashValueId
                Layout.fillWidth: true
            }
            // memory compression 4
            QsComboBox{
                id:cbxMemoryCompression
                Layout.fillWidth: true
            }
        }
        //        ColumnLayout{
        //            visible: maximized && verificationType.currentIndex === 0 // acceptance verification only
        //            enabled: visible

        QsText{
            text: qsTr("LTL:"); color: QsStyle.smallHeaderColor
        }
        // QsDivider{Layout.fillWidth: true; color: QSpinStyle.highlightColor}
        Rectangle{
            Layout.fillWidth: true
            Layout.minimumHeight: 100

            Layout.fillHeight: true
            color: "transparent"
            border.color: QsStyle.borderBackground
            border.width: 1
            radius: 3
            QsTextEdit{
                id:ltlId
                anchors.fill: parent
        }

        }
        // QsDivider{Layout.fillWidth: true; color: QSpinStyle.highlightColor}
        //        }




        Repeater{
            model: 30
            QsButton{
                text: qsTr("hej")
            }
        }
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
            border.color: QsStyle.borderBackground
            border.width: 1
            radius: 3
            color: "transparent"

        }

    }
}
