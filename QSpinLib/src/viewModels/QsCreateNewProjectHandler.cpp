#include "qspin/viewModels/QsCreateNewProjectHandler.h"

void QsCreateNewProjectHandler::updateCanAccept(){ emit canAcceptChanged(); }

QString QsCreateNewProjectHandler::name() const{ return _name; }

void QsCreateNewProjectHandler::setName(QString value){
    if(_name != value){
        _name = value;
        emit nameChanged();
        emit isValidNameChanged();
        updateCanAccept();
    }
}

QString QsCreateNewProjectHandler::promelaPath() const{ return _promelaPath; }

QString QsCreateNewProjectHandler::destination() const{ return _destination; }

bool QsCreateNewProjectHandler::useExistingPml() const{ return _useExistingPml; }

void QsCreateNewProjectHandler::setUseExistingPml(bool value){
    if(_useExistingPml != value){
        _useExistingPml = value;
        emit useExistingPmlChanged();
        updateCanAccept();
    }
}

bool QsCreateNewProjectHandler::canAccept() const{
    return isValidFolder()
            && !name().isEmpty()
            && (useExistingPml() ? isValidPromelaFile() : true);
}

bool QsCreateNewProjectHandler::isValidPromelaFile() const{
    return QFileInfo::exists(_promelaPath) && !promelaPath().isEmpty();
}

bool QsCreateNewProjectHandler::isValidFolder() const{
    return QDir(_destination).exists() && ! destination().isEmpty();
                                                     }

void QsCreateNewProjectHandler::setPromelaPath(QUrl value){
    if(_promelaPath != value.toLocalFile()){
        _promelaPath = value.toLocalFile();
        emit promelaPathChanged();
        emit isValidPromelaFileChanged();
        updateCanAccept();
    }
}

void QsCreateNewProjectHandler::setDestination(QUrl value){
    if(_destination != value.toLocalFile()){
        _destination = value.toLocalFile();
        emit destinationChanged();
        emit isValidFolderChanged();
        updateCanAccept();
    }
}

QsCreateNewProjectHandler::QsCreateNewProjectHandler(QObject *parent):QObject(parent) {}

QsCreateNewProjectHandler::~QsCreateNewProjectHandler() {}
