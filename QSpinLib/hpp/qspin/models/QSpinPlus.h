#ifndef QSPINPLUS_H
#define QSPINPLUS_H
#include <QObject>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "qspin/QObjectBase.h"
#include "qspin/models/IQsSerialization.h"
class QsCodeEditorHandler;
#include "qspin/viewModels/QsCodeEditorHandler.h"
class Configurations;
#include "qspin/models/Configurations.h"


class QSpinPlus : public QObjectBase, public IQXmlSerialization
{
    Q_OBJECT

    Configurations* _configurations;
    QFileInfo _pmlInfo;
    QFileInfo _ProjectInfo;
    QDir _resultFolder, _binFolder, _queuedFolder;
    QsCodeEditorHandler* _currentDocument;

protected:

public:
    void openProject(QFileInfo promelaPath);
    static void createBasicProject(QString name,QDir dir);
    void save(QFileInfo path);
    explicit QSpinPlus(QObject* parent = nullptr, EventAggregator* msgService= nullptr);
        Configurations* configurations()const;

    QFileInfo& projectInfo();
    QFileInfo& pmlInfo();
    //oid setProjectInfo(QFileInfo info);
    void setPmlInfo(QFileInfo info);
    QDir pmlDir()const{return _pmlInfo.absoluteDir();}
    QDir projectDir()const{ return _ProjectInfo.absoluteDir();}
    QDir resultsDir()const{ return _resultFolder;}
    QDir binDir()const {return _binFolder;}
    QDir queuedDir()const {return _queuedFolder;}
    virtual void read(QXmlStreamReader& xml)override;
    virtual void write(QXmlStreamWriter& xml)override;
    ProjectInfo FullProjectInformation(){
        return  ProjectInfo(pmlInfo(),projectInfo(),resultsDir(),binDir(),queuedDir());
    }
    QString currentDocument()const;
    void attachCurrentDocument(QsCodeEditorHandler* current);
    void SendToQueue();

};


#endif // QSPINPLUS_H
