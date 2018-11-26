#include "qspin/QObjectListBase.h"

QObjectListBase::QObjectListBase(QObject *parent, EventAggregator *msgService)
    :QAbstractListModel(parent)
    ,_msgService(msgService)
{
    if(_msgService== nullptr){
        _msgService = qs().msgService();
    }
}

EventAggregator *QObjectListBase::msgService() const {return _msgService;}

void QObjectListBase::toConsole(QString message){
    msgService()->publish(PrintToConsole(message));
}

Qs &QObjectListBase::qs(){ return Qs::instance(); }

