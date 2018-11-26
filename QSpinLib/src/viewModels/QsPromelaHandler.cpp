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
    if(_project != nullptr)
        closeDocument(_project->pmlInfo().absoluteFilePath());

    QFileInfo info(fileUrl.toLocalFile());
    if(!info.exists()){
        toConsole("Error: file do not exist"+info.absoluteFilePath());
        return;
    }
    QDir dir = info.absoluteDir();

    if(!dir.exists(info.baseName())){
        QSpinPlus::createBasicProject(info.baseName(),dir);
    }

    auto project = QSpinPlus::openProject(info.absoluteFilePath());
    editor()->open(fileUrl);
    msgService()->publish(ProjectOpened(project));
    if(_project != nullptr)
        _project->deleteLater();
    _project = project;
    QDir::setCurrent(info.absoluteDir().path());
    setIsEditable(true);
    setIsOpen(true);

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




