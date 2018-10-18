import QtQuick 2.11
import QtQuick.Controls 2.3
import QSpin.CppItems 1.0
SpinBox {
    id: control
    value: 0
    editable: true
    implicitHeight: 32
    padding: 5
    property int spinHeight: 20
    font.pointSize: 10
	validator: IntValidator{

	}

    contentItem: TextInput {
        z: 2
        //width: 70
        anchors.horizontalCenter: control.horizontalCenter
		//text: control.textFromValue(control.value, control.locale)
		text:control.value
        font.pointSize: 10
		font.family: "candara"
        color: "#D4D4D4"
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !control.editable
        validator: control.validator
		inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : parent.width - width
        height: parent.height
        color: "transparent"
        border.width: 0
        implicitWidth: control.spinHeight
        implicitHeight: control.implicitHeight
        //border.color: enabled ? "#21be2b" : "#bdbebf"

        Text {
            text: "+"
            font.bold: true
            font.pixelSize: 12
			color: QsStyle.highlightColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    down.indicator: Rectangle {
        x: control.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: control.spinHeight
        implicitHeight: control.implicitHeight
        color: "transparent"
        border.width: 0
        //color: control.down.pressed ? "#e4e4e4" : "#f6f6f6"
        //border.color: enabled ? "#21be2b" : "#bdbebf"

        Text {
            text: "-"
            font.bold: true
            font.pixelSize: 12
			color: QsStyle.highlightColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        border.width: 1
		border.color: QsStyle.borderBackground
        color: "transparent"
        radius:3

        implicitWidth: 140
    }


}
