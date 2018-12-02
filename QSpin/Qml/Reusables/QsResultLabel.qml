import QtQuick 2.11
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0

	RowLayout {
		implicitHeight: childrenRect.height
		id:resultLabel
		property alias label: labelId.text
		property var result:-1

		QsText{
			id:labelId
			verticalAlignment: Text.AlignVCenter
			Layout.maximumHeight: labelId.height
			Layout.minimumWidth: contentWidth

		}
		QsDivider{
			Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
			Layout.fillWidth: true
			isDottedLine: true

		}
		QsText{
			Layout.maximumHeight: labelId.height
			id:resultId
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignRight
			text: resultLabel.result
			state: resultLabel.result
			states:[
				State {
					name: "true"
					PropertyChanges {
						target: resultId
						text: "true"
					}
				},
				State {
					name: "false"
					PropertyChanges {
						target: resultId
						text: "false"
					}
				},
				State {
					name: "-1"
					PropertyChanges {
						target: resultId
						text: ""
					}
				}
			]
		}

	}

