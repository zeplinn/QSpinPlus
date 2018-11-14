#include "qspin/viewModels/QsConsoleHandler.h"
QQuickTextDocument*QsConsoleHandler::document() const{ return _txtDocument;}

void QsConsoleHandler::setDocument(QQuickTextDocument*value){
	_txtDocument = value;
	emit documentChanged();
}

QsConsoleHandler::QsConsoleHandler(QObject*parent, EventAggregator*msgService):QObject(parent){
	msgService->subscribe(this);
}

void QsConsoleHandler::subscriber(const PrintToConsole&event){
	emit messageSend(event.message());
}
