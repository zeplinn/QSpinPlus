#include "qspin/viewModels/QsVerifyResultHandler.h"

QsVerifyResultList *QsVerifyResultHandler::results() const{ return _resultList; }

VerificationResultContainer *QsVerifyResultHandler::currentItem() const{ return _currentItem; }

void QsVerifyResultHandler::setCurrentItem(VerificationResultContainer *value){
    _currentItem = value;
    emit currentItemChanged();
    if(_currentItem!=nullptr)
        setSelectedResults(_currentItem->VerificationReport());
    else
        setSelectedResults(nullptr);

}

VerificationResults *QsVerifyResultHandler::selectedResults() const{ return   _selectedResults; }

void QsVerifyResultHandler::setSelectedResults(VerificationResults *value){
    _selectedResults = value;
    emit selectedResultsChanged();

}

int QsVerifyResultHandler::currentIndex() const{ return _currentIndex; }

void QsVerifyResultHandler::setCurrentIndex(int value){
    _currentIndex = value;
    emit currentIndexChanged();
    if(value>=0)
        setCurrentItem(_resultList->get(value));
    else setCurrentItem(nullptr);// safe call
}

QString QsVerifyResultHandler::spinCommands() const{
    if(currentItem()==nullptr) return "";
    auto cmds = currentItem()->commands().CommandsToStringLists();
    return cmds.spin.join("  ");
}

QString QsVerifyResultHandler::gccCommands() const{
    if(currentItem()==nullptr) return "";
    auto cmds = currentItem()->commands().CommandsToStringLists();
    return cmds.gcc.join("  ");
}

QString QsVerifyResultHandler::panCommands() const{
    if(currentItem()==nullptr) return "";
    auto cmds = currentItem()->commands().CommandsToStringLists();
    return cmds.pan.join("  ");

}

QString QsVerifyResultHandler::unreached() const{
    if(currentItem()==nullptr) return "";
    return currentItem()->VerificationReport()->unreachedStates();
}

QsVerifyResultHandler::QsVerifyResultHandler(QObject *parent, EventAggregator *msg)
    :QObjectBase(parent,msg)
    ,_currentItem(nullptr)
    ,_selectedResults(nullptr)
    ,_resultList(new QsVerifyResultList(this,msgService()))
    ,_project(nullptr)
    ,_fileWatcher(new QFileSystemWatcher(this))
{
    msgService()->subscribe<VerificationResultFileChanged>(this);
    msgService()->subscribe<ProjectOpened>(this);
    msgService()->subscribe<ProjectSaved>(this);
    msgService()->subscribe<ProjectClosed>(this);
    connect(_fileWatcher,&QFileSystemWatcher::fileChanged
            ,this,&QsVerifyResultHandler::fileUpdated);
}

void QsVerifyResultHandler::subscriber(const ProjectOpened &event){
    if(event.project() == nullptr)
        qFatal("verify result handler cannot open a project with a nullpointer");
    if(event.project()!= _project){
        // add folder to listen to
        auto files = _fileWatcher->files();
        if(!files.isEmpty())
            _fileWatcher->removePaths(files);

        auto nfiles = event.project()->resultsDir().entryInfoList({"*.qspr"},QDir::Files | QDir::NoDotAndDotDot);
        _watchedFiles.clear();
        setCurrentIndex(-1);
        _resultList->clear();
        for(auto f : nfiles){
            _fileWatcher->addPath(f.absoluteFilePath());
            fileUpdated(f.absoluteFilePath());
        }
        _project=event.project();
    }


}

void QsVerifyResultHandler::subscriber(const ProjectSaved &event){
    if(event.project() == nullptr)
        qFatal("verify result handler cannot save a project with a nullpointer");
    if(_project!= event.project()){
        // clear list
        auto files = _fileWatcher->files();
        if(!files.isEmpty())
            _fileWatcher->removePaths(files);


        auto nfiles = event.project()->resultsDir().entryInfoList({"*.qspr"},QDir::Files | QDir::NoDotAndDotDot);
        if(!_watchedFiles.isEmpty()){
            _watchedFiles.clear();
        }
        if(! (_resultList->rowCount()>0))
            _resultList->clear();
        for(auto f : nfiles){
            _fileWatcher->addPath(f.absoluteFilePath());
            fileUpdated(f.absoluteFilePath());
        }
        //auto files =
        //remove folder to listen to
        // add new folder to listen to
        setCurrentIndex(-1);
        _project = event.project();
    }
}

void QsVerifyResultHandler::subscriber(const ProjectClosed &event){
    Q_UNUSED(event)
    setCurrentIndex(-1); // clears all related to at current item
    auto files = _fileWatcher->files();
    _fileWatcher->removePaths(files);
    if(!_watchedFiles.isEmpty())
        _watchedFiles.clear();
    if(_resultList->rowCount()>0)
        _resultList->clear();
    setCurrentIndex(-1);
    _project = nullptr;
    // clear list
    // remove folder to listen to
}

void QsVerifyResultHandler::subscriber(const VerificationResultFileChanged &event){
    auto e = event;
    if(e.status()==VerificationResultFileChanged::Created)
        fileUpdated(e.destination().absoluteFilePath());
    else if (e.status() == VerificationResultFileChanged::Deleted){
        QFile::remove(e.destination().absoluteFilePath());
    }
}

void QsVerifyResultHandler::remove(int index){
    auto item = _resultList->get(index);
    if( currentIndex()== index)
        setCurrentIndex(-1);
    QFile::remove(item->filename().absoluteFilePath());
}

bool QsVerifyResultHandler::compareToCurrentDocument(){
    if(_project!= nullptr && currentItem()!= nullptr){
        return _project->currentDocument() == currentItem()->document();
    }
    return false;
}

QString QsVerifyResultHandler::getXmlReport(){
    if(_project!=nullptr && currentItem()!= nullptr){
        return qs().readTextFile(currentItem()->filename().absoluteFilePath());
    }
    return "";
}

void QsVerifyResultHandler::fileUpdated(QString path){
    QFileInfo fi(path);
    if(fi.suffix()!= "qspr") return;
    auto basename  = qs().extractResultFileBaseName(fi.fileName());
    bool isValid;
    auto createdAt = qs().extractEpochSinceFromFile(fi.fileName(),&isValid);
    auto epoch = qs().getTimeSinceEpochFrom(createdAt);
    if(!isValid){
        toConsole("invalid result file. %"+fi.absoluteFilePath());
        return;
    }

    if(fi.exists()){
        if(!_watchedFiles.contains(epoch)){
            _watchedFiles[qs().getTimeSinceEpochFrom(createdAt)]=true;
            _fileWatcher->addPath(fi.absoluteFilePath());
            //auto item = new VerificationResultContainer(this,msgService());
            //qs().OpenXml(item,path);
            auto item = new QsVerifyResultListItem(fi,this,msgService());
            _resultList->append(epoch,item);
        }
    }
    else{

        if(_watchedFiles.contains(epoch)){
            _watchedFiles.remove(epoch);
            _fileWatcher->removePath(fi.absolutePath());
            _resultList->remove(epoch);
        }
    }

}
