import QtQuick 2.11
import QtQuick.Layouts 1.11
import QSpin.CppItems 1.0

	RowLayout {
		implicitHeight: childrenRect.height
		id:resultLabel
		property alias label: labelId.text
		property real result: 0

		QsText{
			id:labelId
			verticalAlignment: Text.AlignVCenter
			Layout.maximumHeight: labelId.height

		}
		QsDivider{
			Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
			Layout.fillWidth: true
			isDottedLine: true

		}
		QsText{
			Layout.maximumHeight: labelId.height
			id:resultId
			visible: result !==0
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignRight
			text: resultLabel.result
		}

	}

