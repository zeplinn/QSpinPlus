#include "qspin/models/QsItemConfiguration.h"


Arg::Type ItemConfiguration::command() const{ return _command;}

QString ItemConfiguration::name() const{return Arg::name(_command);}

bool ItemConfiguration::checked() const {return _checked;}

bool ItemConfiguration::enabled() const{return _enabled;}

QString ItemConfiguration::argument() const {return Arg::val(command());}

void ItemConfiguration::setChecked(bool value){
    if(_checked != value){
        _checked  =value;
        emit checkedChanged();
    }
}

ItemConfiguration::ItemConfiguration(Arg::Type commandId, QObject *parent):QObject(parent)
  ,_command(commandId),_checked(false),_enabled(false)
{
    if(Arg::isSpinArgument(commandId))       _category = Arg::Spin;
    else if(Arg::isCompileArgument(commandId))    _category = Arg::Compile;
    else if(Arg::isPanArgument(commandId))        _category = Arg::Pan;
    else throw QString("argument is not a category: %1").arg(Arg::name(commandId));
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

QString ItemValueConfiguration::argument() const{return Arg::val(command(),commandValue());}

ItemValueConfiguration::ItemValueConfiguration(Arg::Type command, int value, int minValue, int maxValue, QObject *parent):
    ItemConfiguration(command,parent),_commandValue(value),_minValue(minValue),_maxValue(maxValue){}

Arg::Type ItemTextFileConfiguration::choice() const{return command();}

void ItemTextFileConfiguration::setChoice(Arg::Type value){
    if(command()!= value){
        setCommand(value);
        emit choiceChanged();
    }
}

ItemTextFileConfiguration::ItemTextFileConfiguration(Arg::Type defaultCommand, QObject *parent):ItemConfiguration(defaultCommand,parent){}
