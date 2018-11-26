#ifndef QSVERIFYRESULTHANDLER_H
#define QSVERIFYRESULTHANDLER_H

#include <QObject>
#include "qspin/models/QsVerificationResults.h"
#include <memory>
#include "qspin/QObjectBase.h"
//#include "qspin/viewModels/EventAggregator.h"
//#include "qspin/Qs.h"
// missing subscription object
class QsVerifyResultHandler : public QObjectBase
{
    Q_OBJECT
    // ############### result properties start ##################################

    //statespaceFor
    Q_PROPERTY(bool partialOrderReduction READ partialOrderReduction NOTIFY resultsUpdated)
    Q_PROPERTY(bool neverClaim READ neverClaim NOTIFY resultsUpdated)
    Q_PROPERTY(bool assertionViolations READ assertionViolations NOTIFY resultsUpdated)
    Q_PROPERTY(bool acceptanceCycles READ acceptanceCycles NOTIFY resultsUpdated)
    Q_PROPERTY(bool invalidEndStates READ invalidEndStates NOTIFY resultsUpdated)
    //statespace specifications

    Q_PROPERTY(qreal depthReached READ depthReached NOTIFY resultsUpdated)
    Q_PROPERTY(qreal storedStates READ storedStates NOTIFY resultsUpdated)
    Q_PROPERTY(qreal matchedStates READ matchedStates NOTIFY resultsUpdated)
    Q_PROPERTY(qreal transitionsTaken READ transitionsTaken NOTIFY resultsUpdated)
    Q_PROPERTY(qreal atomicSteps READ atomicSteps NOTIFY resultsUpdated)
    Q_PROPERTY(qreal stateSize READ stateSize NOTIFY resultsUpdated)
    Q_PROPERTY(qreal hashConflicts READ hashConflicts NOTIFY resultsUpdated)
    Q_PROPERTY(qreal hashSize READ hashSize NOTIFY resultsUpdated)

    // memory usage
    Q_PROPERTY(qreal forStates READ forStates NOTIFY resultsUpdated)
    Q_PROPERTY(qreal forHashTable READ forHashTable NOTIFY resultsUpdated)
    Q_PROPERTY(qreal forSearchStack READ forSearchStack NOTIFY resultsUpdated)
    Q_PROPERTY(qreal inTotal READ inTotal NOTIFY resultsUpdated)

    verifyResult_ptr _results = nullptr; //
public:// result properies only
    bool partialOrderReduction()const;
    bool neverClaim()const;
    bool assertionViolations()const;
    bool acceptanceCycles()const;
    bool invalidEndStates()const;

    qreal depthReached()const;
    qreal storedStates()const;
    qreal matchedStates()const;
    qreal transitionsTaken()const;
    qreal atomicSteps()const;
    qreal stateSize()const;
    qreal hashConflicts()const;
    qreal hashSize()const;

    qreal forStates()const;
    qreal forHashTable()const;
    qreal forSearchStack()const;
    qreal inTotal()const;
signals:
    void resultsUpdated();
protected:
public:
    using QObjectBase::QObjectBase;

public slots:
};

#endif // QSVERIFYRESULTHANDLER_H
