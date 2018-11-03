import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
TabButton {
    id:btnId
    //implicitWidth: childrenRect.width
    implicitWidth: 150
    implicitHeight: 24
    leftPadding: 4
    rightPadding: 4
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
