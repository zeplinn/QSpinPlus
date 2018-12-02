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
    QString _name;
public:
     explicit AppendToVeriyQueue(QFileInfo info,QString name,QDateTime createdAt);
    QFileInfo fileInfo();
    QDateTime createdAt();
    QString name()const { return _name;}

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
 QSpinPlus* _project;
public:
 explicit ProjectClosed(QSpinPlus* project)
     :_project(project)
 {}
 QSpinPlus* project()const{ return _project; }
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


////////////////////////////////////////////////////
/// \brief The VerificationResultCreated class
////////////////////////////////////////////////////


class VerificationResultFileChanged{
public:
    enum Status{
        Created,
        Deleted,
        Canceled
    };
private:
    QFileInfo _file;
    Status _status;

public:
    VerificationResultFileChanged(QFileInfo destination,Status status);

    QFileInfo destination();
    Status status();
};

#endif // EVENTOBJECTS_H
