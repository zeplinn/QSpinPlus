#include "qspin/viewModels/QsCreateProjectHandler.h"

QString QsCreateProjectHandler::name() const{ return _name; }

void QsCreateProjectHandler::setName(QString value){_name = value; emit nameChanged(); emit absolutePathChanged();}

QUrl QsCreateProjectHandler::folder() const { return _folder; }

void QsCreateProjectHandler::setFolder(QUrl value){	_folder = value; emit folderChanged(); emit absolutePathChanged(); }

QString QsCreateProjectHandler::absolutePath() const{
	QDir d(folder().toLocalFile());
	return d.filePath(name()+".xml");
}

QsCreateProjectHandler::QsCreateProjectHandler(QObject*parent, EventAggregator&msgService)
	:QObject (parent),msgService(msgService),_name(""),_folder(QUrl(QDir::currentPath()))
{

}
