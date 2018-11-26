import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11

Item {
	id:rootId

RowLayout{
	ColumnLayout{
		RowLayout{
			QsButton{
				text: qsTr("Compare documents")
			}
		}

		QsVerifyResults{

		}

		ListView{
			id:commandsUsedId
		}

		Item{
			id:rawReportId
		}
	}

	ColumnLayout{

		ListView{
			id:verifyResultsId
		}
	}


}

}
