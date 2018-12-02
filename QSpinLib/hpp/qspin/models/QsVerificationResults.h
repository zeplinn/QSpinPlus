#ifndef QSVERIFICATIONRESULTS_H
#define QSVERIFICATIONRESULTS_H

#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
#include <memory>
#include <QTime>
#include "qspin/QObjectBase.h"
#include "qspin/models/IQsSerialization.h"
#include <string>
#include <functional>
using namespace std::placeholders;
// this struct only deals with with truth false values indicated by + or -
class FullStateSpaceFor: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    Q_PROPERTY(bool partialOrderReduction READ partialOrderReduction WRITE setPartialOrderReduction NOTIFY partialOrderReductionChanged)
    bool _partialOrderReduction;
    Q_PROPERTY(bool neverClaim READ neverClaim WRITE setNeverClaim NOTIFY neverClaimChanged)
    bool _neverClaim;
    Q_PROPERTY(bool assertionViolations READ assertionViolations WRITE setAssertionViolations NOTIFY assertionViolationsChanged)
    bool _assertionViolations;
    Q_PROPERTY(bool acceptanceCycles READ acceptanceCycles WRITE setAcceptanceCycles NOTIFY acceptanceCyclesChanged)
    bool _acceptanceCycles;
    Q_PROPERTY(bool invalidEndStates READ invalidEndStates WRITE setInvalidEndStates NOTIFY invalidEndStatesChanged)
    bool _invalidEndStates;


public:
    bool partialOrderReduction()const;
    void setPartialOrderReduction(bool value);
    bool neverClaim()const;
    void setNeverClaim(bool value);
    bool assertionViolations()const;
    void setAssertionViolations(bool value);
    bool acceptanceCycles()const;
    void setAcceptanceCycles(bool value);
    bool invalidEndStates()const;
    void setInvalidEndStates(bool value);
signals:
    void partialOrderReductionChanged();
    void neverClaimChanged();
    void assertionViolationsChanged();
    void acceptanceCyclesChanged();
    void invalidEndStatesChanged();
private:
public:
    FullStateSpaceFor(QObject* parent = nullptr, EventAggregator* msg = nullptr);
//    void extractResult(const QString& results){
//        //    setPartialOrderReduction(static_cast<bool>(extract(results,"([+-])\\s*Partial")));
//        //    setNeverClaim(static_cast<bool>(extract(results,"claim\\s*([+-])")));
//        //    setAssertionViolations(static_cast<bool>(extract(results,"violations\\s*([+-])")));
//        //    setAcceptanceCycles(static_cast<bool>(extract(results,"cycles\\s*([+-])")));
//        //    setInvalidEndStates(static_cast<bool>(extract(results,"states\\s*([+-])")));
//    }
    // IQXmlSerialization interface
public:
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
};



class FullStateSpaceSpecifications: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    Q_PROPERTY(qreal depthReached READ depthReached WRITE setDepthReached NOTIFY depthReachedChanged)
    qreal _depthReached;
    Q_PROPERTY(qreal storedStates READ storedStates WRITE setStoredStates NOTIFY storedStatesChanged)
    qreal _storedStates;
    Q_PROPERTY(qreal matchedStates READ matchedStates WRITE setMatchedStates NOTIFY matchedStatesChanged)
    qreal _matchedStates;
    Q_PROPERTY(qreal transitionTaken READ transitionTaken WRITE setTransitionTaken NOTIFY transitionTakenChanged)
    qreal _transitionTaken;
    Q_PROPERTY(qreal atomicSteps READ atomicSteps WRITE setAtomicSteps NOTIFY atomicStepsChanged)
    qreal _atomicSteps;
    Q_PROPERTY(qreal stateSize READ stateSize WRITE setStateSize NOTIFY stateSizeChanged)
    qreal _stateSize;
    Q_PROPERTY(qreal hashConflicts READ hashConflicts WRITE setHashConflicts NOTIFY hashConflictsChanged)
    qreal _hashConflicts;
    Q_PROPERTY(qreal hashSize READ hashSize WRITE setHashSize NOTIFY hashSizeChanged)
    qreal _hashSize;


public:
    qreal atomicSteps()const;
    void setAtomicSteps(qreal value);
    qreal depthReached()const;
    void setDepthReached(qreal value);
    qreal storedStates()const;
    void setStoredStates(qreal value);
    qreal matchedStates()const;
    void setMatchedStates(qreal value);
    qreal transitionTaken()const;
    void setTransitionTaken(qreal value);

    qreal stateSize()const;
    void setStateSize(qreal value);
    qreal hashConflicts()const;
    void setHashConflicts(qreal value);
    qreal hashSize()const;
    void setHashSize(qreal value);
signals:
    void depthReachedChanged();
    void storedStatesChanged();
    void matchedStatesChanged();
    void transitionTakenChanged();
    void atomicStepsChanged();
    void stateSizeChanged();
    void hashConflictsChanged();
    void hashSizeChanged();
public:
//    void extractResult(const QString& results){
//        //    setDepthReached(extract(results,"depth reached ([0-9+e.]*)"));
//        //    setStoredStates(extract(results,"([0-9+e.]*) states, stored"));
//        //    setMatchedStates(extract(results,"([0-9+e.]*) states, matched"));
//        //    setTransitionTaken(extract(results,"([0-9+e.]*) transitions"));
//        //    setAtomicSteps(extract(results,"([0-9+e.]*) atomic steps"));
//        //    setStateSize(extract(results,"State-vector ([0-9+e.]*) byte"));
//        //    setHashConflicts(extract(results,"hash conflicts:\\s* ([0-9+e.]*)"));
//        //    setHashSize(extract(results,"memory used for hash table \\(-w(\\d+)\\)"));
//    }
    FullStateSpaceSpecifications(QObject* parent= nullptr,EventAggregator* msg = nullptr);



    // IQXmlSerialization interface
public:
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
};



class MemoryUsage: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    Q_PROPERTY(qreal forStates READ forStates WRITE setForStates NOTIFY forStatesChanged)
    qreal _forStates;
    Q_PROPERTY(qreal forHashTable READ forHashTable WRITE setForHashTable NOTIFY forHashTableChanged)
    qreal _forHashTable;
    Q_PROPERTY(qreal forSearchStack READ forSearchStack WRITE setForSearchStack NOTIFY forSearchStackChanged)
    qreal _forSearchStack;
    Q_PROPERTY(qreal inTotal READ inTotal WRITE setInTotal NOTIFY inTotalChanged)
    qreal _inTotal;


public:
    qreal forStates()const;
    void setForStates(qreal value);
    qreal forHashTable()const;
    void setForHashTable(qreal value);
    qreal forSearchStack()const;
    void setForSearchStack(qreal value);
    qreal inTotal()const;
    void setInTotal(qreal value);
signals:
    void forStatesChanged();
    void forHashTableChanged();
    void forSearchStackChanged();
    void inTotalChanged();
public:
    MemoryUsage(QObject* parent = nullptr, EventAggregator* msg = nullptr);
//    void extractResult(const QString& results){
//        //    setForStates(extract(results,"(\\d+\\.\\d+)\\s+actual\\s+memory\\s+usage\\s+for\\s+states"));
//        //    setForHashTable(extract(results,"(\\d+\\.\\d+)\\s+memory\\s+used\\s+for\\s+hash\\s+table"));
//        //    setForSearchStack(extract(results,"(\\d+\\.\\d+)\\s+memory\\s+used\\s+for\\s+.FS\\s+stack"));
//        //    setInTotal(extract(results,"(\\d+\\.\\d+)\\s+total\\s+actual\\s+memory\\s+usage"));
//    }


    // IQXmlSerialization interface
public:
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
};

class ResultMatch{
protected:
    QRegularExpression regex;
    bool _isRead=true;
public:
    virtual bool isMatch(const QString& result)=0;
    explicit ResultMatch(const QString& pattern)
        :regex(QRegularExpression(pattern))
    {}
    virtual ~ResultMatch(){}

};



class ResultMatchReal: public ResultMatch{

    std::function<void(qreal)>_func;
public:
    explicit ResultMatchReal(const QString& pattern,std::function<void(qreal)> func)
        : ResultMatch(pattern)
        ,_func(func)
    {}
    virtual bool isMatch(const QString& result)override;
};


class ResultMatchBool: public ResultMatch{

    std::function<void(bool)>_func;
    void *(*_func2)(bool);
public:
    explicit ResultMatchBool(const QString& pattern,std::function<void(bool)> func)
        : ResultMatch(pattern)
        ,_func(func)
    {}
    //explicit ResultMatchBool(const QString& pattern,void*(*func)(bool))
    //    : ResultMatch(pattern)
    //    ,_fun2c(func)
    //{}
    virtual bool isMatch(const QString& result)override;
};

class ResultMatchString: public ResultMatch{
    std::function<void(QString str)> _func;
public:
    explicit ResultMatchString(const QString& pattern,std::function<void(QString str)> func);
    virtual bool isMatch(const QString& result)override;
};

class VerificationResults:public QObjectBase, public IQXmlSerialization
{
    Q_OBJECT
    //Full stateSpace search
    Q_PROPERTY(FullStateSpaceFor* stateSpaceFor READ stateSpaceFor CONSTANT)
    FullStateSpaceFor* _stateSpaceFor;
    Q_PROPERTY(FullStateSpaceSpecifications* stateSpaceSpec READ stateSpaceSpec CONSTANT)
    FullStateSpaceSpecifications* _stateSpaceSpec;
    Q_PROPERTY(MemoryUsage* memoryUsage READ memoryUsage CONSTANT)
    MemoryUsage* _memoryUsage;
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
    QString _version;
    Q_PROPERTY(QString unreachedStates READ unreachedStates NOTIFY unreachedStatesChanged)
    QString _unreachedStates;
    Q_PROPERTY(qreal errorCount READ errorCount NOTIFY errorCountChanged)
    qreal _errorCount;
    Q_PROPERTY(QString elapsedTime READ elapsedTime NOTIFY elapsedTimeChanged)
    QTime _elapsedTime;




public:
    FullStateSpaceSpecifications* stateSpaceSpec()const;
    FullStateSpaceFor* stateSpaceFor()const;
    MemoryUsage* memoryUsage()const;

    QString version()const;
    void setVersion(QString value);
    QString unreachedStates()const;
    void setUnreachedStates(QString value);
    qreal errorCount()const;
    void setErrorCount(qreal value);
    QString elapsedTime()const;
    void setElapsedTime(QTime value);

signals:
    void versionChanged();
    void unreachedStatesChanged();
    void errorCountChanged();
    void elapsedTimeChanged();
private:
    QList<ResultMatch*> _matches;
    QRegularExpression _versionRegex;
    QString _rawReport;
public:
    explicit VerificationResults(QObject* parent = nullptr, EventAggregator* msg = nullptr);
    //    virtual ~VerificationResults()override{
    //        QObjectBase::~QObjectBase();
    //        clearRegexPatterns();
    //    }
    void constructRegexPatterns();
    void clearRegexPatterns();
    void extractVerificationResults(const QString& results);
    bool isFirstMatch(const QString &result);
    QString assertionViolations(const QString& result){
        QRegularExpression regex("(.|[\\r\\n])*(?=( \\(Spin Version ([0-9]+\\.?)+ -- 2 March [0-9]{4}\\)))");
        auto m = regex.match(result);
        return m.captured();
    }
    // IQXmlSerialization interface
public:
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
public slots:
    QString rawReport();
};
typedef std::shared_ptr<VerificationResults> verifyResult_ptr;

// eventAgregator container


#endif // QSVERIFICATIONRESULTS_H
