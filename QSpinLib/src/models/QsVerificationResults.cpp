#include "qspin/models/QsVerificationResults.h"

namespace{
    qreal extract(QString results, const char pattern[]){
        QRegularExpression regx;
        regx.setPattern(pattern);
        QRegularExpressionMatch m = regx.match(results);

        if(m.hasMatch()){
            QString r = m.captured(1);
            if      ( r == "+" )    return true;
            else if ( r == "-" )    return false;
            else                    return r.toDouble();
        }
        return  0;
    }
}

QsVerificationResults::QsVerificationResults(const QString results)
    :_stateSpaceFor(results)
    ,_stateSpaceSpec(results)
    ,_memUsage(results)
{

}
fullStateSpaceFor::fullStateSpaceFor(QString results)
    :partialOrderReduction(static_cast<bool>(extract(results,"([+-])\\s*Partial")))
    ,neverClaim(static_cast<bool>(extract(results,"claim\\s*([+-])")))
    ,assertionViolations(static_cast<bool>(extract(results,"violations\\s*([+-])")))
    ,acceptanceCycles(static_cast<bool>(extract(results,"cycles\\s*([+-])")))
    ,invalidEndStates(static_cast<bool>(extract(results,"states\\s*([+-])")))
{}


fullStateSpaceSpecifications::fullStateSpaceSpecifications(QString results)
    :depthReached(extract(results,"depth reached ([0-9+e.]*)"))
    ,storedStates(extract(results,"([0-9+e.]*) states, stored"))
    ,matchedStates(extract(results,"([0-9+e.]*) states, matched"))
    ,transitionsTaken(extract(results,"([0-9+e.]*) transitions"))
    ,atomicSteps(extract(results,"([0-9+e.]*) atomic steps"))
    ,stateSize(extract(results,"State-vector ([0-9+e.]*) byte"))
    ,hashConflicts(extract(results,"hash conflicts:\\s* ([0-9+e.]*)"))
    ,hashSize(extract(results,"memory used for hash table \\(-w(\\d+)\\)"))
{}

memoryUsage::memoryUsage(QString results)
    :forStates(extract(results,"(\\d+\\.\\d+)\\s+actual\\s+memory\\s+usage\\s+for\\s+states"))
    ,forHashTable(extract(results,"(\\d+\\.\\d+)\\s+memory\\s+used\\s+for\\s+hash\\s+table"))
    ,forSearchStack(extract(results,"(\\d+\\.\\d+)\\s+memory\\s+used\\s+for\\s+.FS\\s+stack"))
    ,inTotal(extract(results,"(\\d+\\.\\d+)\\s+total\\s+actual\\s+memory\\s+usage"))
{}
