import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0

Button {
    id: btnrootId
    implicitHeight: 24
    implicitWidth: 24
    property alias imageSource: imageId.source
    property string tooltip: ""
    property bool useTooltip: false
    property alias imageRotation: imageId.rotation
    padding: 4
    rightPadding: 4
    leftPadding: 4
//    contentItem: QsText{
//        text: btnrootId.text
//        verticalAlignment: Text.AlignVCenter
//        horizontalAlignment: Text.AlignHCenter
//    }
    contentItem: Image{
        id:imageId
    }

    ToolTip.visible: hovered && useTooltip
    ToolTip.text: tooltip
    ToolTip.delay: 500
    ToolTip.timeout: 2000

    background: Rectangle{
        color: hovered || pressed ? QsStyle.button.pressed : "transparent"
    }
}
