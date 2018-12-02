#include "qspin/models/QueuedVerification.h"

QueuedVerification::QueuedVerification(QFileInfo info, QDateTime createdAt, QObject *parent, EventAggregator* msgService):QObjectBase (parent,msgService) {
    _status = QsSpinRunner::Waiting;
    _fileInfo = info;
    _createdAt = createdAt;


    _baseName = info.baseName();
    _baseName = qs().extractResultFileBaseName(info.fileName());

}

QueuedVerification::~QueuedVerification() {

}

QString QueuedVerification::name() const{ return  _baseName;}

QDateTime QueuedVerification::createdAt() const {return _createdAt;}

QDateTime QueuedVerification::startedAt(){return _startedAt;}

QString QueuedVerification::statusLabel() const{
    switch (_status) {
    case QsSpinRunner::Waiting: return "Waiting";
    case QsSpinRunner::Running: return "Running";
    case QsSpinRunner::Finished: return "Finished";
    case QsSpinRunner::FileNotFound: return "File not found";
    case QsSpinRunner::Error: return "Error";
    case QsSpinRunner::Canceled: return  "Canceled";
    case QsSpinRunner::Starting: return  "Starting";
    }
    return  "unkwon Status";
}

QFileInfo QueuedVerification::fileInfo(){ return _fileInfo; }

QsSpinRunner::Status QueuedVerification::status() const{ return _status;}

void QueuedVerification::setStatus(QsSpinRunner::Status value){
    _status = value;
    emit variablesChanged(this);
}

void QueuedVerification::setStartedAt(QDateTime startedAt){
    _startedAt = startedAt;
    emit variablesChanged(this);
}

void QueuedVerification::cancelVerifcation(){
    emit verificationCanceled(QsSpinRunner::Canceled);
}
