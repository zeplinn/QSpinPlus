import QtQuick 2.11
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Dialogs 1.3
import QSpin.Qml.Views 1.0
ToolBar{
id: rootId
readonly property alias undoButton: btnUndoId
readonly property alias redoButton: btnRedoId
    readonly property alias isVerifyTabSelected: verifyTabId.checked
    readonly property alias isVerifyResultTabSelected:verifyResultTabId.checked
    readonly property alias isSimulationTabSelected: simulationTabId.checked
    readonly property alias isUiLocked: toolbarId.isUiLocked
    property alias toolViewsTabBar: toolsTabId
    signal saveProject(url fileUrl)
    signal openProject(url fileUrl)
    signal createProject(string name,url folder)
    QstopToolbarHandler{
        id: handlerId
        //currentToolTabIndex: toolsTabId.currentIndex

    }

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
                }

                QsTabButton{
                    id:verifyResultTabId
                    text:qsTr("VerificationResults")
                }
                QsTabButton{
                    id:simulationTabId
                    text: qsTr("Simulation")
                }
                // ############ end tool view tabs "#######################
            }
        }
    }
    QsNewProjectDialog{
        id: newProjectDialogId
        x: ( qspinAppId.width - width ) *0.5
        y: (qspinAppId.height -height ) *0.5
        onAccepted: rootId.createProject(name,folder)
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
}
