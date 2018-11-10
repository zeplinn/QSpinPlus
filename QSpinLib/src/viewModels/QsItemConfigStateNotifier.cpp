#include "qspin/models/QsItemConfigStateNotifier.h"

ItemConfigStateNotifier::ItemConfigStateNotifier(ItemConfigStateNotifierList *notifiers):
    QObject(notifiers),config(nullptr),_notifierList(notifiers){
    connect(notifiers,&ItemConfigStateNotifierList::allRequirementsUpdated,this,&ItemConfigStateNotifier::CondigCheckedChanged);
}

void ItemConfigStateNotifier::setConfig(ItemConfiguration *value){
    config = value;
    //config->setEnabled(_nothingIsRequired);
    connect(config,&ItemConfiguration::checkedChanged,this,&ItemConfigStateNotifier::CondigCheckedChanged);
}

ItemConfigStateNotifier* ItemConfigStateNotifier::notIf(Arg::Type command){
    ItemConfigStateNotifier * n = list().getNotifier(command);
    connect(n,&ItemConfigStateNotifier::statusChanged
            ,this,&ItemConfigStateNotifier::updateNotIf);
    return this;
}

ItemConfigStateNotifier* ItemConfigStateNotifier::requireAtLeastOne(Arg::Type command){
    _nothingIsRequired=false;

    ItemConfigStateNotifier * n = list().getNotifier(command);
    atLeatOneRequired =true;
    connect(n,&ItemConfigStateNotifier::statusChanged
            ,this,&ItemConfigStateNotifier::updateRequireAtLeastOne);
    return this;
}

ItemConfigStateNotifier* ItemConfigStateNotifier::required(Arg::Type command){
    _nothingIsRequired=false;
    ItemConfigStateNotifier * n = list().getNotifier(command);
    countRequired++;
    connect(n,&ItemConfigStateNotifier::statusChanged
            ,this,&ItemConfigStateNotifier::updateRequire);
    return this;
}
/*
  if ! enabled && checked && item->checked
*/
void ItemConfigStateNotifier::updateNotIf(Arg::Type command, bool enabled, bool checked){
    Q_UNUSED(enabled)
    // if statement could be compressed,
    // but is implemented for readability
    // comparision agains diagram verification control
    // 2^= 16 combinations
    // choices are described with  binary gates
    // checked config.checked enabled config.enabled
    // 1 = true, 0 = false, x = 0 or 1

    // covers 2 cases where 1 1 1 x
    if( checked && config->checked() && enabled){
        // add command
        // config. set checked = false
        if(!_notIf.contains(command)){
            _notIf[command]=command;
            config->setChecked(false);
        }

    }
    // covers 2 possible 1 0 1 x
    else if (enabled && checked && !config->checked()){
        //add command
        if(!_notIf.contains(command)){
            _notIf[command] = command;
            updateEnabledStatus();
        }
    }

    // covers 4 possible 1 x 0 x
    else if(checked && !enabled){
        // remove command
        // update enabled
        removeAndUpdate(command);
    }
    // covers 8 case where 0 x x x
    else if(!checked){
        // remove command
        //updateEnabled
        removeAndUpdate(command);
    }

}
void ItemConfigStateNotifier::removeAndUpdate(Arg::Type command){
    if(_notIf.contains(command)){
        _notIf.remove(command);
        updateEnabledStatus();
    }
}
void ItemConfigStateNotifier::updateRequireAtLeastOne(Arg::Type command, bool enabled, bool checked){
    // if state is true the command should be added if it do not exist
    Q_UNUSED(enabled)
    if(checked){
        if(!_requireOne.contains(command)){
            _requireOne[command]=command;
            updateEnabledStatus();
        }
    }
    else{
        if(_requireOne.contains(command)){
            _requireOne.remove(command);
            updateEnabledStatus();
        }
    }
}

void ItemConfigStateNotifier::updateRequire(Arg::Type command, bool enabled, bool checked){
    // id state is true the command the command should be added
    Q_UNUSED(enabled)
    if(checked){
        if(!_require.contains(command)){
            _require[command]=command;
            updateEnabledStatus();
        }
    }
    else{
        if(_require.contains(command)){
            _require.remove(command);
            updateEnabledStatus();
        }
    }
}

void ItemConfigStateNotifier::CondigCheckedChanged(){
    emit statusChanged(config->command(),config->enabled(),config->checked());
    bool flag =isEnabled();
    config->setEnabled(flag);
}

void ItemConfigStateNotifier::updateEnabledStatus(){
    bool tmp = isEnabled();
    //if(config->enabled()!=tmp){
    config->setEnabled(tmp);
    bool c = config->enabled();
    emit statusChanged(config->command(),c,config->checked());
    //}
}

bool ItemConfigStateNotifier::isEnabled(){
    return _notIf.count()== 0 && _require.count() == countRequired && (!atLeatOneRequired || _requireOne.count()>0);
}

ItemConfigStateNotifierList::ItemConfigStateNotifierList(QObject *parent):QObject(parent){}

ItemConfigStateNotifier *ItemConfigStateNotifierList::getNotifier(Arg::Type key){
    if(_list.contains(key))
        return _list[key];
    auto *n = new ItemConfigStateNotifier(this);
    _list[key]= n;
    return n;

}

ItemConfigStateNotifier* ItemConfigStateNotifierList::attachItemConfigurationTo(ItemConfiguration *item, Arg::Type key){
    auto i = getNotifier(key);
    i->setConfig(item);
    return  i;
}
