#include "qspin/models/QsItemConfiguration.h"


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
    else if(Arg::isCompileArgument(commandId))    _category = Arg::Compile;
    else if(Arg::isPanArgument(commandId))        _category = Arg::Pan;
    else throw QString("argument is not a category: %1").arg(Arg::name(commandId));
}

ItemConfiguration::ItemConfiguration(ItemConfiguration *item)
    :QObjectBase(nullptr)
    ,_command(item->command())
    ,_name(item->name())
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
    xml.writeStartElement("ItemConfiguration");
    xml.writeAttribute("command",QString::number(command()));
    xml.writeAttribute("checked",checked() ? "true" :"false");
    xml.writeAttribute("enabled",enabled() ? "true" :"false");
    xml.writeAttribute("name",name());
    xml.writeEndElement();// itemConfiguration end
}

QString ItemConfiguration::writeCommand() const{
    return Arg::val(command());
}


void ItemConfiguration::setCommand(Arg::Type value){
    SET_QPROP(_command,value,emit commandChanged();)
}

void ItemConfiguration::readXmlAttributes(QXmlStreamAttributes attr){
    if(attr.hasAttribute("checked")){
        QString c = attr.value("checked").toString();
        if(c == "true") _checked = true;
        else if (c=="false") _checked =false;
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
    readXmlAttributes(xml.attributes());
    while(xml.readNextStartElement()){
        if(xml.name()=="value"){
            QString v = xml.readElementText();
            _commandValue= v.toInt();
        }
        else{
            xml.skipCurrentElement();
        }
    }
}

void ItemValueConfiguration::write(QXmlStreamWriter &xml){
    xml.writeStartElement("ItemValueConfiguration");

    xml.writeAttribute("command",QString::number(command()));
    xml.writeAttribute("checked",checked() ? "true" :"false");
    xml.writeAttribute("enabled",enabled() ? "true" :"false");
    xml.writeAttribute("name",name());

    xml.writeTextElement("value",QString::number(commandValue()));

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



//ItemLTLConfiguration::ItemLTLConfiguration(Arg::Type defaultCommand, QObject *parent)
//    :ItemConfiguration(defaultCommand,parent){

//}



ItemLTLConfiguration::ItemLTLConfiguration(Arg::Type commandId, QObject *parent, EventAggregator *msgService)
    :ItemConfiguration(commandId,parent,msgService)
{
     this->msgService()->subscribe<ProjectOpened>(this);
      this->msgService()->subscribe<ProjectSaved>(this);
}

ItemLTLConfiguration::ItemLTLConfiguration(ItemLTLConfiguration *item)
    :ItemConfiguration(item->command(),item->parent(),item->msgService())
    ,_document(item->document())
{
}

void ItemLTLConfiguration::subscriber(const ProjectOpened &event){
    if(event.project()!= nullptr)
        _destinationDir = event.project()->binDir();
}

void ItemLTLConfiguration::subscriber(const ProjectSaved &event){
    if( event.project()!=nullptr)
        _destinationDir = event.project()->binDir();
}

QString ItemLTLConfiguration::writeCommand() const{
    QFile f(_destinationDir.absoluteFilePath("tmp.ltl"));
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        return QString();
    }
    QTextStream writer(&f);
    QString str = document();
    writer << str.remove(QRegularExpression("[\n\r]"));
    f.close();
    return Arg::val(command(),"tmp.ltl");
}
