#ifndef QSOBJECTBASE_H
#define QSOBJECTBASE_H
#include <QObject>
#include <QDebug>
#include <QMetaType>
class Qs;
class EventAggregator;
#include "qspin/EventObjects.h"
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
    void toConsole(QString message,PrintToConsole::MessageType type=PrintToConsole::Normal);
    static Qs& qs();
    // u
};

#include "qspin/Qs.h"
#include "viewModels/EventAggregator.h"
#endif // QSOBJECTBASE_H
