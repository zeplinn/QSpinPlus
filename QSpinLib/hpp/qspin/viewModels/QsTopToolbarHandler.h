#ifndef QSTOPTOOLBARHANDLER_H
#define QSTOPTOOLBARHANDLER_H
#include <QObject>
#include<QUrl>
#include <QDir>
#include <QCoreApplication>
#include "qspin/Qs.h"
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/eventObjects/SelectedToolTabUpdated.h"
#include "qspin/eventObjects/NewProjectCreated.h"
#include "qspin/eventObjects/ProjectOpened.h"
#include "qspin/eventObjects/ProjectSaved.h"
#include "qspin/eventObjects/NewProjectCreated.h"
#include "qspin/eventObjects/PrintToConsole.h"
class QstopToolbarHandler: public QObject{

		Q_OBJECT
		// ##################### begin properties ###################################
		Q_PROPERTY(int currentToolTabIndex READ currentToolTabIndex WRITE setCurrentToolTabIndex NOTIFY currentToolTabIndexChanged)
		int _currentToolTabIndex;
	public:
		int currentToolTabIndex()const{ return _currentToolTabIndex;}
		void setCurrentToolTabIndex(int value){
			_currentToolTabIndex = value;
			msgService().publish(SelectedToolTabUpdated(currentToolTabIndex()));
			emit currentToolTabIndexChanged();
		}
	signals:
		void currentToolTabIndexChanged();
		// ##################### end properties ###################################
	private:
		EventAggregator* _msgService;
		void toConsole(QString msg){
			msgService().publish(PrintToConsole(msg));
		}

	public:
		EventAggregator& msgService(){ return *_msgService;}
		explicit QstopToolbarHandler(QObject* parent = nullptr, EventAggregator* msgService = &Qs::instance().msgService());
	public slots:
		void openProject(QUrl filePath){
			QString folder =filePath.adjusted(QUrl::RemoveFilename).path();
			if(!QDir::setCurrent(folder)){
				QDir d(folder);
				if(QDir::setCurrent(folder)){
					msgService().publish(ProjectOpened(filePath.path()));
				}
				else{
					msgService().publish(PrintToConsole("Error: open project aborted. unable change current firectory to file"));
				}
			}
			emit unlockUiReady();
		}
		void saveProject(QUrl filePath){
			QString fs = filePath.adjusted(QUrl::RemoveFilename).path();
			QDir d( fs);
			if(!d.exists(fs) && !d.mkpath(fs)){
				toConsole("Error: failed to create chosen directory: "+fs);
			}else{
				msgService().publish(ProjectSaved(filePath.path()));
				QDir::setCurrent(fs);
			}
			emit unlockUiReady();
		}
		void newProject(QString name,QUrl folder){
			QString sFolder = folder.path();
			QDir d(folder.path());
			if(d.exists()){
				if(d.mkdir(name)){
					d.cd(name);
					if(QDir::setCurrent(d.path())){
						QString path = d.filePath(name+".pml");
						msgService().publish(newProjectCreated(path));
					}
					else{
						msgService().publish(PrintToConsole("Error: failed to create new project folder "));
					}
				}
			}
			emit unlockUiReady();
		}
	signals:
		void unlockUiReady();
};

#endif // QSTOPTOOLBARHANDLER_H
