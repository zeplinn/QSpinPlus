import QtQuick 2.11
import QtQuick.Controls 2.4
Item {
    id:selctionBarRootId
    default property  alias contentItems: layoutContainerId.contentData
    implicitWidth:  layoutId.implicitWidth
    implicitHeight: layoutId.implicitHeight
    property alias spacing: layoutId.spacing
    Container{
        id: layoutContainerId
        contentItem: Item{
            implicitWidth: layoutId.implicitWidth
            implicitHeight: layoutId.implicitHeight
            Row{
                id:layoutId
                Repeater{
                    model: layoutContainerId.contentModel
                    delegate: Item{
                        readonly property int visualIndex: Positioner.index
                        implicitWidth:  childrenRect.width
                        implicitHeight:  childrenRect.height
                        children: [modelData]

                    }
                }
            }
        }
    }

}
