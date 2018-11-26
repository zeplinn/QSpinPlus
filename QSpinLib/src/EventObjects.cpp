#include "qspin/EventObjects.h"

PrintToConsole::PrintToConsole(QString message, PrintToConsole::MessageType type)
    :_msg(message)
    ,_type(type)
{}

QString PrintToConsole::message() const{
    switch (_type) {
    case Normal: return _msg;
    case Warning: return QString("Warning: %1").arg(_msg);
    case Error: return QString("Error: %1").arg(_msg);
    }
}

AppendToVeriyQueue::AppendToVeriyQueue(QFileInfo info, QDateTime createdAt)
    :_file(info)
    ,_createdAt(createdAt)
{

}

QFileInfo AppendToVeriyQueue::fileInfo(){ return _file; }

QDateTime AppendToVeriyQueue::createdAt(){return  _createdAt; }

newProjectCreated::newProjectCreated(QFileInfo fileInfo):
    _fileInFo(fileInfo){}

QFileInfo newProjectCreated::fileInfo() const{ return _fileInFo;}

ProjectOpened::ProjectOpened(QSpinPlus *project):
    _project(project){}

QSpinPlus *ProjectOpened::project() const{ return _project;}

ProjectSaved::ProjectSaved(QSpinPlus *fileInfo):
    _fileInFo(fileInfo){}

QSpinPlus *ProjectSaved::project() const{ return _fileInFo;}

SelectedToolTabUpdated::SelectedToolTabUpdated(int value):_value(value){}

int SelectedToolTabUpdated::value() const{ return _value; }
