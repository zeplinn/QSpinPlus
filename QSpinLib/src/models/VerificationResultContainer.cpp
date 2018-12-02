#include "qspin/models/VerificationResultContainer.h"

VerificationResultContainer::VerificationResultContainer(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
    ,_commands(new SpinCommands(this,msgService))
    ,_results(nullptr)
{}

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
            else if(xml.name()=="TrailDocument")
                _trailDocument = xml.readElementText();
            else if(xml.name()==qs().nameof(_commands)){
                _commands->read(xml);
            }
            else if(xml.name() == VerificationResults::staticMetaObject.className()){
                _results = new VerificationResults(this,msgService());
                _results->read(xml);
            }
        }
    }
}

void VerificationResultContainer::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(Qs::nameof(this));
    xml.writeAttribute("name",_name);
    if(_created.isValid())
        xml.writeTextElement("Created",_created.toString());
    if(_started.isValid()){
        xml.writeTextElement("Started",_started.toString());
    }
    if(_finished.isValid())
        xml.writeTextElement("Finished",_finished.toString());
    _commands->write(xml);
    if(_results != nullptr)
        _results->write(xml);
    if(!_document.isEmpty())
    xml.writeTextElement("Document",_document);
    if(!_trailDocument.isEmpty())
        xml.writeTextElement("TrailDocument",_trailDocument);
    xml.writeEndElement();
}

SpinCommands &VerificationResultContainer::commands(){ return *_commands;}

void VerificationResultContainer::setCommands(SpinCommands *value){
    _commands = value;
    _commands->setParent(this);
}

QString VerificationResultContainer::document(){ return _document; }

void VerificationResultContainer::setDocument(QString document){
    _document = document;
}


QDateTime VerificationResultContainer::createdAt() const { return _created;}

void VerificationResultContainer::setCreatedAt(QDateTime time){
    if(!_created.isValid()){
        _created = time;
    }
}

void VerificationResultContainer::addResults(VerificationResults *results){
    _results = results;
    _results->setParent(this);
}

VerificationResults *VerificationResultContainer::VerificationReport() const{ return _results;}

QString VerificationResultContainer::name() const{ return _name;}

void VerificationResultContainer::setName(QString value){
    if(_name.isEmpty()){
        _name = value;
    }
}
