#ifndef EVENTOBJECTS_H
#define EVENTOBJECTS_H
#include <QObject>
#include <QDateTime>
#include <QFileInfo>

class QSpinPlus;


////////////////////////////////////////////////
/// \brief The PrintToConsole class
////////////////////////////////////////////////


class PrintToConsole{
public:
    enum MessageType{
        Normal,
        Warning,
        Error
    };
private:
    QString _msg;
    MessageType _type;
public:
    explicit PrintToConsole(QString message,MessageType type = Normal);
    QString message()const;
};


////////////////////////////////////////////////
/// \brief The AppendToVeriyQueue class
///////////////////////////////////////////////


class AppendToVeriyQueue
{
    QFileInfo _file;
    QDateTime _createdAt;
public:
     explicit AppendToVeriyQueue(QFileInfo info,QDateTime createdAt);
    QFileInfo fileInfo();
    QDateTime createdAt();


};

//////////////////////////////////////////////
/// \brief The newProjectCreated class
/////////////////////////////////////////////


class newProjectCreated{
        QFileInfo _fileInFo;

            public:
        explicit newProjectCreated(QFileInfo fileInfo);
        QFileInfo fileInfo()const;

};


//////////////////////////////////////////////
/// \brief The ProjectClosed class
//////////////////////////////////////////////



class ProjectClosed{

};



//////////////////////////////////////////////
/// \brief The ProjectOpened class
/////////////////////////////////////////////



class ProjectOpened{
        QSpinPlus* _project;

            public:
        explicit ProjectOpened(QSpinPlus* project);
        QSpinPlus* project()const;
};


//////////////////////////////////////////////
/// \brief The ProjectSaved class
//////////////////////////////////////////////

class ProjectSaved{
        QSpinPlus* _fileInFo;

            public:
        explicit ProjectSaved(QSpinPlus* fileInfo);
        QSpinPlus* project()const;
};


/////////////////////////////////////////////
/// \brief The SelectedToolTabUpdated class
/////////////////////////////////////////////


class SelectedToolTabUpdated{
        int _value;
public:
        explicit SelectedToolTabUpdated(int value);
          int value()const;
};


// project includes goes here to avoid import conflicts conflicts

//#include "qspin/models/QSpinPlus.h"


#endif // EVENTOBJECTS_H
