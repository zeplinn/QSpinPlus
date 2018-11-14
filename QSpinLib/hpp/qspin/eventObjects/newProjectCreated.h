#ifndef NEWPROJECTCREATED_H
#define NEWPROJECTCREATED_H
#include <QFileInfo>
class newProjectCreated{
		QFileInfo _fileInFo;

			public:
		explicit newProjectCreated(QFileInfo fileInfo):
			_fileInFo(fileInfo){}
		QFileInfo fileInfo()const{ return _fileInFo;}

};

#endif // NEWPROJECTCREATED_H
