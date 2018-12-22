#ifndef SPINCOMMANDS_H
#define SPINCOMMANDS_H
#include <QObject>
#include <QList>
#include "qspin/QObjectBase.h"
#include "qspin/models/IQsSerialization.h"
#include "qspin/models/Arg.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QPointer>
class ItemConfiguration;
class ItemValueConfiguration;
class ItemLTLConfiguration;
#include "qspin/models/QsItemConfiguration.h"
struct compiledCommands{
    QStringList spin;
    QStringList gcc;
    QStringList pan;
};

class SpinCommands : public QObjectBase, public IQXmlSerialization
{
    Q_OBJECT

    QPointer<ItemLTLConfiguration> _ltl=nullptr;
    QList<ItemConfiguration*> _commands;


    // IQXmlSerialization interface
public:
    explicit SpinCommands(QObject* parent = nullptr, EventAggregator* msgService=nullptr);
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
    compiledCommands CommandsToStringLists();
    void append(ItemConfiguration* item);
    ItemLTLConfiguration* ltl();
    static QString tmpSpinFileName(){ return "tmp.pml";}
    static QString tmpLtlFileName(){ return "tmp.ltl";}
};


#endif // SPINCOMMANDS_H
