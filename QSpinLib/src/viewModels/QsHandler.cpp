#include "qspin/viewModels/QsHandler.h"

void QsHandler::registerAsQml(){
    qmlRegisterType<QsHandler>(QsImpports::cppItems(),1,0,"QsHandler");
}

QsHandler::QsHandler(QObject *parent) : QObject(parent)
{

}
