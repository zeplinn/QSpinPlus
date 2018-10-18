import QtQuick 2.11
import QtQuick.Controls 2.3
import QSpin.CppItems 1.0
Item{
    id:control
    implicitWidth: row.width
    implicitHeight:  row.height
    property int currentIndex: 0
    property alias model: repeater.model
    property alias spacing: row.spacing
    Row{
        id:row
        spacing:2
        Repeater{
            id:repeater
            model:["A","L","S"]
            delegate: QsButton{
                id:btnRadio
                property int btnIndex: Positioner.index
                width: 32
                height: 32
                text: modelData
                checkable: true
                checked: false

                onClicked:{control.currentIndex = btnRadio.btnIndex;}
                states:State{
                    when: control.currentIndex === btnRadio.btnIndex
                    PropertyChanges{
                        target: btnRadio
						textColor: QsStyle.highlightColor
						borderColor: QsStyle.highlightColor
                        checked:true
                    }
                }

            }
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
