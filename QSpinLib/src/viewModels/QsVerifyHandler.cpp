#include "qspin/viewModels/QsVerifyHandler.h"



VerificationConfiguration *QsVerifyHandler::currentConfiguration() const{
    return _currentItem.isNull() ? nullptr : _currentItem.data();
}

int QsVerifyHandler::currentIndex() const{return _currentIndex;}

void QsVerifyHandler::setCurrentIndex(int value){
    //if( _currentIndex != value){

    _currentIndex = value;
    if(_currentIndex < 0 || _currentIndex>= _project->configurations()->count() )
        _currentIndex=-1;
    if(currentIndex()<0)
        _currentItem = nullptr;
    else _currentItem = _project->configurations()->get(value);
    emit currentIndexChanged();
    emit currentConfigurationChanged(_currentItem);
    //}
}

bool QsVerifyHandler::isProjectOpen() const{ return _isProjectOpen;}

QsVerifyHandler::QsVerifyHandler(QObject *parent, EventAggregator *msgService)
    :QObjectListBase(parent,msgService)
    ,_currentIndex(-1)
    ,_currentItem(nullptr)
    ,_project(nullptr)
{
    this->msgService()->subscribe<ProjectClosed>(this);
    this->msgService()->subscribe<ProjectOpened>(this);
    this->msgService()->subscribe<ProjectSaved>(this);
}

QVariant QsVerifyHandler::data(const QModelIndex &index, int role) const{
    int idx = index.row();
    if( _project == nullptr)
        return QVariant();
    auto configs = _project->configurations();
    if(idx<0 || idx >= configs->count()) return  QVariant();

    auto config = configs->get(idx);
    switch (role) {
    case SaftyRoleMode: return QVariant::fromValue(config->safetyMode());
    case ProgressMode: return QVariant::fromValue(config->progressMode());
    case AcceptanceMode: return QVariant::fromValue(config->acceptanceMode());
    case VerifyMode:
        return config->currentMode();
    case Name: return config->name();
    }
    return QVariant();
}

int QsVerifyHandler::rowCount(const QModelIndex &index) const{
    Q_UNUSED(index)
    if( _project!=nullptr)
        return _project->configurations()->count();
    return 0;
}

QHash<int, QByteArray> QsVerifyHandler::roleNames() const{
    QHash<int,QByteArray> r;
    r[SaftyRoleMode]="saftyMode_role";
    r[ProgressMode]="progresMode_role";
    r[AcceptanceMode]="acceptanceMode_role";
    r[VerifyMode] ="verifyMode_role";
    r[Name]="name_role";
    return r;
}

void QsVerifyHandler::setIsProjectOpen(bool value){
    _isProjectOpen = value;
    emit isProjectOpenChanged();
}

void QsVerifyHandler::subscriber(const ProjectOpened &event){
    if(event.project()==nullptr){
        qFatal(" verify handler project opened cannot be a nullpointer");
    }
    setCurrentIndex(-1);
    beginResetModel();
    _project = event.project();
    endResetModel();
    setIsProjectOpen(true);
}

void QsVerifyHandler::subscriber(const ProjectSaved &event){
    if(event.project()!=_project){
        setCurrentIndex(-1);
        beginResetModel();
        _project= event.project();
        endResetModel();
    }
    if(_project!=nullptr){
        auto c =_project->configurations();
        for(int i =0; i <c->count();i++){
            auto vc = c->get(i);
            auto ltl = vc->ltl();
            qs().writeTextFile(ltl->document(),_project->projectDir().absoluteFilePath(vc->name()+".ltl"));
        }
    }
}

void QsVerifyHandler::subscriber(const ProjectClosed &event){
    Q_UNUSED(event)

    setIsProjectOpen(false);
    setCurrentIndex(-1);
    beginResetModel();
    _project=nullptr;
    endResetModel();
}

void QsVerifyHandler::addConfiguration(QString name){
    if(_project==nullptr) return;
    auto c = _project->configurations();
    auto vc = new VerificationConfiguration(this,c->msgService() );
    vc->updateConfigurations();
    vc->setName(name);
    QObject::connect(vc,&VerificationConfiguration::verifyModeChanged,this,&QsVerifyHandler::verifyModeUpdated);
    beginInsertRows(QModelIndex(),c->count(),c->count());
    c->append( vc);
    endInsertRows();
    setCurrentIndex(c->count()-1);
}

void QsVerifyHandler::removeConfiguration(VerificationConfiguration *item){
    if(_project==nullptr) return;
    auto c = _project->configurations();
    if(c->count()==0) return;
    int idx = currentIndex()-1 <0 ? 0 : currentIndex()-1;
    beginRemoveRows(QModelIndex(),currentIndex(),currentIndex());
    c->removeAt(currentIndex());
    setCurrentIndex(idx);
    endRemoveRows();
    item->deleteLater();
}

void QsVerifyHandler::queueVerification(VerificationConfiguration *item){
    if(_project.isNull() || item == nullptr) return;

    auto resultContatiner = new VerificationResultContainer(this,msgService());
    resultContatiner->setCommands(item->getSpinCommands());
    QString document =  _project->currentDocument();//  qs().readTextFile(_project->pmlInfo().absoluteFilePath());
    resultContatiner->setDocument(document);

    auto date =QDateTime::currentDateTime();
    auto fileInfo = qs().constructResultFileName(_project->queuedDir(),item->name(),date);
    resultContatiner->setFile(fileInfo);
    resultContatiner->setName(item->name());
    resultContatiner->setCreatedAt(date);
    qs().WriteXml(resultContatiner,fileInfo.absoluteFilePath());
    msgService()->publish(AppendToVeriyQueue(fileInfo,item->name(),resultContatiner->createdAt()));
    resultContatiner->deleteLater();

}



void QsVerifyHandler::verifyModeUpdated(Arg::Type mode){
    Q_UNUSED(mode)
    dataChanged(index(currentIndex()),index(currentIndex()),{VerifyMode});
}

void QsVerifyHandler::checkSyntax(){
    QProcess p;
    QDir workDir = _project->projectDir();
    QString tmpDir ="sc_check_"+currentConfiguration()->name();
    workDir.mkdir(tmpDir);
    workDir.cd(tmpDir);
    p.setWorkingDirectory(workDir.absolutePath());
    auto vResult = new VerificationResultContainer();
    auto spinCommands = new SpinCommands();
    auto vc = currentConfiguration();

    //        for ( auto ic : _project->configurations())
    //            set
    //        spinCommands->append()

}
