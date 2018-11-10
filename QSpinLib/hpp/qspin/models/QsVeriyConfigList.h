#ifndef QSVERIYCONFIGLIST_H
#define QSVERIYCONFIGLIST_H
#include "qspin/models/QsItemConfiguration.h"
#include "qspin/models/Arg.h"
class QsVeriyConfigList{
    QHash<Arg::Type,ItemConfiguration*> _configs;

public:

    void append(ItemConfiguration* item){
        _configs[item->command()] = item;
    }

    void saveConfig(){}
    void compileVerifications(){

    }
};

#endif // QSVERIYCONFIGLIST_H
