#ifndef QSVERIFICATIONCONFIGURATION_H
#define QSVERIFICATIONCONFIGURATION_H
#include <QObject>
#include "Arg.h"
#include "qspin/models/QsItemConfiguration.h"

//typedef SimpleConfiguration sc;
class VerificationConfiguration: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QString _name;
    //spin configs
    Q_PROPERTY(ItemConfiguration* o1 READ o1 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o2 READ o2 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o3 READ o3 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o4 READ o4 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o5 READ o5 CONSTANT)
    Q_PROPERTY(ItemConfiguration* o6 READ o6 CONSTANT)
//    Q_PROPERTY(ItemConfiguration* verifyMode READ verifyMode CONSTANT)
//    ItemConfiguration *_o1,*_o2,*_o3,*_o4,*_o5,*_o6; // o7 is allways enabled for parser to work
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
    Q_PROPERTY(ItemConfiguration* hc0 READ hc0 CONSTANT)
    Q_PROPERTY(ItemConfiguration* hc1 READ hc1 CONSTANT)
    Q_PROPERTY(ItemConfiguration* hc2 READ hc2 CONSTANT)
    Q_PROPERTY(ItemConfiguration* hc3 READ hc3 CONSTANT)
//    ItemConfiguration *_safety, *_sfh, *_noFair, *_np, *_bfs, *_bfs_disk, *_noReduce, *_space, *_nfair ;
//    ItemChoiceConfiguration  *_bfs_disk_limit, *_bfs_limit, *_vectorSZV, _memLimit;

    // pan runtime configs
    Q_PROPERTY(ItemValueConfiguration* timeLimit READ timeLimit CONSTANT)
    Q_PROPERTY(ItemConfiguration* safetyMode READ safetyMode CONSTANT)
    Q_PROPERTY(ItemConfiguration* progressMode READ progressMode CONSTANT)
    Q_PROPERTY(ItemConfiguration* acceptanceMode READ acceptanceMode CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* hashSize READ hashSize CONSTANT)
    Q_PROPERTY(ItemValueConfiguration* searchDepth READ searchDepth CONSTANT)
    Q_PROPERTY(ItemConfiguration* weakFairness READ weakFairness CONSTANT)
//    ItemConfiguration* _saftyMode, *_progressMode, *_acceptanceMode;
//    ItemChoiceConfiguration *_timeLimit,* _verifyMode;

    QHash<Arg::Type,ItemConfiguration*> spinConfigs;
    QHash<Arg::Type,ItemConfiguration*> compileConfigs;
    QHash<Arg::Type,ItemConfiguration*> panConfigs;
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
    // add ltl command later
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
    ItemConfiguration* hc0()const;
    ItemConfiguration* hc1()const;
    ItemConfiguration* hc2()const;
    ItemConfiguration* hc3()const;

    // pan runtime commands
    ItemValueConfiguration* timeLimit()const;
    ItemConfiguration* safetyMode()const;
    ItemConfiguration* progressMode()const;
    ItemConfiguration* acceptanceMode()const;
    ItemValueConfiguration* hashSize()const;
    ItemValueConfiguration* searchDepth()const;
    ItemConfiguration* weakFairness()const;
   // ItemChoiceConfiguration* verifyMode()const;
signals:// properties
    void nameChanged();
    void saftyModeChanged();

public:
    Arg::Type currentMode();
    explicit VerificationConfiguration(QObject* parent = nullptr);

signals:
    void itemConfigurationChanged();
    void verifyModeChanged(Arg::Type mode);
public slots:
    void updateSelectedVerifyMode(int mode);
private:
    ItemConfiguration* newSpinItem(Arg::Type command,int value =-1);
    ItemConfiguration* newCompileItem(Arg::Type command,int value =-1);
    ItemConfiguration* newPanItem(Arg::Type command,int value =-1);



};

#endif // QSVERIFICATIONCONFIGURATION_H
