#include "qspin/viewModels/QsCreateProjectHandler.h"

QString QsCreateProjectHandler::filename() const{ return _name.isEmpty() ? "" : _name+".pml"; }

QString QsCreateProjectHandler::name() const{ return _name; }

void QsCreateProjectHandler::setName(QString value){
    _name = value;
    emit nameChanged();
    setIsValidName(value);
    updateAbsolutePath();
}

QUrl QsCreateProjectHandler::folder() const { return _folder; }

void QsCreateProjectHandler::setFolder(QUrl value){
    _folder = value;
    emit folderChanged();
    setIsValidFolder(value);
    updateAbsolutePath();
}

QString QsCreateProjectHandler::absolutePath() const{ return _absolutePath; }

void QsCreateProjectHandler::updateAbsolutePath( ){
        _absolutePath = folder().toLocalFile()+"/"+filename();
        emit absolutePathChanged();
}

bool QsCreateProjectHandler::isValidName() const{ return _isValidName;}

void QsCreateProjectHandler::setIsValidName(QString name){
    _isValidName =qs().isValidFileName(name);
    emit isValidNameChanged();
}

bool QsCreateProjectHandler::isValidFolder(){
    return  _isValidFolder;
}

void QsCreateProjectHandler::setIsValidFolder(QUrl folder){
    QDir d(folder.toLocalFile());
    _isValidFolder = d.exists();
    emit isValidFolderChanged();

}



//QsCreateProjectHandler::QsCreateProjectHandler(QObject*parent, EventAggregator&msgService)
//	:QObject (parent),msgService(msgService),_name(""),_folder(QUrl(QDir::currentPath()))
//{

//}
