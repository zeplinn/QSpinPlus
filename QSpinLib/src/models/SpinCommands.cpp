#include "qspin/models/SpinCommands.h"


SpinCommands::SpinCommands(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
    ,_ltl(nullptr)
    ,_commands(QList<ItemConfiguration*>())
{}

void SpinCommands::read(QXmlStreamReader &xml)
{
    // cmds inputs are fixed when file is read
    if(xml.name()== qs().nameof(this)){
        while (xml.readNextStartElement()) {
            Arg::Type cmd =Arg::None;
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
                _ltl = ilc;
            }
            else if (xml.name() == ItemAdvancedStringConfiguration::staticMetaObject.className()) {
                auto isc = new ItemAdvancedStringConfiguration(cmd,this,msgService());
                isc->read(xml);
                _commands << isc;
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
    cmds.spin << Arg::val(Arg::Verify) << Arg::val(Arg::O7);
    cmds.gcc << "pan.c" << "-o" <<"pan";
    for(auto ic : _commands){
        auto cmd = ic->writeCommand();
        if(!cmd.isEmpty()){
            switch (ic->category()) {
            case Arg::Spin:
                cmds.spin << cmd;
                break;
            case Arg::Gcc:
                cmds.gcc << cmd;
                break;
            case Arg::Pan:
                cmds.pan << cmd;
                break;
            }
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
        _ltl = ic;
        _commands <<ic;
    }
    else if (name == ItemAdvancedStringConfiguration::staticMetaObject.className()){
        auto ic = qobject_cast<ItemAdvancedStringConfiguration*>(item);
        _commands << ic;
    }
}

ItemLTLConfiguration *SpinCommands::ltl(){ return _ltl;}

