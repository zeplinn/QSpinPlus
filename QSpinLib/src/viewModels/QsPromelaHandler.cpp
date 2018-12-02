#include "qspin/viewModels/QsPromelaHandler.h"

void QsPromelaHandler::saveDocument(QUrl fileUrl){
    if(_project == nullptr) return;
    QFileInfo info(fileUrl.toLocalFile());
    editor()->saveAs(fileUrl);
    _project->save(info);

    msgService()->publish(ProjectSaved(_project));
    QDir::setCurrent(_project->pmlDir().absolutePath());
    emit projectSaved(fileUrl);
}

void QsPromelaHandler::openDocument(QUrl fileUrl){
    if(_project != nullptr){
        closeDocument(_project->pmlInfo().absoluteFilePath());
    }

    QFileInfo info(fileUrl.toLocalFile());
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
    if(_project != nullptr)
        _project->deleteLater();
    _project = project;
    QDir::setCurrent(info.absoluteDir().path());
    setIsEditable(true);
    setIsOpen(true);

}

void QsPromelaHandler::createDocument(QString name, QUrl folder){
    QDir dir(folder.toLocalFile());

    //create promelaFile
    QString document = QString("// %1 created at: %2").arg(name).arg(QDateTime::currentDateTime().toString());
    QFile pml(dir.absoluteFilePath(name+".pml"));

    pml.open(QIODevice::WriteOnly);
    QTextStream write(&pml);
    write << document;
    pml.close();
    // create intitial project structure
    // open promela file
    QFileInfo pmlInfo (dir.absoluteFilePath(name+".pml"));
    QSpinPlus::createBasicProject(name,pmlInfo.absoluteDir());
    openDocument(pmlInfo.absoluteFilePath());
}

void QsPromelaHandler::closeDocument(QUrl fileUrl){
    Q_UNUSED(fileUrl)
    if(_project != nullptr){
        if(fileUrl.isValid()){
            saveDocument(fileUrl);

        }
        else
            saveDocument(_project->pmlInfo().absoluteFilePath());
        qs().msgService()->publish(ProjectClosed(_project));
        _project->deleteLater();
        _project = nullptr;
    }
    setIsEditable(false);

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




