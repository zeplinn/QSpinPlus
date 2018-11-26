#include "qspin/viewModels/QsSpinQueueHandler.h"


bool QsSpinQueueHandler::isRunning() const{ return _isRunning; }

void QsSpinQueueHandler::setIsRunning(bool value){
    if(_isRunning != value){
        _isRunning = value;
        emit isRunningChanged();
    }
}

VerificationQueue *QsSpinQueueHandler::verifyQueue() const{ return _verifyQueue; }

QsSpinQueueHandler::QsSpinQueueHandler(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
    ,_verifyQueue(new VerificationQueue(this,msgService))
{
    this->msgService()->subscribe<AppendToVeriyQueue>(this);
    this->msgService()->subscribe<ProjectOpened>(this);
    this->msgService()->subscribe<ProjectClosed>(this);

    // ensures that queuedVerifictions always are added on the main thread
    connect(this,&QsSpinQueueHandler::addingNewQueueItem
            ,this,&QsSpinQueueHandler::addNewQueueItem
            ,Qt::QueuedConnection);
}


void QsSpinQueueHandler::subscriber(const ProjectOpened &event){
    if(_project.data()!=event.project())
        _project = event.project();
    _verifyQueue->setbuildDir(_project->binDir());
}

void QsSpinQueueHandler::subscriber(const ProjectClosed &event){
    Q_UNUSED(event);
    _project = nullptr;
    _verifyQueue->setbuildDir(QDir());
}

void QsSpinQueueHandler::statusUpdated(){
}

void QsSpinQueueHandler::verificationRequsted(){}

void QsSpinQueueHandler::subscriber(const AppendToVeriyQueue &event){
    auto f = event;
    emit addingNewQueueItem(f.fileInfo(),f.createdAt());
}

void QsSpinQueueHandler::addNewQueueItem(QFileInfo info, QDateTime createdAt){
    _verifyQueue->append(new QueuedVerification(info,createdAt));


}
