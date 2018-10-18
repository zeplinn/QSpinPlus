#include "qspin/viewModels/QsVerifyResultHandler.h"

bool QsVerifyResultHandler::partialOrderReduction() const{ return _results ? _results->fullStatespaceFor().partialOrderReduction : 0 ;}

bool QsVerifyResultHandler::neverClaim() const{ return _results ? _results->fullStatespaceFor().neverClaim : 0 ;}

bool QsVerifyResultHandler::assertionViolations() const{ return _results ? _results->fullStatespaceFor().assertionViolations : 0 ;}

bool QsVerifyResultHandler::acceptanceCycles() const{ return _results ? _results->fullStatespaceFor().acceptanceCycles : 0 ;}

bool QsVerifyResultHandler::invalidEndStates() const{ return _results ? _results->fullStatespaceFor().invalidEndStates : 0 ;}

qreal QsVerifyResultHandler::depthReached() const{ return _results ? _results->fullStatespaceSpecifications().depthReached : 0 ;}

qreal QsVerifyResultHandler::storedStates() const{ return _results ? _results->fullStatespaceSpecifications().storedStates : 0 ;}

qreal QsVerifyResultHandler::matchedStates() const{ return _results ? _results->fullStatespaceSpecifications().matchedStates : 0 ;}

qreal QsVerifyResultHandler::transitionsTaken() const{ return _results ? _results->fullStatespaceSpecifications().transitionsTaken : 0 ;}

qreal QsVerifyResultHandler::atomicSteps() const{ return _results ? _results->fullStatespaceSpecifications().atomicSteps : 0 ;}

qreal QsVerifyResultHandler::stateSize() const{ return _results ? _results->fullStatespaceSpecifications().stateSize : 0 ;}

qreal QsVerifyResultHandler::hashConflicts() const{ return _results ? _results->fullStatespaceSpecifications().hashConflicts : 0 ;}

qreal QsVerifyResultHandler::hashSize() const{ return _results ? _results->fullStatespaceSpecifications().hashSize : 0 ;}

qreal QsVerifyResultHandler::forStates() const{ return _results ? _results->memoryUsed().forStates : 0 ;}

qreal QsVerifyResultHandler::forHashTable() const{ return _results ? _results->memoryUsed().forHashTable : 0 ;}

qreal QsVerifyResultHandler::forSearchStack() const{ return _results ? _results->memoryUsed().forSearchStack : 0 ;}

qreal QsVerifyResultHandler::inTotal() const{ return _results ? _results->memoryUsed().inTotal : 0 ;}


QsVerifyResultHandler::QsVerifyResultHandler(QObject *parent) : QObject(parent)
  ,msgService(Qs::instance().msgService()),_results(nullptr)
{

}

//qreal QsVerifyResultHandler::result(QsVerifyResultHandler::ResultCode code) const{
//    switch (code) {
//    case PartialOrderReduction: return results->fullStatespaceFor().partialOrderReduction;
//    case NeverClaim: return results->fullStatespaceFor().neverClaim;
//    case AssertionVioLations: return results->fullStatespaceFor().assertionViolations;
//    case AcceptanceCycles: return results->fullStatespaceFor().acceptanceCycles;
//    case InvalidEndStates: return results->fullStatespaceFor().invalidEndStates;

//    case DepthReached: return results->fullStatespaceSpecifications().depthReached;
//    case StoredStates: return results->fullStatespaceSpecifications().storedStates;
//    case MathedStates: return results->fullStatespaceSpecifications().mathedStates;
//    case TranisitionsTaken: return results->fullStatespaceSpecifications().transitionsTaken;
//    case AtomicSteps: return results->fullStatespaceSpecifications().atomicSteps;
//    case StateSize: return results->fullStatespaceSpecifications().stateSize;
//    case HashConflicts: return results->fullStatespaceSpecifications().hashConflicts;
//    case HashSize: return results->fullStatespaceSpecifications().hashSize;

//    case ForStates: return results->memoryUsage().forStates;
//    case ForHashTable: return results->memoryUsage().forHashTable;
//    case ForSearchStack: return results->memoryUsage().forSearchStack;
//    case InTotal: return results->memoryUsage().inTotal;

//    }
//}
