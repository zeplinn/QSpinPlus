import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.11
import QSpin.Qml.Reusables 1.0
import QSpin.CppItems 1.0
//import QSpin 1.0
QsPane{
    QsVerifyResultHandler{
        id:results
    }

    padding: 0
    RowLayout{
        clip: true
        id:verificationMenu

        QsGroup{
            id: fullStatespaceFor
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
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

        QsGroup{
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            id:statespaceSpecifications
            header: qsTr("Full statespace specifications")
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
                result: results.mathedStates
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

        QsGroup{
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            id:memoryUsage
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
