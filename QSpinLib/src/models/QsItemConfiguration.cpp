#include "qspin/models/QsItemConfiguration.h"

void ItemConfiguration::readXmlAttributes(QXmlStreamAttributes attr){
    if(attr.hasAttribute("checked")){
        QString c = attr.value("checked").toString();
        if(c == "true") _checked=true;
        else if (c=="false") _checked=false;
        else {
            // unknown
        }
    }
    if(attr.hasAttribute("enabled")){
        QString c = attr.value("enabled").toString();
        if(c == "true") _enabled = true;
        else if (c=="false") _enabled =false;
        else {
            // unknown
        }
    }

    if(attr.hasAttribute("category")){
        _category = static_cast<Arg::Category>(attr.value("category").toInt());
        }
    if(attr.hasAttribute("command")){
        _command = static_cast<Arg::Type>(attr.value("command").toInt());
    }

}

void ItemConfiguration::writeDefaultXmlAttributes(QXmlStreamWriter& xml){
    xml.writeAttribute("command",QString::number(command()));
    xml.writeAttribute("category",QString::number(category()));
    xml.writeAttribute("checked",checked() ? "true" :"false");
    xml.writeAttribute("enabled",enabled() ? "true" :"false");
    xml.writeAttribute("name",name());
}


Arg::Type ItemConfiguration::command() const{ return _command;}

QString ItemConfiguration::name() const{return Arg::name(_command);}

bool ItemConfiguration::checked() const {return _checked;}

bool ItemConfiguration::enabled() const{return _enabled;}

void ItemConfiguration::setEnabled(bool value){
    _enabled = value;
    emit enabledChanged();
}

QString ItemConfiguration::argument() const {return Arg::val(command());}

void ItemConfiguration::setChecked(bool value){
    if(_checked != value){
        _checked  =value;
        emit checkedChanged();
    }
}

ItemConfiguration::ItemConfiguration(Arg::Type commandId, QObject *parent, EventAggregator *msgService):QObjectBase (parent,msgService)
  ,_command(commandId),_checked(false),_enabled(false)
{
    if(Arg::isSpinArgument(commandId))       _category = Arg::Spin;
    else if(Arg::isCompileArgument(commandId))    _category = Arg::Gcc;
    else if(Arg::isPanArgument(commandId))        _category = Arg::Pan;
}

ItemConfiguration::ItemConfiguration(ItemConfiguration *item)
    :QObjectBase(nullptr)
    ,_command(item->command())
    ,_checked(item->checked())
    ,_enabled(item->enabled())
    ,_category(item->category())

{
    setMsgService(item->msgService());
    setParent(item->parent());
}

Arg::Category ItemConfiguration::category() const{return  _category;}

void ItemConfiguration::read(QXmlStreamReader &xml){
    readXmlAttributes(xml.attributes());
    xml.skipCurrentElement();// no children, so skip for next object
}

void ItemConfiguration::write(QXmlStreamWriter &xml){
    xml.writeStartElement(qs().nameof(this));
    writeDefaultXmlAttributes(xml);
    xml.writeEndElement();// itemConfiguration end
}

QString ItemConfiguration::writeCommand() const{
    return Arg::val(command());
}


void ItemConfiguration::setCommand(Arg::Type value){
    SET_QPROP(_command,value,emit commandChanged();)
}



int ItemValueConfiguration::commandValue() const{return _commandValue;}

void ItemValueConfiguration::setCommandValue(int value){
    if(command()!=value){
        _commandValue = value;
        emit commandValueChanged();
    }
}

int ItemValueConfiguration::maxValue() const{ return _maxValue;}

int ItemValueConfiguration::minValue() const{ return _minValue;}

QString ItemValueConfiguration::argument() const{return Arg::val(command(),commandValue());}

void ItemValueConfiguration::read(QXmlStreamReader &xml){
    if(xml.name() == qs().nameof(this)){
        auto attr = xml.attributes();
        readXmlAttributes(attr);
        if(attr.hasAttribute("value")){
            bool isvalid;
            setCommandValue(attr.value("value").toInt(&isvalid));
            if(!isvalid)
                qCritical("invalid ItemValueConfiguration value"+attr.value("value").toLocal8Bit());
        }
        xml.skipCurrentElement();
    }
}

void ItemValueConfiguration::write(QXmlStreamWriter &xml){
    xml.writeStartElement(qs().nameof(this));

    writeDefaultXmlAttributes(xml);
    xml.writeAttribute("value",QString::number(commandValue()));

    xml.writeEndElement();// end ItemValueConfiguration
}

ItemValueConfiguration::ItemValueConfiguration(Arg::Type command, int value, int minValue, int maxValue, QObject *parent, EventAggregator *msgService):
    ItemConfiguration(command,parent,msgService),_commandValue(value),_minValue(minValue),_maxValue(maxValue){}

ItemValueConfiguration::ItemValueConfiguration(ItemValueConfiguration *item)
    :ItemConfiguration(item)
    ,_commandValue(item->commandValue())
    ,_minValue(item->minValue())
    ,_maxValue(item->maxValue())
{}

QString ItemLTLConfiguration::document() const{ return _document; }

void ItemLTLConfiguration::setDocument(QString value){
    if(_document != value){
        _document = value;

        emit documentChanged();
    }
}

ItemLTLConfiguration::ItemLTLConfiguration(Arg::Type commandId, QObject *parent, EventAggregator *msgService)
    :ItemConfiguration(commandId,parent,msgService)
{
}

ItemLTLConfiguration::ItemLTLConfiguration(ItemLTLConfiguration *item)
    :ItemConfiguration(item->command(),item->parent(),item->msgService())
    ,_document(item->document())
{
}



void ItemLTLConfiguration::subscriber(const ProjectSaved &event){
    if( event.project()!=nullptr)
        if(!document().isEmpty())
            qs().writeTextFile(document(), event.project()->projectDir().absoluteFilePath(name()));
}

void ItemLTLConfiguration::read(QXmlStreamReader &xml){
    if(xml.name()== qs().nameof(this)){
        readXmlAttributes(xml.attributes());
        while (xml.readNextStartElement()) {
            if(xml.name() =="Document"){
                setDocument(xml.readElementText());
            }
        }
    }
}

void ItemLTLConfiguration::write(QXmlStreamWriter &xml){
    xml.writeStartElement(qs().nameof(this));
    writeDefaultXmlAttributes(xml);
    xml.writeTextElement("Document",document());
    xml.writeEndElement();
}

QString ItemLTLConfiguration::writeCommand() const{
    return Arg::val(command(),SpinCommands::tmpLtlFileName())+ SpinCommands::tmpLtlFileName();
}

ItemAdvancedStringConfiguration::ItemAdvancedStringConfiguration(Arg::Type cmd, QObject *parent, EventAggregator *msg)
    :ItemConfiguration(cmd,parent,msg)
{
}

ItemAdvancedStringConfiguration::ItemAdvancedStringConfiguration(ItemAdvancedStringConfiguration *item)
    :ItemConfiguration(item)
    ,_text(item->text())

{
    _category = item->category();
}

QString ItemAdvancedStringConfiguration::text() const{ return _text; }

void ItemAdvancedStringConfiguration::setText(QString value){
    if(_text != value){
        _text = value;
        emit textChanged();
    }
}

void ItemAdvancedStringConfiguration::read(QXmlStreamReader &xml){
    if(xml.name() == qs().nameof(this)){
        readXmlAttributes(xml.attributes());
        while (xml.readNextStartElement()) {
            if(xml.name()=="Text")
                setText(xml.readElementText());
        }
    }
}

void ItemAdvancedStringConfiguration::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(qs().nameof(this));
    writeDefaultXmlAttributes(xml);
    xml.writeTextElement("Text",text());
    xml.writeEndElement();
}

QString ItemAdvancedStringConfiguration::writeCommand() const
{
    return  text();
}
