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

ItemConfiguration *VerificationConfiguration::safety() const{return compileConfigs[Arg::Safety];}

ItemConfiguration *VerificationConfiguration::sfh() const{return compileConfigs[Arg::SFH];}

ItemConfiguration *VerificationConfiguration::noFair() const{return compileConfigs[Arg::NoFair];}

ItemConfiguration *VerificationConfiguration::np() const{return compileConfigs[Arg::NonProgressCycle];}

ItemConfiguration *VerificationConfiguration::bfs() const{return compileConfigs[Arg::BFS];}

ItemConfiguration *VerificationConfiguration::bfs_disk() const{return compileConfigs[Arg::BFS_DISK];}

ItemValueConfiguration *VerificationConfiguration::bfs_disk_limit() const{return qobject_cast<ItemValueConfiguration*>( compileConfigs[Arg::BFS_DISK_LIMIT]);}

ItemValueConfiguration *VerificationConfiguration::bfs_limit() const{return qobject_cast<ItemValueConfiguration*>( compileConfigs[Arg::BFS_LIMIT]);}

ItemValueConfiguration *VerificationConfiguration::nfair() const{return qobject_cast<ItemValueConfiguration*>( compileConfigs[Arg::NFair]);}

ItemConfiguration *VerificationConfiguration::noReduce() const{return compileConfigs[Arg::NoReduce];}

ItemConfiguration *VerificationConfiguration::space() const{return compileConfigs[Arg::Space];}

ItemValueConfiguration *VerificationConfiguration::vectorSZV() const{return qobject_cast<ItemValueConfiguration*>(compileConfigs[Arg::VectorSZV]);}

ItemValueConfiguration *VerificationConfiguration::memLimit() const{return qobject_cast<ItemValueConfiguration*>(compileConfigs[Arg::MemLim]);}

ItemConfiguration *VerificationConfiguration::collapse() const{return compileConfigs[Arg::Collapse];}

ItemConfiguration *VerificationConfiguration::hc0() const{return compileConfigs[Arg::HC0];}

ItemConfiguration *VerificationConfiguration::hc1() const{return compileConfigs[Arg::HC1];}

ItemConfiguration *VerificationConfiguration::hc2() const{return compileConfigs[Arg::HC2];}

ItemConfiguration *VerificationConfiguration::hc3() const{return compileConfigs[Arg::HC3];}

// pan configs

ItemValueConfiguration *VerificationConfiguration::timeLimit() const{return qobject_cast<ItemValueConfiguration*>(panConfigs[Arg::TimeLimit]);}

ItemConfiguration *VerificationConfiguration::safetyMode() const{return panConfigs[Arg::SafetyMode];}

ItemConfiguration *VerificationConfiguration::progressMode() const{return panConfigs[Arg::ProgressMode];}

ItemConfiguration *VerificationConfiguration::acceptanceMode() const{return panConfigs[Arg::AccepanceMode];}

ItemValueConfiguration *VerificationConfiguration::hashSize() const{return qobject_cast<ItemValueConfiguration*>(panConfigs[Arg::HashSize]);}

ItemValueConfiguration *VerificationConfiguration::searchDepth() const{return qobject_cast<ItemValueConfiguration*> (panConfigs[Arg::SearchDepth]);}

ItemConfiguration *VerificationConfiguration::weakFairness() const{return panConfigs[Arg::WeakFairness];}

Arg::Type VerificationConfiguration::currentMode(){return _currentMode;}

//ItemChoiceConfiguration *VerificationConfiguration::verifyMode() const{ return _verifyMode;}

VerificationConfiguration::VerificationConfiguration(QObject *parent):QObject(parent),_currentMode(Arg::SafetyMode)
//  ,_saftyMode(new ItemConfiguration(Arg::SaftyMode,this))
//  ,_progressMode(new ItemConfiguration(Arg::ProgressMode,this))
//  ,_acceptanceMode(new ItemConfiguration(Arg::AccepanceMode,this))
//  ,_verifyMode(new ItemChoiceConfiguration(Arg::SaftyMode))
{
    // spin options
    auto c = new ItemConfiguration(Arg::Verify,this); // allways added
    c->setChecked(true);
    spinConfigs[Arg::Verify] = c;
    newSpinItem(Arg::O1);
    newSpinItem(Arg::O2);
    newSpinItem(Arg::O3);
    newSpinItem(Arg::O4);
    newSpinItem(Arg::O5);
    newSpinItem(Arg::O6);

//    // compileTime options
    newCompileItem(Arg::Safety)->onlyIf(Arg::SafetyMode);
    newCompileItem(Arg::SFH)->onlyIf(Arg::SafetyMode);
    newCompileItem(Arg::NoFair,2)->onlyIf(Arg::SafetyMode);
    newCompileItem(Arg::NonProgressCycle)->onlyIf(Arg::ProgressMode);
    newCompileItem(Arg::BFS);
    newCompileItem(Arg::BFS_DISK)->onlyIf(Arg::BFS);
    newCompileItem(Arg::BFS_DISK_LIMIT,1000000)->onlyIf(Arg::BFS);
    newCompileItem(Arg::BFS_LIMIT,100000)->onlyIf(Arg::BFS);
    newCompileItem(Arg::NFair);
    newCompileItem(Arg::NoReduce);
    newCompileItem(Arg::Space);
    newCompileItem(Arg::VectorSZV,1024);
    newCompileItem(Arg::MemLim,256);
    // compile memory compression
    newCompileItem(Arg::Collapse);
    newCompileItem(Arg::HC0);
    newCompileItem(Arg::HC1);
    newCompileItem(Arg::HC2);
    newCompileItem(Arg::HC3);

    //pan runtime options
    newPanItem(Arg::TimeLimit,30);
    newPanItem(Arg::SafetyMode)->notIf(Arg::ProgressMode)->notIf(Arg::AccepanceMode)->setChecked(true);
    newPanItem(Arg::ProgressMode)->notIf(Arg::SafetyMode)->notIf(Arg::AccepanceMode);
    newPanItem(Arg::AccepanceMode)->notIf(Arg::SafetyMode)->notIf(Arg::ProgressMode);
    newPanItem(Arg::HashSize,18);
    newPanItem(Arg::SearchDepth,10000);
    newPanItem(Arg::WeakFairness)->notIf(Arg::SafetyMode);
}

void VerificationConfiguration::updateSelectedVerifyMode(int mode){
    _currentMode = static_cast<Arg::Type>( mode);
    //qDebug()<<"update SelectedVerifyMode called ->"<< Arg::name(_currentMode);
    emit verifyModeChanged(currentMode());
}

ItemConfiguration *VerificationConfiguration::newSpinItem(Arg::Type command, int value){
    ItemConfiguration* c;
    if(value<0) c = new ItemConfiguration(command,this);
    else c = new ItemValueConfiguration(command,value,this);
    spinConfigs[command] = c;
    return c;
}

ItemConfiguration *VerificationConfiguration::newCompileItem(Arg::Type command, int value){
    ItemConfiguration* c;
    if(value<0) c = new ItemConfiguration(command,this);
    else c = new ItemValueConfiguration(command,value,this);
    compileConfigs[command] = c;
    return c;
}

ItemConfiguration *VerificationConfiguration::newPanItem(Arg::Type command, int value){
    ItemConfiguration* c;
    if(value<0) c = new ItemConfiguration(command,this);
    else c = new ItemValueConfiguration(command,value,this);
    panConfigs[command] = c;
    return c;
}
