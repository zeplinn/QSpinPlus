import QtQuick 2.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
Item {
	implicitHeight: childrenRect.height
	Column{
		anchors.left: parent.left
		anchors.right: parent.right
		Rectangle{
			implicitHeight: 24
			anchors.left: parent.left
			anchors.right: parent.right
			gradient: Gradient{
				GradientStop{ position: 0; color: QsStyle.general.menubarGradiant0 }
				GradientStop{ position: 1; color: QsStyle.general.menubarGradiant1}
			}
			QsDivider{
				oritentation: Qt.Horizontal
				anchors.top: parent.top
				anchors.left: parent.left
				anchors.right: parent.right
				color: QsStyle.general.border
			}
			QsDivider{
				oritentation: Qt.Horizontal
				anchors.bottom: parent.bottom
				anchors.left: parent.left
				anchors.right: parent.right
				color: QsStyle.general.border
			}
		}

	QsVerifyResults{
		anchors.left: parent.left
		anchors.right: parent.right
	}
	}

}
