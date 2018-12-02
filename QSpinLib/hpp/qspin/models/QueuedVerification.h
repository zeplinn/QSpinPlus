#ifndef QUEUEDVERIFICATION_H
#define QUEUEDVERIFICATION_H
#include <QObject>
#include <QDateTime>
#include <QThread>
#include <QPointer>
#include <QFileInfo>
#include "qspin/QObjectBase.h"
#include "qspin/models/QsSpinRunner.h"

class QueuedVerification : public QObjectBase
{
    Q_OBJECT

private:
    QString _baseName;
    QDateTime _createdAt;
    QDateTime _startedAt;
    QsSpinRunner::Status _status;


    // end properties
private:
    QFileInfo _fileInfo;

public:
    explicit QueuedVerification(QFileInfo info, QDateTime createdAt, QObject* parent= nullptr, EventAggregator *msgService=nullptr);
    virtual ~QueuedVerification();

    QString name()const;
    QDateTime createdAt()const;
    QDateTime startedAt();

    QString statusLabel()const;
    QFileInfo fileInfo();
    QsSpinRunner::Status status()const;
public slots:
    void setStatus(QsSpinRunner::Status value);
    void setStartedAt(QDateTime startedAt);
    void cancelVerifcation();
signals:
    void variablesChanged(QueuedVerification* item);
    void verificationCanceled(QsSpinRunner::Status);

};





#endif // QUEUEDVERIFICATION_H
