#ifndef QSVERIFYRESULTREPORTHANDLER_H
#define QSVERIFYRESULTREPORTHANDLER_H
#include "qspin/QObjectBase.h"
#include "qspin/models/QsVerificationResults.h"
class QsVerifyResultReportHandler: public QObjectBase
{
Q_OBJECT
    Q_PROPERTY(VerificationResults* reference READ reference WRITE setReference NOTIFY referenceChanged)
    VerificationResults* _reference;
    Q_PROPERTY(VerificationResults* item READ item NOTIFY itemChanged)
    VerificationResults* _item;

public:
    VerificationResults* reference()const{ return _reference; }
    void setReference(VerificationResults* value){

            _reference = value;
            emit referenceChanged();
            setItem(value);

    }
    VerificationResults* item()const{ return _item != nullptr ? _item : _defaultResults; }
    void setItem(VerificationResults* value){
            _item = value;
            emit itemChanged();        
    }
signals:
    void referenceChanged();
    void itemChanged();

private:
    VerificationResults* _defaultResults;
public:
    QsVerifyResultReportHandler(QObject* parent = nullptr , EventAggregator* msg =nullptr)
        : QObjectBase(parent,msg)
        ,_reference(nullptr)
        ,_item(nullptr)
        ,_defaultResults(new VerificationResults(this,msgService()))
    {}
};
#endif // QSVERIFYRESULTREPORTHANDLER_H
