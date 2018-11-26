#ifndef VERIFICATIONRESULTSCONTAINER_H
#define VERIFICATIONRESULTSCONTAINER_H
#include <QObject>
#include <QDateTime>
#include <QFile>
#include "qspin/QObjectBase.h"
class SpinCommands;
#include "qspin/models/SpinCommands.h"
#include "qspin/models/IQsSerialization.h"
class VerificationResultContainer : public QObjectBase, public IQXmlSerialization
{
    Q_OBJECT
    QDateTime _created;
    QDateTime _started;
    QDateTime _finished;
    bool _createdSet= false, _startedSet=false,_finishedSet=false;
    SpinCommands* _commands;
    QString _document;
    QString _name;

public:
    using QObjectBase::QObjectBase;


    // IQXmlSerialization interface
public:
    explicit VerificationResultContainer(QObject* parent= nullptr, EventAggregator* msgService = nullptr)
        :QObjectBase(parent,msgService)
        ,_commands(new SpinCommands(this,msgService))
    {}
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
    SpinCommands& commands();
    void setCommands(SpinCommands* value);
    QFileInfo saveAs(QString name,QDir destination);
    bool open(const QFileInfo& filepath);
    QDateTime created()const;
};
#endif // VERIFICATIONRESULTSCONTAINER_H
