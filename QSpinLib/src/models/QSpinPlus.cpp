#include "qspin/models/QSpinPlus.h"


void QSpinPlus::openProject(QFileInfo promelaPath){
    QString projectPath = QString("%1/%2/%2.qsp")
            .arg(promelaPath.absoluteDir().absolutePath())
            .arg(promelaPath.baseName());
    QFile f(projectPath);
    qs().OpenXml(this,projectPath);
    QXmlStreamReader reader(&f);
    setPmlInfo(promelaPath);
}

void QSpinPlus::createBasicProject(QString name, QDir dir){
    //toConsole("Project folder created:" +dir.path()+"/"+name);
    dir.mkdir(name);
    dir.cd(name);
    dir.mkdir("results");
    dir.mkdir("bin");
    dir.mkdir("queued");

    // create project file
    QString filename = name + ".qsp";
    QFile initital(":/misc/default.qsp");
    initital.open(QIODevice::ReadOnly |QIODevice::Text);
    QFile newProject(dir.absoluteFilePath(filename));
    newProject.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream read(&initital), write(&newProject);
    write << read.readAll();
    initital.close();
    newProject.close();
}

void QSpinPlus::save(QFileInfo info){
    if(info.absoluteFilePath() != pmlInfo().absoluteFilePath()){
        auto from = projectDir();
        auto old_project_name = projectInfo().fileName();
        setPmlInfo(info);
        Qs::copyFolder(from,projectDir());
        QFile::remove(projectDir().absoluteFilePath(old_project_name));
    }
    QFile f(projectInfo().absoluteFilePath());
    f.open(QIODevice::WriteOnly);

    QXmlStreamWriter writer(&f);
    write(writer);
    f.close();
}

QSpinPlus::QSpinPlus(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
    ,_configurations(new Configurations(this,msgService))
{}

Configurations *QSpinPlus::configurations() const{ return _configurations;}

QFileInfo &QSpinPlus::projectInfo(){ return  _ProjectInfo;}

QFileInfo &QSpinPlus::pmlInfo(){ return _pmlInfo;}

//void QSpinPlus::setProjectInfo(QFileInfo info){
//    _ProjectInfo = info;
//}

void QSpinPlus::setPmlInfo(QFileInfo info){
    _pmlInfo = info;
    QString p_filePath = QString("%1/%2/%2.qsp")
            .arg(info.absoluteDir().path())
            .arg(info.baseName());
    _ProjectInfo =QFileInfo(p_filePath);
    _resultFolder = projectDir().absolutePath()+"/results";
    _binFolder = projectDir().absolutePath()+"/bin";
    _queuedFolder = projectDir().absolutePath()+"/queued";

}

void QSpinPlus::read(QXmlStreamReader &xml){

    QString x =xml.name().toString();
    if(qs().nameof(this) ==x ){
        while (xml.readNextStartElement()) {
            x = xml.name().toString();
            QString y = qs().nameof(_configurations);
            if(x== qs().nameof(_configurations)){
                _configurations->read(xml);
            }
        }
    }else{
        // invalid project file
        qCritical("invaild qspin project file");
        toConsole("Reading Project file: Invalid project format");
    }
}

void QSpinPlus::write(QXmlStreamWriter &xml){
    xml.setAutoFormatting(true);
    xml.writeStartElement("QSpinPlus");
    _configurations->write(xml);
    xml.writeEndElement();// QSpinPlus
}

QString QSpinPlus::currentDocument() const{ return _currentDocument->text(); }

void QSpinPlus::attachCurrentDocument(QsCodeEditorHandler *current){
    _currentDocument = current;
}

void QSpinPlus::SendToQueue(){

}
