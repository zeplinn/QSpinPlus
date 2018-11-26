#ifndef QOBJECTLISTBASE_H
#define QOBJECTLISTBASE_H
#include <QObject>
#include <QAbstractListModel>
class Qs;
class EventAggregator;
class QObjectListBase: public QAbstractListModel{
Q_OBJECT
    EventAggregator* _msgService;
public:
    explicit QObjectListBase(QObject* parent = nullptr,EventAggregator* msgService = nullptr);
    EventAggregator* msgService()const;
    void setMsgService(EventAggregator* service)
    {
        if(service != nullptr)
            _msgService=nullptr;
    }
    void toConsole(QString message);
    static Qs& qs();
    // u
protected:

};

#include "qspin/Qs.h"
#include "viewModels/EventAggregator.h"
#include "qspin/EventObjects.h"
#endif // QOBJECTLISTBASE_H
