#include "qspin/models/QSpinPlus.h"


QSpinPlus *QSpinPlus::openProject(QString promelaPath){

    QFile f(promelaPath);
    auto project = new QSpinPlus();
    f.open(QFile::ReadOnly |QFile::Text);
    QXmlStreamReader reader(&f);
    project->read(reader);
    project->setPmlInfo(promelaPath);
    f.close();
    return  project;
}

QSpinPlus* QSpinPlus::createBasicProject(QString name, QDir dir){
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
    return openProject(dir.absoluteFilePath(filename));
}

void QSpinPlus::save(QFileInfo info){
    if(info.absoluteFilePath() != pmlInfo().absoluteFilePath()){
        auto from = projectDir();
        auto old_project_name = projectInfo().fileName();
        setPmlInfo(info);
        QsCopy::copyFolder(from,projectDir());
        QFile::remove(projectDir().absoluteFilePath(old_project_name));
    }
    QFile f(projectInfo().absoluteFilePath());
    f.open(QIODevice::WriteOnly);

    QXmlStreamWriter writer(&f);
    write(writer);
    f.close();
}

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
    if(xml.readNextStartElement() && xml.name() == "QSpinPlus"){
        while (xml.readNextStartElement()) {
            if(xml.name() == "Configurations"){
                _configurations->read(xml);
            }
        }
    }else{
        // invalid project file
    }
}

void QSpinPlus::write(QXmlStreamWriter &xml){
    xml.setAutoFormatting(true);
    xml.writeStartElement("QSpinPlus");
    _configurations->write(xml);
    xml.writeEndElement();// QSpinPlus
}
