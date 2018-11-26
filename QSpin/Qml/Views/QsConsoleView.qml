import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
Item {
	id: rootId
	implicitHeight: 200
	implicitWidth: 200

	QsConsoleHandler{
		onMessageSend: consoleId.append(messsage)

	}
		Rectangle{
			id:headerBarId
			implicitHeight: 24
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			gradient: Gradient{
				GradientStop{ position: 0; color: QsStyle.general.menubarGradiant0 }
				GradientStop{ position: 1; color: QsStyle.general.menubarGradiant1}
			}
			QsDivider{
				oritentation: Qt.Horizontal
				anchors{
					left: parent.left
					right: parent.right
					top: parent.top
				}
				color: QsStyle.general.border
			}
			QsDivider{
				oritentation: Qt.Horizontal
				anchors{
					left: parent.left
					right: parent.right
					bottom:  parent.bottom

				}
				color: QsStyle.general.border
			}
		}

		QsCodeEditor{
			id: consoleId
			anchors.top: headerBarId.bottom
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			implicitHeight: 250
			readonly: true
			background: QsStyle.promelaEditor.background
		}


}
