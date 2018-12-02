#include "qspin/QObjectBase.h"

QObjectBase::QObjectBase(QObject *parent, EventAggregator *msgService)
    :QObject (parent)
    ,_msgService(msgService)
{
    if(_msgService== nullptr){
        _msgService = qs().msgService();
    }
}

EventAggregator *QObjectBase::msgService() const {return _msgService;}

void QObjectBase::toConsole(QString message, PrintToConsole::MessageType type){
    msgService()->publish(PrintToConsole(message,type));
}

Qs &QObjectBase::qs(){ return Qs::instance(); }

