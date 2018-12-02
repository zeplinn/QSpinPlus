import QtQuick 2.11
import QtQuick.Controls 2.4
import QSpin.CppItems 1.0
import QSpin.Qml.Reusables 1.0
import QtQuick.Layouts 1.11
import QtQml.Models 2.4
import QtQuick.Window 2.11


QsPane {
	id:rootId
	//mplicitWidth: childrenRect.width
	//implicitHeight: 500
	RowLayout{

		id:layoutId
		spacing: 0
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		QsVerifyResultHandler{
			id:handlerId
			currentIndex: verifyResultsId.currentIndex
			onCurrentItemChanged: {
				if(currentItem !== null){
					displaydocId.documentHandler.setText(currentItem.document())
					compareIndicator.isSameDoc = compareToCurrentDocument()

				}else{
					displaydocId.documentHandler.clearText()


				}
			}
			property int leftPadding: 4
		}

		ColumnLayout{
			enabled: handlerId.currentItem !== null
			RowLayout{
				QsButton{
					text: qsTr("Compare documents")
					Layout.alignment: Qt.AlignLeft | Qt.AlignTop
					Layout.preferredWidth: implicitWidth+24
					Rectangle{
						id:compareIndicator
						property bool isSameDoc: false
						opacity: enabled ? 0.4 : 0
						radius: 6
						color: isSameDoc ? "green" : "red"
						anchors.verticalCenter: parent.verticalCenter
						anchors.right: parent.right
						anchors.rightMargin: 4
						implicitHeight: 12
						implicitWidth: 12
					}
					onClicked:{
						compareIndicator.isSameDoc = handlerId.compareToCurrentDocument()
					}
				}
				QsButton{
					text: qsTr("Raw XML file")
					onClicked: {
						xmlReportWindowId.document.setText(handlerId.getXmlReport())
						if(!xmlReportWindowId.visible)
							xmlReportWindowId.show()
					}
				}
				QsButton{
					text: qsTr("Raw Verification report")
					onClicked: {
						xmlReportWindowId.document.setText(handlerId.selectedResults.rawReport())
						if(!xmlReportWindowId.visible){
							xmlReportWindowId.show()

						}

					}
				}
			}
			QsDivider{
				oritentation: Qt.Horizontal
				Layout.fillWidth: true
				color: QsStyle.general.border
			}


			QsVerifyResults{
				id:resultsId
				Layout.fillWidth: true
				Layout.minimumWidth: 600
				report: handlerId.selectedResults

			}
			QsDivider{
				visible: resultsId.open
				oritentation: Qt.Horizontal
				Layout.fillWidth: true
				color: QsStyle.general.border
			}
			RowLayout{
				QsText{ leftPadding: handlerId.leftPadding;	text: qsTr("Used Spin commands:"); Layout.preferredWidth: 140}
				QsText{	text: handlerId.spinCommands;rightPadding: handlerId.leftPadding; elide: QsText.ElideLeft}
			}
			RowLayout{
				QsText{	leftPadding: handlerId.leftPadding;text: qsTr("Used gcc commands:"); Layout.preferredWidth: 140}
				QsText{	text: handlerId.gccCommands; rightPadding: handlerId.leftPadding; elide: QsText.ElideLeft	}
			}
			RowLayout{
				QsText{	leftPadding: handlerId.leftPadding;text: qsTr("Used Pan commands"); Layout.preferredWidth: 140 }
				QsText{ text: handlerId.panCommands; rightPadding: handlerId.leftPadding; elide: QsText.ElideLeft		}
			}
			ColumnLayout{
				id:closerId
				QsText{
					id:unreachedLabelId
					property bool isVisible: false
					Layout.fillWidth: true
					Layout.preferredHeight: 40
					leftPadding: 8
					text: qsTr("Unreached states")
					horizontalAlignment: Text.AlignLeft
					verticalAlignment: Text.AlignVCenter
					height: 30
					MouseArea{
						anchors.fill: parent
						onClicked: unreachedLabelId.isVisible = ! unreachedLabelId.isVisible
					}
					QsDivider{
						oritentation: Qt.Horizontal
						anchors.left: parent.left
						anchors.right: parent.right
						anchors.top: parent.top
						color: QsStyle.general.border
					}
					QsDivider{
						oritentation: Qt.Horizontal
						anchors.left: parent.left
						anchors.right: parent.right
						anchors.bottom:  parent.bottom
						color: QsStyle.general.border
					}
				}

				QsText{

					visible: unreachedLabelId.isVisible
					wrapMode: QsText.WordWrap
					text: handlerId.unreached
					Layout.maximumWidth: 600
				}
			}


			Item {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.minimumHeight: 200
				QsCodeEditor{
					id:displaydocId
					anchors.fill: parent
					anchors.rightMargin: 8
					clip: true
					foreground: QsStyle.promelaEditor.foreground
					background: QsStyle.promelaEditor.background
					tabIndentSize: QsStyle.promelaEditor.tabIndents
					readonly: true
					font{
						family: QsStyle.promelaEditor.fontFamily
						pointSize: QsStyle.promelaEditor.pointSize
					}

					syntaxHighlighter: promelaHighlighterId
					QsPromelaSyntaxHighlighter{
						id: promelaHighlighterId
						colors: QsStyle.promelaEditor.syntaxHighlighter
					}

					Rectangle{
						border.color: QsStyle.general.border
						border.width: 1
						anchors.fill: parent
						color: "transparent"

					}
				}
			}
		}
		QsDivider{
			oritentation: Qt.Vertical
			Layout.fillHeight: true
			color: QsStyle.general.border
		}


		ListView{
			id:verifyResultsId
			highlightFollowsCurrentItem: true
			Layout.fillHeight: true
			implicitWidth: 250
			currentIndex: -1
			model: visualModel
		}

	}
	DelegateModel{
		id:visualModel
		model: handlerId.results
		delegate: itemResultDisplayId
	}
	Component{
		id:itemResultDisplayId
		ItemDelegate{
			id: rootDelId
			property int idx: rootDelId.DelegateModel.itemsIndex
			anchors.left: parent.left
			anchors.right: parent.right
			implicitHeight: childrenRect.height
			Column{
				anchors.left: parent.left
				anchors.right: parent.right
				leftPadding: 4
				rightPadding: 4
				QsText{ topPadding: 4;  text: model.name_role }
				QsText{ leftPadding: 12; bottomPadding: 4; text: model.createdAt_role}
				QsDivider{
					anchors.left: parent.left
					anchors.right: parent.right
					oritentation: Qt.Horizontal
					color: QsStyle.general.border
				}
			}
			background: Rectangle{
				id: idxBgId
				color: QsStyle.general.background
				states:[
					State {
						when: rootDelId.ListView.view.currentIndex === rootDelId.idx
						PropertyChanges {
							target: idxBgId
							color: QsStyle.general.hovered
							opacity: 0.2
						}
					}
				]
				QsToolButton{
					anchors.right: parent.right
					anchors.verticalCenter: parent.verticalCenter
					anchors.rightMargin: 4
					imageSource: "qrc:/icons/close.png"
					onClicked: handlerId.remove(rootDelId.idx)
				}
			}
			onClicked:{
				console.debug("resultIndexClicked: "+rootDelId.idx)
				rootDelId.ListView.view.currentIndex = rootDelId.idx
			}
		}
	}
	/*property Window  xmlReport: */Window{
		id:xmlReportWindowId
		minimumHeight: 400
		minimumWidth: 400
		width: 600
		height: 900
		visibility: Window.Hidden
		property alias document: xmlReportTextArea.documentHandler

		Rectangle{
			Keys.onEscapePressed: close()
			anchors.fill: parent
			color:QsStyle.general.background
			QsCodeEditor{
				id:xmlReportTextArea
				anchors.fill: parent
				//anchors.margins: 8
				readonly: true
			}
			onVisibleChanged: {
				if(!visible)
					document.clear()
			}
		}
	}

}
