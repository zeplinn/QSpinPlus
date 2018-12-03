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
            ,this,&QsSpinQueueHandler::addNewQueueItem_asyncOnly
            ,Qt::QueuedConnection);
    connect(this,&QsSpinQueueHandler::removingQueuedItem
            ,this,&QsSpinQueueHandler::removeQueuedItem_asyncOnly
            ,Qt::QueuedConnection);

}


void QsSpinQueueHandler::subscriber(const ProjectOpened &event){
    if(event.project()== nullptr){
        qFatal("qspin queue cannot open nullpointer project");
    }
    if(_project!=event.project()){
        _project = event.project();
        if(!_project->queuedDir().isEmpty()){
            qs().removeFiles(_project->queuedDir());
        }
    }
}

void QsSpinQueueHandler::subscriber(const ProjectClosed &event){
    Q_UNUSED(event);
    _verifyQueue->clear();
    _project = nullptr;
}

void QsSpinQueueHandler::startVerification(QueuedVerification *item){
    if(item->status()!= QsSpinRunner::Waiting) return;
    item->setStatus(QsSpinRunner::Starting);
    auto runner = new QsSpinRunner(
                item->fileInfo()
                ,_project->FullProjectInformation()
                ,msgService()
                );

    item->setStartedAt(QDateTime::currentDateTime());

    auto thread = new QThread();
    runner->moveToThread(thread);
    // on verification finsihed send result destination file
    connect(runner,&QsSpinRunner::resultCreated
            ,this,&QsSpinQueueHandler::sendVerificationResult
            );

    // connect queued item with spin runner
    connect(runner,&QsSpinRunner::statusUpdated
            ,item,&QueuedVerification::setStatus
            );
    connect(item,&QueuedVerification::verificationCanceled
            ,runner,&QsSpinRunner::terminateProcess
            );

    // terminate thread on job finished
    connect(runner,&QsSpinRunner::finished
            ,thread,&QThread::quit
            );


    // clean up thread and spin runner object when done
    connect(thread,&QThread::finished
            ,runner,&QsSpinRunner::deleteLater
            );
    connect(thread,&QThread::finished
            ,thread,&QThread::deleteLater
            );

    // connect handler to process message chhannels
    connect(runner,&QsSpinRunner::stdOutReady,
            this,&QsSpinQueueHandler::spinProcessOutputReady);
    connect(runner,&QsSpinRunner::stdErrOutReady,
            this,&QsSpinQueueHandler::spinProcessStdErrorOutReady);


    //start next verification if any queued item available
    // when verification object is destroyed
    connect(runner,&QsSpinRunner::destroyed
            ,this,&QsSpinQueueHandler::startNextQueuedVerification
            );



    // execute run() on thread started
    connect(thread,&QThread::started,runner,&QsSpinRunner::runVerify);
    thread->start();

}

void QsSpinQueueHandler::subscriber(const AppendToVeriyQueue &event){
    auto f = event;
    emit addingNewQueueItem(f.fileInfo(),f.createdAt());
}

void QsSpinQueueHandler::subscriber(const ProjectSaved &event)
{
    if(event.project()!=_project){
        _verifyQueue->clear();
    }
}

void QsSpinQueueHandler::addNewQueueItem_asyncOnly(QFileInfo info, QDateTime createdAt){
    auto item = new QueuedVerification(info,createdAt);
    _verifyQueue->append(item);
    if(_verifyQueue->rowCount()==1){
        startVerification(item);
    }


}

void QsSpinQueueHandler::removeQueuedItem_asyncOnly(QueuedVerification *item){
    int idx = verifyQueue()->position(item);
    item->cancelVerifcation(); // safe call no need for gaurds
    verifyQueue()->removeItem(idx);

    if(idx ==0 && verifyQueue()->rowCount()>0){
        auto first = verifyQueue()->get(0);
        if( first->status() == QsSpinRunner::Waiting){
            startVerification(first);
        }
    }
}

void QsSpinQueueHandler::spinProcessOutputReady(QString stdOut){
    toConsole(stdOut);
}

void QsSpinQueueHandler::spinProcessStdErrorOutReady(QString stdErr){
    toConsole(stdErr);
}

void QsSpinQueueHandler::sendVerificationResult(QFileInfo file, VerificationResultFileChanged::Status status){
    msgService()->publish(
                VerificationResultFileChanged(file
                                              ,status)
                );
}
