#include "qspin/models/VerificationResultContainer.h"

void VerificationResultContainer::read(QXmlStreamReader &xml)
{
    if(xml.name()==Qs::nameof(this)){
        auto attr = xml.attributes();
        if(attr.hasAttribute("name"))
            _name = attr.value("name").toString();
        while (xml.readNextStartElement()) {
            if(xml.name()=="Created"){
                _created = QDateTime::fromString(xml.readElementText().toLocal8Bit());
            }
            else if(xml.name()=="Started"){
                _started = QDateTime::fromString(xml.readElementText().toLocal8Bit());
            }
            else if(xml.name()=="Finished"){
                _finished = QDateTime::fromString(xml.readElementText().toLocal8Bit());
            }
            else if(xml.name()=="Document"){
                _document =xml.readElementText().toLocal8Bit();
            }
            else if(xml.name()=="SpinCommands"){
                _commands->read(xml);
            }
        }
    }
}

void VerificationResultContainer::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(Qs::nameof(this));
    xml.writeAttribute("name",_name);
    if(_createdSet)
        xml.writeTextElement("Created",_created.toString());
    if(_started.isValid()){
        xml.writeTextElement("Started",_started.toString());
    }
    if(_finished.isValid())
        xml.writeTextElement("Finished",_finished.toString());
    xml.writeTextElement("Document",_document);
    _commands->write(xml);
    xml.writeEndElement();
}

SpinCommands &VerificationResultContainer::commands(){ return *_commands;}

void VerificationResultContainer::setCommands(SpinCommands *value){
    _commands = value;
    _commands->setParent(this);
}

QFileInfo VerificationResultContainer::saveAs(QString name, QDir destination){
    _name= name;
    if(!_created.isValid()){
        _created = QDateTime::currentDateTime();
    }
    if(!destination.exists() && ! destination.mkpath(destination.currentPath())){
        qCritical("failed create destination folder");
        return QFileInfo();
    }
    QString fileName =QString("%1_%2.qspr")
            .arg(name)
            .arg(_created.toMSecsSinceEpoch());
    QFileInfo _fileInfo = destination.absoluteFilePath(fileName);

    QFile f(_fileInfo.absoluteFilePath());

    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        qCritical("failed to open export path");
        return QFileInfo();

    }
    QXmlStreamWriter writer(&f);
    write(writer);
    f.close();
    return _fileInfo;
}

bool VerificationResultContainer::open(const QFileInfo &filepath){
    if(!filepath.exists())
        return false;
    QFile f(filepath.absoluteFilePath());
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }
    QXmlStreamReader reader(&f);
    read(reader);


    f.close();
    return true;
}

QDateTime VerificationResultContainer::created() const { return _created;}
