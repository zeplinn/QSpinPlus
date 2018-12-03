import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
//import QSpin 1.0
Item{
	id:rootId
	implicitHeight: childrenRect.height
	Component.onCompleted: console.debug("verify result w/h: "+width+" / "+height)
	property var flow:""// verificationMenu.flow
	property alias report: handlerId.reference
	readonly property alias open: headerLayout.isVisble
	QsVerifyResultReportHandler{
		id:handlerId
	}


	ColumnLayout{
		id:rootLayoutId
		property int prefferedWidths: width/3
		Component.onCompleted: console.debug("verify result colLayout w/h: "+width+" / "+height)
		anchors.left: parent.left
		anchors.right: parent.right
		MouseArea{
			implicitHeight: 24
			Layout.fillWidth: true
			onClicked: headerLayout.isVisble = ! headerLayout.isVisble
		RowLayout{
			id: headerLayout
		anchors.fill: parent
			property bool isVisble: true
			QsText{leftPadding: 16; text:qsTr("Spin version: "); Layout.fillWidth: true}
			QsText{text:handlerId.item.version; Layout.fillWidth: true}
			QsText { text: qsTr("Elapsed time"); Layout.fillWidth: true }
			QsText{rightPadding: 16;
				text:handlerId.item.elapsedTime
				Layout.fillWidth: true}
		}
		}
		QsDivider{
			oritentation: Qt.Horizontal
			Layout.fillWidth:  true
			color: QsStyle.general.border
		}
		RowLayout{
			visible: headerLayout.isVisble
			QsGroup{
				id: fullStatespaceFor
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Component.onCompleted: console.debug("verify result group1 w/h: "+width+" / "+height)
				Layout.fillWidth: true

				Layout.preferredWidth: rootLayoutId.prefferedWidths

//				width: parent.mininmalWidth
				header: qsTr("Full statespace for")
				containerWidth: statespaceSpecifications.containerWidth
				QsResultLabel{
					id:partialOrder
					label: qsTr("Partial order reduction:")
					result: handlerId.item.stateSpaceFor.partialOrderReduction
				}
				QsResultLabel{
					id:neverClaim
					label: qsTr("Never claim:")
					result: handlerId.item.stateSpaceFor.neverClaim
				}
				QsResultLabel{
					id: assertViolations
					label: qsTr("Assertion violations:")
					result: handlerId.item.stateSpaceFor.assertionViolations
				}

				QsResultLabel{
					id: acceptanceCycles
					label: qsTr("Acceptance cycles:")
					result: handlerId.item.stateSpaceFor.acceptanceCycles
				}
				QsResultLabel{
					id: invalidEndStates
					label: qsTr("Invalid end states:")
					result: handlerId.item.stateSpaceFor.invalidEndStates
				}

			}

			QsDivider{
				oritentation: Qt.Vertical
				Layout.fillHeight: true
				color: QsStyle.general.border
			}

			QsGroup{
				//width: parent.mininmalWidth
				id:statespaceSpecifications
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Layout.fillWidth: true
				Layout.preferredWidth: rootLayoutId.prefferedWidths
				Component.onCompleted: console.debug("verify result group2 w/h: "+width+" / "+height)

				header: qsTr("Full statespace specifications")

				QsResultLabel{
					id: depthReached
					label: qsTr("Depth reached:")
					result: handlerId.item.stateSpaceSpec.depthReached
				}

				QsResultLabel{
					id: storedStates
					label: qsTr("Stored states:")
					result: handlerId.item.stateSpaceSpec.storedStates
				}
				QsResultLabel{
					id: mathedStates
					label: qsTr("Mathed states:")
					result: handlerId.item.stateSpaceSpec.matchedStates
				}

				QsResultLabel{
					id: transitionsTaken
					label: qsTr("Transitions taken:")
					result: handlerId.item.stateSpaceSpec.transitionTaken
				}
				QsResultLabel{
					id: atomicSteps
					label: qsTr("Atomic steps:")
					result: handlerId.item.stateSpaceSpec.atomicSteps
				}
				QsResultLabel{
					id: stateSize
					label: qsTr("State size:")
					result: handlerId.item.stateSpaceSpec.stateSize
				}
				QsResultLabel{
					id: hashConfilicts
					label: qsTr("Hash conflicts:")
					result: handlerId.item.stateSpaceSpec.hashConflicts
				}
				QsResultLabel{
					id:hashSize
					label: qsTr("Hash size:")
					result: handlerId.item.stateSpaceSpec.hashSize
				}

			}
			QsDivider{
				oritentation: Qt.Vertical
				Layout.fillHeight: true
				color: QsStyle.general.border
			}

			QsGroup{
				id:memoryUsage
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Layout.preferredWidth: rootLayoutId.prefferedWidths
				Layout.fillWidth: true

				Component.onCompleted: console.debug("verify result group3 w/h: "+width+" / "+height)

				//width: parent.mininmalWidth
				header: qsTr("Memory usage")
				containerWidth: statespaceSpecifications.containerWidth
				QsResultLabel{
					id:forStates
					label: qsTr("For states:")
					result: handlerId.item.memoryUsage.forStates
				}
				QsResultLabel{
					id: forHashTable
					label: qsTr("For hash table:")
					result: handlerId.item.memoryUsage.forHashTable
				}
				QsResultLabel{
					id: forSearchStack
					label: qsTr("For search stack:")
					result: handlerId.item.memoryUsage.forSearchStack
				}

				QsResultLabel{
					id: inTtotal
					label: qsTr("In total:")
					result: handlerId.item.memoryUsage.inTotal
				}

			}
		}

	}
}
