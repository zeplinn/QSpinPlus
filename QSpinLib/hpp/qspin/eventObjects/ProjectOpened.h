#ifndef PROJECTOPENED_H
#define PROJECTOPENED_H
#include <QFileInfo>
class ProjectOpened{
		QFileInfo _fileInFo;

			public:
		explicit ProjectOpened(QFileInfo fileInfo):
			_fileInFo(fileInfo){}
		QFileInfo fileInfo()const{ return _fileInFo;}
};

#endif // PROJECTOPENED_H
