import QtQuick 2.11
import QSpin.CppItems 1.0
QsPane{
    bottomPadding: 5
    topPadding: 5
    property alias text: headerId.text
    property alias wrapMode: headerId.wrapMode
    property alias textColor: headerId.color
    QsText {

        id: headerId
        //color: "#757575"
		color: QsStyle.general.foreground
        wrapMode: Text.NoWrap
        font{
			pointSize: 10//14
            italic: true
        }

    }
}
