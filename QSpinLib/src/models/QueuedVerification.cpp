#include "qspin/models/QueuedVerification.h"

QueuedVerification::QueuedVerification(QFileInfo info, QDateTime createdAt, QObject *parent):QObject (parent) {
    _status = QsSpinRunner::Waiting;
    _fileInfo = info;
    _createdAt = createdAt;
    _baseName = info.baseName();

    connect(&t,&QThread::finished,&t,&QThread::quit);
}

QueuedVerification::~QueuedVerification() {

}

QString QueuedVerification::name() const{ return  _baseName;}

QDateTime QueuedVerification::createdAt() const {return _createdAt;}

QString QueuedVerification::statusLabel() const{
    switch (_status) {
    case QsSpinRunner::Waiting: return "Waiting";
    case QsSpinRunner::Running: return "Running";
    case QsSpinRunner::Finished: return "Finished";
    case QsSpinRunner::FileNotFound: return "File not found";
    case QsSpinRunner::Error: return "Error";
    }
}

QsSpinRunner::Status QueuedVerification::status() const{ return _status;}

void QueuedVerification::setStatus(QsSpinRunner::Status value){
    _status = value;
    emit variablesChanged(this);
}
void QueuedVerification::terminate(){}

void QueuedVerification::start(QDir workingdir){
    if(_status == QsSpinRunner::Waiting){
        setStatus(QsSpinRunner::Running);
        if(_runner.isNull())
            _runner = new QsSpinRunner(_fileInfo,workingdir);
        _runner->moveToThread(&t);
        connect(_runner,&QsSpinRunner::finished
                ,this,&QueuedVerification::verificationFinished
                ,Qt::QueuedConnection);

        t.start();
    }
}

void QueuedVerification::remove(){
    emit removedFromQueue(this);
}

void QueuedVerification::verificationStarted(){
    _runner->run();

    _runner->deleteLater();
}

void QueuedVerification::verificationFinished(){
    emit removedFromQueue(this);
}

void QueuedVerification::statusUpdated(QsSpinRunner::Status update){

}
