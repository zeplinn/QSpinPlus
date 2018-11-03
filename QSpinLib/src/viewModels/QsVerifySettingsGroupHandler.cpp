#include "qspin/viewModels/QsVerifySettingsGroupHandler.h"

VerificationConfiguration *QsVerifySettingsGroupHandler::item() const{return _item;}

void QsVerifySettingsGroupHandler::setReference(VerificationConfiguration *value){
    if(_item != value){
        _item = value;
        emit referenceChanged();
    }
}

QsVerifySettingsGroupHandler::QsVerifySettingsGroupHandler(QObject *parent):QObject(parent), _item(new VerificationConfiguration(this)){}
