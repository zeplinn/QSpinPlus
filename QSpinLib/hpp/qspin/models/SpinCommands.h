#ifndef SPINCOMMANDS_H
#define SPINCOMMANDS_H
#include <QObject>
#include <QList>
#include "qspin/QObjectBase.h"
#include "qspin/models/IQsSerialization.h"
#include "qspin/models/Arg.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
class ItemConfiguration;
class ItemValueConfiguration;
class ItemLTLConfiguration;
struct compiledCommands{
    QStringList spin;
    QStringList gcc;
    QStringList pan;
};

class SpinCommands : public QObjectBase, public IQXmlSerialization
{
    Q_OBJECT

    QList<ItemConfiguration*> _commands;


    // IQXmlSerialization interface
public:
    using QObjectBase::QObjectBase;
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
    compiledCommands writeCommands();
    void append(ItemConfiguration* item);
    void append(ItemValueConfiguration* item);
};


#include "qspin/models/QsItemConfiguration.h"
#endif // SPINCOMMANDS_H
