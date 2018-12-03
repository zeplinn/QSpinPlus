#include "qspin/viewModels/QsPromelaHandler.h"

void QsPromelaHandler::saveDocument(QUrl fileUrl){
    if(_project == nullptr){
        qFatal("current project is a null pointer");
    }
    QFileInfo info(fileUrl.toLocalFile());
    QString name = info.baseName();
    if( !qs().isValidFileName(name)){
        emit inValidPromelaFile(info.absoluteFilePath());
        return;
    }
    editor()->saveAs(fileUrl);
    _project->save(info);

    msgService()->publish(ProjectSaved(_project));
    QDir::setCurrent(_project->pmlDir().absolutePath());
    emit projectSaved(fileUrl);
}

void QsPromelaHandler::openDocument(QUrl fileUrl){
    QFileInfo info(fileUrl.toLocalFile());
    if(!qs().isValidFileName(info.baseName())){
        emit inValidPromelaFile(info.absoluteFilePath());
        return;
    }
    if(_project != nullptr){
        closeDocument(_project->pmlInfo().absoluteFilePath());
    }

    if(!info.exists()){
        toConsole("Error: file do not exist"+info.absoluteFilePath());
        return;
    }
    QDir dir = info.absoluteDir();

    if(!dir.exists(info.baseName())){
        QSpinPlus::createBasicProject(info.baseName(),dir);
    }

    auto project = new QSpinPlus(this, msgService());
    project->openProject(info);
    project->attachCurrentDocument( editor() );
    if(project == nullptr)
        toConsole("failed to open project file");
    editor()->open(fileUrl);
    msgService()->publish(ProjectOpened(project));
    QDir::setCurrent(info.absoluteDir().path());
    _project= project;
    setIsEditable(true);
    setIsOpen(true);

}

void QsPromelaHandler::createDocument(QString filepath){
    QFileInfo finfo(filepath);
    if(!qs().isValidFileName(finfo.baseName())){
        emit inValidPromelaFile(finfo.absoluteFilePath());
        return;
    }
    //create promelaFile
    QString document = QString("// %1 created at: %2").arg(finfo.fileName()).arg(QDateTime::currentDateTime().toString());

    qs().writeTextFile(document,finfo.absoluteFilePath());
    // open promela file
    openDocument(finfo.absoluteFilePath());
}

void QsPromelaHandler::closeDocument(QUrl fileUrl){
    Q_UNUSED(fileUrl)
    if(_project != nullptr){
        QFileInfo info(fileUrl.toLocalFile());
        if(info.exists()){
            saveDocument(fileUrl);
            qs().msgService()->publish(ProjectClosed(_project));
            _project->deleteLater();
            _project = nullptr;

        }
        setIsEditable(false);
        setIsOpen(false);
    }
}

void QsPromelaHandler::saveExistingDocument(){
    saveDocument(_project->pmlInfo().absoluteFilePath());
}

void QsPromelaHandler::closeExistingDocumet(){
    if(_project!=nullptr)
        closeDocument(_project->pmlInfo().absoluteFilePath());
}

QsCodeEditorHandler*QsPromelaHandler::editor() const { return  _editor;}

void QsPromelaHandler::setEditor(QsCodeEditorHandler*value){
    _editor = value;
    emit editorChanged();
}

bool QsPromelaHandler::isEditable() const{ return _isEditable; }

void QsPromelaHandler::setIsEditable(bool value){
    if(_isEditable != value){
        _isEditable = value;
        emit isEditableChanged();
    }
}

bool QsPromelaHandler::isOpen() const{ return _isOpen; }

void QsPromelaHandler::setIsOpen(bool value){
    if(_isOpen != value){
        _isOpen = value;
        emit isOpenChanged();
    }
}




