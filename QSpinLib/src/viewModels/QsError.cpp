#include "qspin/viewModels/QsError.h"

QsError::QsError(QObject *parent) : QObject(parent)
{

}

void QsError::registerAsQml(){
    qmlRegisterUncreatableType<QsError>(QsImpports::cppItems(),1,0,"QsErrors","only contain enum and constant string messeages");
}

QString QsError::message(QsError::Errors code){
	switch (code) {
		case SaveDocument: return "Failed to save document";
		case OpenDocument: return "failed to open document";
		default: return  "Unkown error occured";
	}
}
