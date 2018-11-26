#include "qspin/viewModels/QsConsoleHandler.h"
QQuickTextDocument*QsConsoleHandler::document() const{ return _txtDocument;}

void QsConsoleHandler::setDocument(QQuickTextDocument*value){
	_txtDocument = value;
	emit documentChanged();
}

QsConsoleHandler::QsConsoleHandler(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
{
    this->msgService()->subscribe<PrintToConsole>(this);
}

void QsConsoleHandler::subscriber(const PrintToConsole&event){
    emit messageSend(event.message());
}
