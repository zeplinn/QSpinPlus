
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
    flags:  Qt.Window | Qt.FramelessWindowHint
    width: 1600
    height: 900
    minimumHeight: 764
    minimumWidth: 1024

    title: qsTr("Hello World")
    background: Rectangle{
        border.color: "black"
        border.width: 1

    }

    //onWidthChanged: qspin.Minimized
    // background: Rectangle{color: Qt.rgba(45/256)}

    // menu bars ##################################################

    header:Rectangle{
        implicitHeight: 32
        anchors.left: parent.left
        anchors.right: parent.right
        border.color: "black"
        border.width: 1
        gradient: Gradient{
            id: g
            property real c1: 51/256
            property real c2: 59/256
            GradientStop{ position: 0; color: Qt.rgba(g.c2,g.c2,g.c2,1) }
            GradientStop{ position: 1; color: Qt.rgba(g.c1,g.c1,g.c1,1) }
        }
//        QsDivider{
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.right
//            color: "black"

//        }

        // enables window dragging
        MouseArea {
            anchors.fill: parent;
            property point clickPos: "1,1"

            onPressed: {
                clickPos = Qt.point(mouse.x,mouse.y)
            }

            onPositionChanged: {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                var new_x = qspinAppId.x + delta.x
                var new_y = qspinAppId.y + delta.y
                if (new_y <= 0)
                    qspinAppId.visibility = Window.Maximized
                else
                {
                    if (qspinAppId.visibility === Window.Maximized)
                        qspinAppId.visibility = Window.Windowed
                    qspinAppId.x = new_x
                    qspinAppId.y = new_y
                }
            }
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

            Text{
                id: appTitleId
                height: parent.height
                text: qsTr("QSpin+")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: QsStyle.headerColor
                font.pointSize: 16
            }
            spacing: 8

            // selection tabs
            Item{
                Layout.fillWidth: true
            }
            QsTabBar{
                id: toolsTabId
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                QsTabButton{
                    text:qsTr("Verification")
                }

                QsTabButton{
                    text:qsTr("Verification Results")
                }

                QsTabButton{
                    id:tabBtnInteractiveId
                    text: qsTr("Interactive")

                }
                QsTabButton{
                    text: qsTr("Simulation")
                }
            }
            Item {
                Layout.minimumWidth: 200
                Layout.maximumWidth: 200
            }
            QsToolButton{
                imageSource: "qrc:/icons/minimize.png"
                onClicked: qspinAppId.showMinimized()
                useTooltip: false

            }
            QsToolButton{
                imageSource: "qrc:/icons/maximize.png"
                onClicked: qspinAppId.showMaximized()
                useTooltip: false

            }
            QsToolButton{
                imageSource: "qrc:/icons/close.png"
                onClicked: qspinAppId.close()
                useTooltip: false
                //                Image{
                //                    anchors.centerIn: parent
                //                    source: "qrc:/icons/close.png"
                //                }
            }
        }
    }


    // text editor area
    ColumnLayout{
        anchors{
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            right: toolsViewId.left
        }
        spacing: 0

        QsCodeEditor{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 500
            Layout.minimumWidth: 800

        }
        // popup menu
        Item{
            visible: false
            Layout.fillWidth: true
            Layout.minimumHeight: 200
        }

        //bottom bar
        Rectangle{
            Layout.fillWidth: true
            Layout.minimumHeight: 32
            Layout.maximumHeight: 32
            gradient: Gradient{
                GradientStop{ position: 0; color: Qt.rgba(g.c2,g.c2,g.c2,1) }
                GradientStop{ position: 1; color: Qt.rgba(g.c1,g.c1,g.c1,1) }
            }

            QsDivider{
                anchors{
                    top : parent.top
                    left: parent.left
                    right: parent.right

                }
                color: "black"
            }

            QsTabBar{
                anchors.verticalCenter: parent.verticalCenter
                QsTabButton{
                    text: qsTr("Verification scheduler")
                }
                QsTabButton{
                    text: qsTr("Output")
                }

                QsTabButton{
                    text: qsTr("Interactive selector")
                }
            }
        }

    }
    QsToolViews{
        id:toolsViewId
        anchors{
            //left:editor.right
            right: parent.right
            top: parent.top
            bottom:parent.bottom
        }
        width: parent.width*0.5
        selectedTabIndex:toolsTabId.currentIndex
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


    // frame window
    QsDivider{
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        color: "black"
        oritentation: Qt.Vertical
    }
    QsDivider{
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        color: "black"
        oritentation: Qt.Vertical
    }
    QsDivider{
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "black"
    }
}
