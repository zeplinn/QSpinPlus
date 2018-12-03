#ifndef QSVERIFICATIONCONFIGURATION_H
#define QSVERIFICATIONCONFIGURATION_H
#include <QObject>
#include <QDateTime>
#include <stdint.h>
//#include "qspin/Qs.h"
//#include <QXmlStreamReader>
#include "qspin/QObjectBase.h"
class SpinCommands;
#include "qspin/models/SpinCommands.h"
#include "qspin/models/VerificationResultContainer.h"
#include "Arg.h"
#include "qspin/models/IQsSerialization.h"
class ItemConfiguration;
class ItemValueConfiguration;
class ItemLTLConfiguration;
class ItemAdvancedStringConfiguration;
#include "qspin/models/QsItemConfigStateNotifier.h"
#include "qspin/models/QsItemConfiguration.h"
class VerificationConfiguration: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    // ##################### begin properties ######################
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QString _name;
    Q_PROPERTY(bool readonly READ readonly NOTIFY readonlyChanged)
    bool _readonly=false;
public:
    bool readonly()const{ return _readonly; }
    void setReadonly(bool value){
        if(_readonly != value){
            _readonly = value;
            emit readonlyChanged();
        }
    }
signals:
    void readonlyChanged();
    // properties for every spin configurations
private:
    //spin configs
    Q_PROPERTY(ItemConfiguration* o1 READ o1 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o2 READ o2 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o3 READ o3 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o4 READ o4 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o5 READ o5 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o6 READ o6 CONSTANT)
    Q_PROPERTY(ItemLTLConfiguration* ltl READ ltl CONSTANT)

    // compile configs
    Q_PROPERTY(ItemConfiguration* safety READ safety CONSTANT)
    Q_PROPERTY(ItemConfiguration* sfh READ sfh CONSTANT)
    Q_PROPERTY(ItemConfiguration* noFair READ noFair CONSTANT)
    Q_PROPERTY(ItemConfiguration* np READ np CONSTANT)
    Q_PROPERTY(ItemConfiguration* bfs READ bfs CONSTANT)
    Q_PROPERTY(ItemConfiguration* bfs_disk READ bfs_disk CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* bfs_disk_limit READ bfs_disk_limit CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* bfs_limit READ bfs_limit CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* nfair READ nfair CONSTANT)
    Q_PROPERTY(ItemConfiguration* noReduce READ noReduce CONSTANT)
    Q_PROPERTY(ItemConfiguration* space READ space CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* vectorSZV READ vectorSZV CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* memLimit READ memLimit CONSTANT)

    Q_PROPERTY(ItemConfiguration* collapse READ collapse CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* hc READ hc CONSTANT)

    // pan runtime configs
    Q_PROPERTY(ItemValueConfiguration* timeLimit READ timeLimit CONSTANT)
    Q_PROPERTY(ItemConfiguration* safetyMode READ safetyMode CONSTANT)
    Q_PROPERTY(ItemConfiguration* progressMode READ progressMode CONSTANT)
    Q_PROPERTY(ItemConfiguration* acceptanceMode READ acceptanceMode CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* hashSize READ hashSize CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* searchDepth READ searchDepth CONSTANT)
    Q_PROPERTY(ItemConfiguration* weakFairness READ weakFairness CONSTANT)

    // advneced string options
    ItemAdvancedStringConfiguration* _spin;
    Q_PROPERTY(ItemAdvancedStringConfiguration* spin READ spin CONSTANT)
    Q_PROPERTY(ItemAdvancedStringConfiguration* gcc READ gcc CONSTANT)
    Q_PROPERTY(ItemAdvancedStringConfiguration* pan READ pan CONSTANT)
    ItemAdvancedStringConfiguration* _gcc;
    ItemAdvancedStringConfiguration* _pan;


    Arg::Type _currentMode;
public:// properties
    QString name()const;
    void setName(QString value);
    // spin commands
    ItemConfiguration* o1()const;
    ItemConfiguration* o2()const;
    ItemConfiguration* o3()const;
    ItemConfiguration* o4()const;
    ItemConfiguration* o5()const;
    ItemConfiguration* o6()const;
    ItemLTLConfiguration* ltl()const;
    //compile commands
    ItemConfiguration* safety()const;
    ItemConfiguration* sfh()const;
    ItemConfiguration* noFair()const;
    ItemConfiguration* np()const;
    ItemConfiguration* bfs()const;
    ItemConfiguration* bfs_disk()const;
    ItemValueConfiguration* bfs_disk_limit()const;
    ItemValueConfiguration* bfs_limit()const;
    ItemValueConfiguration* nfair()const;
    ItemConfiguration* noReduce()const;
    ItemConfiguration* space()const;
    ItemValueConfiguration* vectorSZV()const;
    ItemValueConfiguration* memLimit()const;
    ItemConfiguration* collapse()const;
    ItemValueConfiguration* hc()const;

    // pan runtime commands
    ItemValueConfiguration* timeLimit()const;
    ItemConfiguration* safetyMode()const;
    ItemConfiguration* progressMode()const;
    ItemConfiguration* acceptanceMode()const;
    ItemValueConfiguration* hashSize()const;
    ItemValueConfiguration* searchDepth()const;
    ItemConfiguration* weakFairness()const;

    //advanced configs
    ItemAdvancedStringConfiguration* spin()const;
    ItemAdvancedStringConfiguration* gcc()const;
    ItemAdvancedStringConfiguration* pan()const;
    // end of properties for spin configurations
signals:// properties
    void nameChanged();
    void saftyModeChanged();
    // ##################### end properties ######################
private:
    QHash<Arg::Type,ItemConfiguration*> spinConfigs;
    QHash<Arg::Type,ItemConfigStateNotifier*> _itemNotifier; // item config notifier service
    ItemConfigStateNotifierList notifiers;


public:
    Arg::Type currentMode();
    explicit VerificationConfiguration(QObject* parent = nullptr, EventAggregator* msgService=nullptr);
    SpinCommands* getSpinCommands();
    // interface
    virtual void read(QXmlStreamReader& xml) override;
    virtual void write(QXmlStreamWriter& xml)override;
signals:
    void itemConfigurationChanged();
    void verifyModeChanged(Arg::Type mode);
public slots:
    QStringList getCurrentCommandsAsStrings();
    void updateSelectedVerifyMode(int mode);
    void updateConfigurations();
private:
    ItemConfigStateNotifier* addNewConfigItem( Arg::Type command);
    ItemConfigStateNotifier* addNewConfigValueItem( Arg::Type command,int maxValue,int minValue=0,int value =0);
    ItemValueConfiguration* toValueItem(Arg::Type command)const;


    ItemConfigStateNotifier *addNewLtlConfigItem(Arg::Type command);
};

// all needed cross dependency includes here

#endif // QSVERIFICATIONCONFIGURATION_H
