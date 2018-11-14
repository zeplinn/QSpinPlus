#include "qspin/viewModels/QsPromelaHandler.h"

QsPromelaHandler::QsPromelaHandler(QObject*parent, EventAggregator*msgService)
	:QObject(parent),_msgService(msgService){}

void QsPromelaHandler::saveDocument(QUrl fileUrl){
	QString path = fileUrl.adjusted(QUrl::RemoveFilename).path();
	QDir dir(path);
	if(! dir.exists() && !dir.mkpath(path)){
		msgService().publish(PrintToConsole(" failed to create save directory"));
		return;
	}
	editor()->saveAs(fileUrl);
	msgService().publish(ProjectSaved(fileUrl.path()));
	msgService().publish(PrintToConsole("project saved:"+ fileUrl.path()));
	emit projectSaved(fileUrl);
}

QsCodeEditorHandler*QsPromelaHandler::editor() const { return  _editor;}

void QsPromelaHandler::setEditor(QsCodeEditorHandler*value){
	_editor = value;
	emit editorChanged();
}

EventAggregator&QsPromelaHandler::msgService(){return * _msgService;}
