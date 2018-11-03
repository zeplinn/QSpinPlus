import QtQuick 2.0

QsButton {
	id: rootId
	checkable: true

	background: Rectangle{
		id: backgroundId
		color: QsStyle.button.background
		states:[
			State {
				name: "Checked"
				when: rootId.checked
				PropertyChanges {
					target: backgroundId
					color: QsStyle.button.pressed

				}
			}
		]
	}
}
