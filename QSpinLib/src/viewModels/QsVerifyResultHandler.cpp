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
