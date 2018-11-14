#ifndef PROJECTSAVED_H
#define PROJECTSAVED_H
#include <QFileInfo>
class ProjectSaved{
		QFileInfo _fileInFo;

			public:
		explicit ProjectSaved(QFileInfo fileInfo):
			_fileInFo(fileInfo){}
		QFileInfo fileInfo()const{ return _fileInFo;}
};

#endif // PROJECTSAVED_H
