import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QtQuick.Layouts 1.11
import QtQml.Models 2.4
QsPane {
	default property alias columns: tableHandlerId.columns
	property alias tableModel: tableHandlerId.tModel
	property alias delegate: visualModel.delegate
	ListView{
		id:tableListId
		model: delegateModel
		states:[
			State {
				when: delegateModel === null

				PropertyChanges {
					target: tableListId
					model: tableModel
				}
			}
		]
		header: RowLayout{
			id:columnHeadersLayoutId
			Repeater{
				model: tableHandlerId.columns
				ItemDelegate{
					Layout.fillWidth: true
					text: modelData.text
				}
			}
		}

		Repeater{
			model: tableListId.header.children
			QsDivider{
				color: QsStyle.general.border
			}
		}

		QsTableHandler{
			id:tableHandlerId
			property QsTableColumn columns: []
			property var tModel: []
			//property Component delegate: null
		}
		DelegateModel{
			id:visualModel
			model: tableHandlerId.tModel

		}
	}
}
