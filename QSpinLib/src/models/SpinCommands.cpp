#include "qspin/models/SpinCommands.h"


SpinCommands::SpinCommands(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
    ,_commands(QList<ItemConfiguration*>())
{}

void SpinCommands::read(QXmlStreamReader &xml)
{
    if(xml.name()== qs().nameof(this)){
        while (xml.readNextStartElement()) {
            auto attr = xml.attributes();
            Arg::Type cmd =Arg::None;
            if(attr.hasAttribute("command"))
                cmd = static_cast<Arg::Type>(attr.value("command").toInt());
            if(xml.name()==ItemConfiguration::staticMetaObject.className()){
                auto ic = new ItemConfiguration(cmd,this,msgService());
                _commands << ic;
                ic->read(xml);
            }
            else if(xml.name()==ItemValueConfiguration::staticMetaObject.className()){
                auto ivc = new ItemValueConfiguration(cmd,0,0,0,this,msgService());
                _commands << ivc;
                ivc->read(xml);
            }
            else if(xml.name()==ItemLTLConfiguration::staticMetaObject.className()){
                auto ilc = new ItemLTLConfiguration(cmd,this,msgService());
                _commands << ilc;
                ilc->read(xml);
            }
        }
    }
}

void SpinCommands::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(qs().nameof(this));
    for ( auto ic : _commands)
        ic->write(xml);
    xml.writeEndElement();
}

compiledCommands SpinCommands::CommandsToStringLists(){
    compiledCommands cmds;
    // default commands
    cmds.spin << "-a" << "-o7";
    cmds.gcc << "pan.c" << "-o" <<"pan";
    for(auto ic : _commands){
        switch (ic->category()) {
        case Arg::Spin:
            cmds.spin << ic->writeCommand();
            if(ic->command() ==Arg::LTL){
                cmds.ltl = qobject_cast<ItemLTLConfiguration*>(ic);
            }
            break;
        case Arg::Gcc:
            cmds.gcc << ic->writeCommand();
            break;
        case Arg::Pan:
            cmds.pan << ic->writeCommand();
            break;
        }
    }
    cmds.spin << tmpSpinFileName();
    return cmds;
}

void SpinCommands::append(ItemConfiguration *item){
    auto name =qs().nameof(item);
    if(name == ItemConfiguration::staticMetaObject.className())
        _commands << new ItemConfiguration(item);
    else if( name == ItemValueConfiguration::staticMetaObject.className()){
        auto ic = qobject_cast<ItemValueConfiguration*>(item);
        _commands << ic;
    }
    else if (name == ItemLTLConfiguration::staticMetaObject.className()) {
        auto ic = qobject_cast<ItemLTLConfiguration*>(item);
        _commands <<ic;
    }
}

