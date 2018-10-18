#ifndef QSVERIFICATIONRESULTS_H
#define QSVERIFICATIONRESULTS_H

#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
#include <memory>


// this struct only deals with with truth false values indicated by + or -
struct fullStateSpaceFor{
        bool const  partialOrderReduction =0;
        bool const  neverClaim =0;
        bool const  assertionViolations =0;
        bool const  acceptanceCycles =0;
        bool const  invalidEndStates =0;
        fullStateSpaceFor(QString results);
};
struct fullStateSpaceSpecifications{
		qreal const  depthReached =0;
		qreal const  storedStates =0;
        qreal const  matchedStates =0;
		qreal const  transitionsTaken =0;
		qreal const  atomicSteps =0;
		qreal const  stateSize =0;
		qreal const  hashConflicts =0;
		qreal const  hashSize =0;
        fullStateSpaceSpecifications(QString results);


};
struct memoryUsage{
		qreal const  forStates =0;
		qreal const  forHashTable =0;
		qreal const  forSearchStack =0;
		qreal const  inTotal =0;
        memoryUsage(QString results);

};
class QsVerificationResults
{
		//Full stateSpace search
	fullStateSpaceFor _stateSpaceFor;
	fullStateSpaceSpecifications _stateSpaceSpec;
    memoryUsage _memUsage;
	public:
        explicit QsVerificationResults(const QString results);
	const fullStateSpaceFor& fullStatespaceFor()const{return _stateSpaceFor;}
	const fullStateSpaceSpecifications& fullStatespaceSpecifications()const{return _stateSpaceSpec;}
    const memoryUsage& memoryUsed()const{ return _memUsage;}
	signals:

	public slots:
};
typedef std::shared_ptr<QsVerificationResults> verifyResult_ptr;

// eventAgregator container


#endif // QSVERIFICATIONRESULTS_H
