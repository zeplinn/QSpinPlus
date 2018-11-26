#ifndef QSPINQUEUEHANLDER_H
#define QSPINQUEUEHANLDER_H


#ifdef Q_OS_WIN
#define QS_SPIN "wsl"
#define QS_GCC "wsl"
#define QS_PAN "wsl"
#else
#define QS_SPIN "spin"
#define QS_GCC "gcc"
#define QS_PAN "pan"
#endif
#include <QObject>
#include <QDateTime>
#include <QFuture>
#include <QFileInfo>
#include <QProcess>
//#include "qspin/Qs.h"
#include "qspin/QObjectBase.h"
#include "qspin/models/QSpinPlus.h"
//#include "qspin/viewModels/EventAggregator.h"
#include <QAbstractListModel>
#include "qspin/models/QsSpinRunner.h"
#include "qspin/models/VerificationQueue.h"
#include <qspin/models/QsItemConfiguration.h>
#include <qspin/models/VerificationResultContainer.h>
//#include "qspin/eventObjects/PrintToConsole.h"
//#include "qspin/eventObjects/AppendToVeriyQueue.h"
//#include "qspin/eventObjects/ProjectOpened.h"
//#include "qspin/eventObjects/ProjectClosed.h"
#include <QMetaObject>

class QsSpinQueueHandler : public QObjectBase
        , public ISubscriber<AppendToVeriyQueue>
        , public ISubscriber<ProjectOpened>
        , public ISubscriber<ProjectClosed>
{
    Q_OBJECT
    // --> ############## begin properties ##############

    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    bool _isRunning = false;

    bool isRunning()const;
    void setIsRunning(bool value);

    Q_PROPERTY(VerificationQueue* verifyQueue READ verifyQueue CONSTANT)
    VerificationQueue* _verifyQueue;

    VerificationQueue* verifyQueue()const;

    // <-- ############## end properties ##############
private:
    QPointer<QSpinPlus> _project;
public:
    explicit QsSpinQueueHandler(QObject* parent = nullptr,EventAggregator* msgService=nullptr);
    virtual void subscriber(const ProjectOpened& event)override;
    virtual void subscriber(const ProjectClosed& event)override;
signals:
    void spinRunnerStarted();
    void verificationSend();
    void isRunningChanged();
    void addingNewQueueItem(QFileInfo info , QDateTime createdAt);

public slots:
    void statusUpdated(/* status enum*/);
    void verificationRequsted();
    virtual void subscriber(const AppendToVeriyQueue& event) override;
private slots:
    void addNewQueueItem(QFileInfo info, QDateTime createdAt);


};









#endif // QSPINQUEUEHANLDER_H
