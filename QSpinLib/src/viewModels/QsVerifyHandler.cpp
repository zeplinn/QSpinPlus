#include "qspin/viewModels/QsVerifyHandler.h"


void QsVerifyHandler::registerAsQml(){
    qmlRegisterType<QsVerifyHandler>(QsImpports::cppItems(),1,0,"VerificationHandler");
}

QsVerifyHandler::QsVerifyHandler(QObject *parent) : QObject(parent)
  ,msgService(Qs::instance().msgService())
{

}

//qreal QsVerifyHandler::verifyResults(QsVerifyHandler::ResultCode code){
//	switch (code) {
//		case PartialOrderReduction: return _results->fullStatespaceFor().partialOrderReduction;
//		case NeverClaim: return _results->fullStatespaceFor().neverClaim;
//		case AssertionVioLations: return _results->fullStatespaceFor().assertionViolations;
//		case AcceptanceCycles: return  _results->fullStatespaceFor().acceptanceCycles;
//		case InvalidEndStates: return _results->fullStatespaceFor().invalidEndStates;
//		default: qFatal("not a verification result");
//	}
//}
