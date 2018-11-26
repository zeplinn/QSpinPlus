#ifndef QSOBJECTBASE_H
#define QSOBJECTBASE_H
#include <QObject>
#include <QDebug>
#include <QMetaType>
class Qs;
class EventAggregator;
class QObjectBase: public QObject{
    Q_OBJECT
    EventAggregator* _msgService;
public:
    explicit QObjectBase(QObject* parent = nullptr,EventAggregator* msgService = nullptr);
    EventAggregator* msgService()const;
    void setMsgService(EventAggregator* service)
    {
        if(service != nullptr)
            _msgService=nullptr;
    }
    void toConsole(QString message);
    static Qs& qs();
    // u
};

#include "qspin/Qs.h"
#include "viewModels/EventAggregator.h"
#include "qspin/EventObjects.h"
#endif // QSOBJECTBASE_H
