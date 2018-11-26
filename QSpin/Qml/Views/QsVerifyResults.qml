import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
//import QSpin 1.0
Item{
	id:rootId
	implicitHeight: childrenRect.height

	QsVerifyResultHandler{
		id:results
	}
	Row{
		id:verificationMenu
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.leftMargin: 8
		anchors.rightMargin: 8
		clip: true
		spacing: 0
		property int mininmalWidth: width/3 -3

		QsGroup{
			id: fullStatespaceFor
			leftPadding: 4
			rightPadding: 4
			width: parent.mininmalWidth
			header: qsTr("Full statespace for")
			containerWidth: statespaceSpecifications.containerWidth
			QsResultLabel{
				id:partialOrder
				label: qsTr("Partial order reduction:")
				result: results.partialOrderReduction
			}
			QsResultLabel{
				id:neverClaim
				label: qsTr("Never claim:")
				result: results.neverClaim
			}
			QsResultLabel{
				id: assertViolations
				label: qsTr("Assertion violations:")
				result: results.assertionViolations
			}

			QsResultLabel{
				id: acceptanceCycles
				label: qsTr("Acceptance cycles:")
				result: results.acceptanceCycles
			}
			QsResultLabel{
				id: invalidEndStates
				label: qsTr("Invalid end states:")
				result: results.invalidEndStates
			}

		}

		QsDivider{
			oritentation: Qt.Vertical
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			color: QsStyle.general.border
		}

		QsGroup{
			width: parent.mininmalWidth
			id:statespaceSpecifications
			header: qsTr("Full statespace specifications")
			leftPadding: 4
			rightPadding: 4
			QsResultLabel{
				id: depthReached
				label: qsTr("Depth reached:")
				result: results.depthReached
			}

			QsResultLabel{
				id: storedStates
				label: qsTr("Stored states:")
				result: results.storedStates
			}
			QsResultLabel{
				id: mathedStates
				label: qsTr("Mathed states:")
				result: results.matchedStates
			}

			QsResultLabel{
				id: transitionsTaken
				label: qsTr("Transitions taken:")
				result: results.transitionsTaken
			}
			QsResultLabel{
				id: atomicSteps
				label: qsTr("Atomic steps:")
				result: results.atomicSteps
			}
			QsResultLabel{
				id: stateSize
				label: qsTr("State size:")
				result: results.stateSize
			}
			QsResultLabel{
				id: hashConfilicts
				label: qsTr("Hash conflicts:")
				result: results.stateSize
			}
			QsResultLabel{
				id:hashSize
				label: qsTr("Hash size:")
				result: results.hashSize
			}

		}
		QsDivider{
			oritentation: Qt.Vertical
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			color: QsStyle.general.border
		}

		QsGroup{
			leftPadding: 4
			rightPadding: 4
			id:memoryUsage
			width: parent.mininmalWidth
			header: qsTr("Memory usage")
			containerWidth: statespaceSpecifications.containerWidth
			QsResultLabel{
				id:forStates
				label: qsTr("For states:")
				result: results.forStates
			}
			QsResultLabel{
				id: forHashTable
				label: qsTr("For hash table:")
				result: results.forHashTable
			}
			QsResultLabel{
				id: forSearchStack
				label: qsTr("For search stack:")
				result: results.forSearchStack
			}

			QsResultLabel{
				id: inTtotal
				label: qsTr("In total:")
				result: results.inTotal
			}

		}

	}

}
