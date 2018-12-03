#include "qspin/models/QsVerificationConfiguration.h"


ItemLTLConfiguration *VerificationConfiguration::ltl() const{ return qobject_cast<ItemLTLConfiguration*>( spinConfigs[Arg::LTL]); }

ItemAdvancedStringConfiguration *VerificationConfiguration::spin() const{ return _spin; }

ItemAdvancedStringConfiguration *VerificationConfiguration::gcc() const{ return _gcc; }

ItemAdvancedStringConfiguration *VerificationConfiguration::pan() const{ return _pan; }

QString VerificationConfiguration::name() const{return _name;}

void VerificationConfiguration::setName(QString value){
    if(_name != value){
        _name = value;
        emit nameChanged();
    }
}

ItemConfiguration *VerificationConfiguration::o1() const{return spinConfigs[Arg::O1];}

ItemConfiguration *VerificationConfiguration::o2() const{return spinConfigs[Arg::O2];}

ItemConfiguration *VerificationConfiguration::o3() const{return spinConfigs[Arg::O3];}

ItemConfiguration *VerificationConfiguration::o4() const{return spinConfigs[Arg::O4];}

ItemConfiguration *VerificationConfiguration::o5() const{return spinConfigs[Arg::O5];}

ItemConfiguration *VerificationConfiguration::o6() const{return spinConfigs[Arg::O6];}

// compile configs

ItemConfiguration *VerificationConfiguration::safety() const{return spinConfigs[Arg::Safety];}

ItemConfiguration *VerificationConfiguration::sfh() const{return spinConfigs[Arg::SFH];}

ItemConfiguration *VerificationConfiguration::noFair() const{return spinConfigs[Arg::NoFair];}

ItemConfiguration *VerificationConfiguration::np() const{return spinConfigs[Arg::NonProgressCycle];}

ItemConfiguration *VerificationConfiguration::bfs() const{return spinConfigs[Arg::BFS];}

ItemConfiguration *VerificationConfiguration::bfs_disk() const{return spinConfigs[Arg::BFS_DISK];}

ItemValueConfiguration *VerificationConfiguration::bfs_disk_limit() const{return toValueItem(Arg::BFS_DISK_LIMIT);}

ItemValueConfiguration *VerificationConfiguration::bfs_limit() const{return toValueItem( Arg::BFS_LIMIT);}

ItemValueConfiguration *VerificationConfiguration::nfair() const{return qobject_cast<ItemValueConfiguration*>( spinConfigs[Arg::NFair]);}

ItemConfiguration *VerificationConfiguration::noReduce() const{return spinConfigs[Arg::NoReduce];}

ItemConfiguration *VerificationConfiguration::space() const{return spinConfigs[Arg::Space];}

ItemValueConfiguration *VerificationConfiguration::vectorSZV() const{return qobject_cast<ItemValueConfiguration*>(spinConfigs[Arg::VectorSZV]);}

ItemValueConfiguration *VerificationConfiguration::memLimit() const{return qobject_cast<ItemValueConfiguration*>(spinConfigs[Arg::MemLim]);}

ItemConfiguration *VerificationConfiguration::collapse() const{return spinConfigs[Arg::Collapse];}

ItemValueConfiguration *VerificationConfiguration::hc() const{ return toValueItem(Arg::HC);}



// pan configs

ItemValueConfiguration *VerificationConfiguration::timeLimit() const{return toValueItem(Arg::TimeLimit);}

ItemConfiguration *VerificationConfiguration::safetyMode() const{return spinConfigs[Arg::SafetyMode];}

ItemConfiguration *VerificationConfiguration::progressMode() const{return spinConfigs[Arg::ProgressMode];}

ItemConfiguration *VerificationConfiguration::acceptanceMode() const{return spinConfigs[Arg::AccepanceMode];}

ItemValueConfiguration *VerificationConfiguration::hashSize() const{return toValueItem(Arg::HashSize);}

ItemValueConfiguration *VerificationConfiguration::searchDepth() const{return toValueItem( Arg::SearchDepth);}

ItemConfiguration *VerificationConfiguration::weakFairness() const{return spinConfigs[Arg::WeakFairness];}


Arg::Type VerificationConfiguration::currentMode(){return _currentMode;}

VerificationConfiguration::VerificationConfiguration(QObject *parent, EventAggregator *msgService)
    :QObjectBase(parent,msgService)
    ,_currentMode(Arg::SafetyMode)
{
    addNewConfigItem(Arg::O1);
    addNewConfigItem(Arg::O2);
    addNewConfigItem(Arg::O3);
    addNewConfigItem(Arg::O4);
    addNewConfigItem(Arg::O5);
    addNewConfigItem(Arg::O6);
    addNewLtlConfigItem(Arg::LTL)->required(Arg::AccepanceMode);

    //    // compileTime options
    addNewConfigItem(Arg::Safety)->required(Arg::SafetyMode);
    addNewConfigItem(Arg::SFH)->required(Arg::SafetyMode);
    addNewConfigItem(Arg::NoFair)->required(Arg::SafetyMode);
    addNewConfigItem(Arg::NonProgressCycle)->required(Arg::ProgressMode);
    addNewConfigItem(Arg::BFS);
    addNewConfigItem(Arg::BFS_DISK)->required(Arg::BFS);
    addNewConfigValueItem(Arg::BFS_DISK_LIMIT,INT32_MAX,128,1000000)->required(Arg::BFS);
    addNewConfigValueItem(Arg::BFS_LIMIT,INT32_MAX,0,100000)->required(Arg::BFS);
    addNewConfigValueItem(Arg::NFair,3,0,2);
    addNewConfigItem(Arg::NoReduce);
    addNewConfigItem(Arg::Space);
    addNewConfigValueItem(Arg::VectorSZV,INT32_MAX,128,1024);
    addNewConfigValueItem(Arg::MemLim,INT32_MAX,256,256);
    // compile memory compression
    addNewConfigItem(Arg::Collapse)->notIf(Arg::HC);
    addNewConfigValueItem(Arg::HC,3,0,2)->notIf(Arg::Collapse);

    //pan runtime options
    addNewConfigValueItem(Arg::TimeLimit,INT32_MAX,0,30);
    addNewConfigItem(Arg::SafetyMode)->notIf(Arg::ProgressMode)->notIf(Arg::AccepanceMode);
    addNewConfigItem(Arg::ProgressMode)->notIf(Arg::SafetyMode)->notIf(Arg::AccepanceMode);
    addNewConfigItem(Arg::AccepanceMode)->notIf(Arg::SafetyMode)->notIf(Arg::ProgressMode);
    addNewConfigValueItem(Arg::HashSize,INT32_MAX,1,18);
    addNewConfigValueItem(Arg::SearchDepth,INT32_MAX,256,10000);
    addNewConfigItem(Arg::WeakFairness)->notIf(Arg::SafetyMode);

    // allways available item configurations
    _spin = new ItemAdvancedStringConfiguration(Arg::Spin,parent,this->msgService());
    _gcc = new ItemAdvancedStringConfiguration(Arg::Gcc,parent,this->msgService());
    _pan = new ItemAdvancedStringConfiguration(Arg::Pan,parent,this->msgService());
}


SpinCommands *VerificationConfiguration::getSpinCommands(){
    auto commands = new SpinCommands();
    for(auto c: spinConfigs){
        if(c->checked() && c->enabled()){
            commands->append(c);
        }

    }
    commands->append(_spin);
    commands->append(_gcc);
    commands->append(_pan);
    return commands;
}



void VerificationConfiguration::read(QXmlStreamReader &xml){
    auto attr = xml.attributes();
    if(attr.hasAttribute("name"))
        setName(attr.value("name").toString());
    else setName("nameMissing");
    while (xml.readNextStartElement()) {
        QString n = xml.name().toString();
        if(xml.name()==ItemValueConfiguration::staticMetaObject.className()
                || xml.name()==ItemConfiguration::staticMetaObject.className()
                || xml.name()==ItemLTLConfiguration::staticMetaObject.className()
                )
        {

            auto attr = xml.attributes();
            auto index = static_cast<Arg::Type>(attr.value("command").toInt());
            spinConfigs[index]->read(xml);
        }
        else{
            xml.raiseError("invalid configuration object");
        }
    }
    updateConfigurations();

}

void VerificationConfiguration::write(QXmlStreamWriter &xml){
    xml.writeStartElement(qs().nameof(this));
    xml.writeAttribute("name",name());
    for(auto ic: spinConfigs)
        ic->write(xml);
    xml.writeEndElement();// verification configuration

}

QStringList VerificationConfiguration::getCurrentCommandsAsStrings(){
    auto spincmds = getSpinCommands();
    auto cmds = spincmds->CommandsToStringLists();
    spincmds->deleteLater();
    return QStringList()<< cmds.spin.join(" ") << cmds.gcc.join(" ") << cmds.pan.join(" ");
}

void VerificationConfiguration::updateSelectedVerifyMode(int mode){
    _currentMode = static_cast<Arg::Type>( mode);
    emit verifyModeChanged(currentMode());
}

void VerificationConfiguration::updateConfigurations(){
    notifiers.updateAllRequirements();
}

ItemConfigStateNotifier *VerificationConfiguration::addNewConfigItem(Arg::Type command){
    auto item = new ItemConfiguration(command,this,msgService());
    ItemConfigStateNotifier* notifier = notifiers.getNotifier(command);
    notifier->setConfig(item);
    spinConfigs[command]=item;
    return notifier;
}
ItemConfigStateNotifier *VerificationConfiguration::addNewLtlConfigItem(Arg::Type command){
    auto item = new ItemLTLConfiguration(command,this,msgService());
    ItemConfigStateNotifier* notifier = notifiers.getNotifier(command);
    notifier->setConfig(item);
    spinConfigs[command]=item;
    return notifier;
}

ItemConfigStateNotifier *VerificationConfiguration::addNewConfigValueItem(Arg::Type command, int maxValue, int minValue, int value ){
    auto item = new ItemValueConfiguration(command,value, minValue,maxValue,this,msgService());
    auto notifier = notifiers.getNotifier(command);
    notifier->setConfig(item);
    spinConfigs[command]=item;
    return notifier;
}

ItemValueConfiguration *VerificationConfiguration::toValueItem(Arg::Type command) const{
    return  qobject_cast<ItemValueConfiguration*>(spinConfigs[command]);
}

