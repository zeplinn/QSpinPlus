#ifndef VERIFICATIONRESULTSCONTAINER_H
#define VERIFICATIONRESULTSCONTAINER_H
#include <QObject>
#include <QDateTime>
#include <QFile>
#include "qspin/QObjectBase.h"
#include "qspin/models/QsVerificationResults.h"
class SpinCommands;
#include "qspin/models/SpinCommands.h"
#include "qspin/models/IQsSerialization.h"
class VerificationResultContainer : public QObjectBase, public IQXmlSerialization
{
    Q_OBJECT
    QDateTime _created;
    QDateTime _started;
    QDateTime _finished;
    SpinCommands* _commands= nullptr;
    VerificationResults* _results;
    QString _document;
    QString _trailDocument="";
    QString _name;
    QFileInfo _file;

public:
    explicit VerificationResultContainer(QObject* parent= nullptr, EventAggregator* msgService = nullptr);


    // IQXmlSerialization interface
public:
    virtual void read(QXmlStreamReader &xml) override;
    virtual void write(QXmlStreamWriter &xml) override;
    void setCommands(SpinCommands* value);
    void setDocument(QString document);
   // QFileInfo saveAs(QString name,QDir destination);
   // bool open(const QFileInfo& filepath);
    QDateTime createdAt()const;
    void setCreatedAt(QDateTime time);
    void addResults(VerificationResults* results);
    void setFile(QFileInfo path){_file = path;}
public slots:
    SpinCommands& commands();
    QString document();
    QString name()const;
    void setName(QString value);
    QString TrailDocument()const {return _trailDocument;}
    void setTrailDocument(QString trail_document) {_trailDocument = trail_document;}
    QFileInfo& filename(){return _file;}
    VerificationResults* VerificationReport()const;
};
#endif // VERIFICATIONRESULTSCONTAINER_H
