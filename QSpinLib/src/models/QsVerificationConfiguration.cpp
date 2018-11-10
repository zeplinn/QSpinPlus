#include "qspin/models/QsVerificationConfiguration.h"


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

VerificationConfiguration::VerificationConfiguration(QObject *parent):QObject(parent),_currentMode(Arg::SafetyMode)

{
    auto &list= *new ItemConfigStateNotifierList(this);
    // spin options
    auto c = new ItemConfiguration(Arg::Verify,this); // allways added
    c->setChecked(true);
    c->setEnabled(true);
    spinConfigs[Arg::Verify] = c;
    addNewConfigItem(list,Arg::O1);
    addNewConfigItem(list,Arg::O2);
    addNewConfigItem(list,Arg::O3);
    addNewConfigItem(list,Arg::O4);
    addNewConfigItem(list,Arg::O5);
    addNewConfigItem(list,Arg::O6);
// remember to add ltl item

//    // compileTime options
    addNewConfigItem(list,Arg::Safety)->required(Arg::SafetyMode);
    addNewConfigItem(list,Arg::SFH)->required(Arg::SafetyMode);
    addNewConfigItem(list,Arg::NoFair)->required(Arg::SafetyMode);
    addNewConfigItem(list,Arg::NonProgressCycle)->required(Arg::ProgressMode);
    addNewConfigItem(list,Arg::BFS);
    addNewConfigItem(list,Arg::BFS_DISK)->required(Arg::BFS);
    addNewConfigValueItem(list,Arg::BFS_DISK_LIMIT,INT32_MAX,128,1000000)->required(Arg::BFS);
    addNewConfigValueItem(list,Arg::BFS_LIMIT,INT32_MAX,0,100000)->required(Arg::BFS);
    addNewConfigValueItem(list,Arg::NFair,3,0,2);
    addNewConfigItem(list,Arg::NoReduce);
    addNewConfigItem(list,Arg::Space);
    addNewConfigValueItem(list,Arg::VectorSZV,INT32_MAX,128,1024);
    addNewConfigValueItem(list,Arg::MemLim,INT32_MAX,256,256);
    // compile memory compression
    addNewConfigItem(list,Arg::Collapse)->notIf(Arg::HC);
    addNewConfigValueItem(list,Arg::HC,3,0,2)->notIf(Arg::Collapse);

    //pan runtime options
    addNewConfigValueItem(list,Arg::TimeLimit,INT32_MAX,0,30);
    addNewConfigItem(list,Arg::SafetyMode)->notIf(Arg::ProgressMode)->notIf(Arg::AccepanceMode);
    addNewConfigItem(list,Arg::ProgressMode)->notIf(Arg::SafetyMode)->notIf(Arg::AccepanceMode);
    addNewConfigItem(list,Arg::AccepanceMode)->notIf(Arg::SafetyMode)->notIf(Arg::ProgressMode);
    addNewConfigValueItem(list,Arg::HashSize,18);
    addNewConfigValueItem(list,Arg::SearchDepth,10000);
    addNewConfigItem(list,Arg::WeakFairness)->notIf(Arg::SafetyMode);
    list.updateAllRequirements();
}

void VerificationConfiguration::updateSelectedVerifyMode(int mode){
    _currentMode = static_cast<Arg::Type>( mode);
    emit verifyModeChanged(currentMode());
}

ItemConfigStateNotifier *VerificationConfiguration::addNewConfigItem(ItemConfigStateNotifierList &notifierList, Arg::Type command){
    auto item = new ItemConfiguration(command,this);
    ItemConfigStateNotifier* notifier = notifierList.getNotifier(command);
    notifier->setConfig(item);
    spinConfigs[command]=item;
    return notifier;
}

ItemConfigStateNotifier *VerificationConfiguration::addNewConfigValueItem(ItemConfigStateNotifierList &notifierList, Arg::Type command, int maxValue, int minValue, int value ){
    auto item = new ItemValueConfiguration(command,value, minValue,maxValue,this);
    auto notifier = notifierList.getNotifier(command);
    notifier->setConfig(item);
    spinConfigs[command]=item;
    return notifier;
}

ItemValueConfiguration *VerificationConfiguration::toValueItem(Arg::Type command) const{
    return  qobject_cast<ItemValueConfiguration*>(spinConfigs[command]);
}

