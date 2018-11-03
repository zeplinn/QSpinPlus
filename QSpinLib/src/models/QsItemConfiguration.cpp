#include "qspin/models/QsItemConfiguration.h"


Arg::Type ItemConfiguration::command() const{ return _command;}

QString ItemConfiguration::name() const{return _name;}

bool ItemConfiguration::checked() const {return _checked;}

void ItemConfiguration::setChecked(bool value){
    if(_checked != value){
        _checked  =value;
        emit checkedChanged();
    }
}

ItemConfiguration::ItemConfiguration(Arg::Type command, QObject *parent):QObject(parent),_command(command),_name(Arg::name(command)){}

ItemConfiguration *ItemConfiguration::onlyIf(Arg::Type command){
    _requirements << requirement(command,true);
    return this;
}

ItemConfiguration *ItemConfiguration::notIf(Arg::Type command){
    _requirements << requirement(command,false);
    return this;

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

ItemValueConfiguration::ItemValueConfiguration(Arg::Type command, int value, QObject *parent):ItemConfiguration(command,parent),_commandValue(value){}

Arg::Type ItemChoiceConfiguration::choice() const{return command();}

void ItemChoiceConfiguration::setChoice(Arg::Type value){
    if(command()!= value){
        setCommand(value);
        emit choiceChanged();
    }
}

ItemChoiceConfiguration::ItemChoiceConfiguration(Arg::Type defaultCommand, QObject *parent):ItemConfiguration(defaultCommand,parent){}
