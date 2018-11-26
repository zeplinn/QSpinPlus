#ifndef QSITEMCONFIGSTATENOTIFIER_H
#define QSITEMCONFIGSTATENOTIFIER_H
#include <QObject>
#include <QSharedPointer>
class ItemConfiguration;
class ItemConfigStateNotifier;
#include "qspin/models/Arg.h"
class ItemConfigStateNotifierList:public QObject{
    Q_OBJECT
    typedef QHash<Arg::Type,ItemConfigStateNotifier*> notifierList;
notifierList _list;
public:
explicit ItemConfigStateNotifierList(QObject* parent= nullptr);
    void updateAllRequirements(){  emit allRequirementsUpdated();  }
    ItemConfigStateNotifier* getNotifier(Arg::Type key);
    bool contains(Arg::Type key){return  _list.contains(key);}
    ItemConfigStateNotifier *attachItemConfigurationTo(ItemConfiguration* item,Arg::Type key);
    bool isEmpty()const{ return _list.isEmpty();}
signals:
    void allRequirementsUpdated();
};

class ItemConfigStateNotifier: public QObject{
    Q_OBJECT
    bool _nothingIsRequired = true;
    bool atLeatOneRequired= false;
    int countRequired=0;
    ItemConfiguration* config;
    ItemConfigStateNotifierList *_notifierList;
    QHash<Arg::Type,Arg::Type> _require;
    QHash<Arg::Type,Arg::Type> _notIf;
    QHash<Arg::Type,Arg::Type> _requireOne;
public:
    explicit ItemConfigStateNotifier(ItemConfigStateNotifierList *notifiers=nullptr);
    void setConfig(ItemConfiguration* value);
    ItemConfigStateNotifier *notIf(Arg::Type command);
    ItemConfigStateNotifier *requireAtLeastOne(Arg::Type command);
    ItemConfigStateNotifier *required(Arg::Type command);
signals:
    void statusChanged(Arg::Type command,bool enabled, bool checked);
public slots:

// slots are private to ensure no connections outside can be made
private slots:
    void updateNotIf(Arg::Type command,bool enabled,bool checked);
    void updateRequireAtLeastOne(Arg::Type command,bool enabled, bool checked);
    void updateRequire(Arg::Type command,bool enabled, bool checked);
    void CondigCheckedChanged();
private:
    void updateEnabledStatus();
    bool isEnabled();
    ItemConfigStateNotifierList& list(){return *_notifierList;}
    void removeAndUpdate(Arg::Type command);
};
#include "qspin/models/QsItemConfiguration.h"
#endif // QSITEMCONFIGSTATENOTIFIER_H
