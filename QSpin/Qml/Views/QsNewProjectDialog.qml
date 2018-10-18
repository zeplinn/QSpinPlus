import QtQuick 2.0
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Dialogs 1.3 as Fd
Dialog{
    title: qsTr("Create new Project")
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    closePolicy: Popup.NoAutoClose | Popup.CloseOnEscape
    ColumnLayout{
        id:rootLayoutId
        anchors.fill: parent
        spacing: 20

        TextField{
            id:projectNameId
            Layout.fillWidth: true
        }

        CheckBox {
            id: checkBox
            text: qsTr("Remove spaces for path")
        }
        RowLayout{
            spacing: 10
            Label{
                text: qsTr("Path:")
            }
            QsText{
                id:absolutePathId
                Layout.minimumWidth: 300
                text: qsTr("some absolute path")
                Layout.fillWidth: true
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
//        RowLayout{
//            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
//            QsButton{
//                text: qsTr("Create")
//                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
//                onClicked: {
//                    completed()
//                }
//            }
//            QsButton{
//                text: qsTr("Cancel")
//                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
//                onClicked:{
//                    completed()
//                }
//            }
//        }

    }
    Fd.FileDialog{
        id:folderExplorerId

        selectFolder: true
    }

}
