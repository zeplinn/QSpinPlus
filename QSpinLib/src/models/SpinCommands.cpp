#include "qspin/models/SpinCommands.h"


void SpinCommands::read(QXmlStreamReader &xml)
{
    if(Qs::isClassName<SpinCommands>(xml.name())){
        while (xml.readNextStartElement()) {
            auto attr = xml.attributes();
            Arg::Type cmd =Arg::None;
            if(attr.hasAttribute("command"))
                cmd = static_cast<Arg::Type>(attr.value("command").toInt());
            if(xml.name()=="ItemConfiguration"){
                auto ic = new ItemConfiguration(cmd,this);
                ic->read(xml);
            }
            else if(xml.name()=="ItemValueConfiguration"){
                auto ivc = new ItemValueConfiguration(cmd,0,0,0,this);
                ivc->read(xml);
            }
            else if(xml.name()=="ItemFileConfiguration"){
                // ltl
            }
        }
    }
}

void SpinCommands::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(Qs::nameof<SpinCommands>());
    for ( auto ic : _commands)
        ic->write(xml);
    xml.writeEndElement();
}

compiledCommands SpinCommands::writeCommands(){
    compiledCommands cmds;
    for(auto ic : _commands){
        switch (ic->category()) {
        case Arg::Spin:
            cmds.spin << ic->writeCommand();
            break;
        case Arg::Compile:
            cmds.gcc << ic->writeCommand();
            break;
        case Arg::Pan:
            cmds.pan << ic->writeCommand();
            break;
        }
    }
    return cmds;
}

void SpinCommands::append(ItemConfiguration *item){
    _commands << new ItemConfiguration(item);
}

void SpinCommands::append(ItemValueConfiguration *item){
    _commands << new ItemValueConfiguration(item);
}
