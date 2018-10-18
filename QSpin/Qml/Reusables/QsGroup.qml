import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.4
QsPane {
	default property alias newData: container.data
	property alias header: headerId.text
	property alias containerWidth: container.width
	property alias headerWrapMode: headerId.wrapMode
	rightPadding: 5
	ColumnLayout{
		id:container
		QsHeader{
			id:headerId
		}



	}
}
