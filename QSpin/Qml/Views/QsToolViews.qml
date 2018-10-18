import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.Qml.Reusables 1.0
Item {
id: toolViewId

property alias selectedTabIndex: tabsId.currentIndex
    SwipeView{
        interactive: false
        id: tabsId
        anchors.fill: parent
        currentIndex: 0
        clip: true

        QsVerificationView{
            height: tabsId.height
            width: tabsId.width
        }
        QsInteractiveView{
            height: tabsId.height
            width: tabsId.width

        }
        QsSimulationView{
            height: tabsId.height
            width: tabsId.width

        }

        contentItem: ListView {
                  model: tabsId.contentModel
                  interactive: tabsId.interactive
                  currentIndex: tabsId.currentIndex

                  spacing: tabsId.spacing
                  orientation: tabsId.orientation
                  snapMode: ListView.SnapOneItem
                  boundsBehavior: Flickable.StopAtBounds

                  highlightRangeMode: ListView.StrictlyEnforceRange
                  preferredHighlightBegin: 0
                  preferredHighlightEnd: 0
                  highlightMoveDuration: 0
                  //highlightMoveDuration: 50
                  //                    min:10
//                  maximumFlickVelocity: 4 * (tabsId.orientation ===
//                  Qt.Horizontal ? width : height)
              }

    }
}
