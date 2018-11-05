#ifndef QSSPINRUNNER_H
#define QSSPINRUNNER_H

#include <QObject>
#include "qspin/Qs.h"
#include "qspin/viewModels/EventAggregator.h"
#include <QFuture>
#include <QProcess>
#include <QDateTime>
#include <QAbstractListModel>
#include <qspin/models/QsItemConfiguration.h>
#include "qspin/Qs.h"
class QsQueedItemConfiguration: public QObject{
    Q_OBJECT
    EventAggregator& msgService;
QDateTime _timeStamp;
QList<ItemConfiguration*> _spinConfigs;
QList<ItemConfiguration*> _compileConfig;
QList<ItemConfiguration*> _panConfig;
// entire textDocument
// result when done // formatted
// raw result report
// possible errors
// possible error trail

public:
    QsQueedItemConfiguration(QObject* parent=nullptr,EventAggregator& msgService = Qs::instance().msgService()):QObject (parent),msgService(msgService){}
    virtual void read(){}
    virtual void write(){}
    QStringList createSpinArguments()const{return QStringList();}
    QStringList createCompileArguments()const{return QStringList();}
    QStringList createPanArguments()const{return QStringList();}
    QString status(){return "some status";}
    QString name(){return "someName";}
    QString createdTimeStamp(){return "creationTime";}
    QString startedRunning(){return "some start time";}

};

class QsSpinQueueHandler : public QAbstractListModel
{
	Q_OBJECT
    // ################ begin properties #########################################################

    // ################ end properties #########################################################
    EventAggregator& msgService;
    bool _isStarted = false;
    QProcess spin;
QList<QsQueedItemConfiguration*> _itemsQueued;
    public:
    explicit QsSpinQueueHandler(QObject *parent = nullptr, EventAggregator& msgService= Qs::instance().msgService());
    virtual QVariant data(const QModelIndex& index,int role=Qt::DisplayRole)const override;
    virtual QHash<int,QByteArray> roleNames()const override;
virtual int rowCount(const QModelIndex& index = QModelIndex())const override;
    signals:
    public:
    void run();
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    bool isStarted();
    private slots:

    private:

};

#endif // QSSPINRUNNER_H
