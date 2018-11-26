#ifndef QUEUEDVERIFICATION_H
#define QUEUEDVERIFICATION_H
#include <QObject>
#include <QDateTime>
#include <QThread>
#include <QPointer>
#include <QFileInfo>
#include "qspin/QObjectBase.h"
#include "qspin/models/QsSpinRunner.h"

class QueuedVerification : public QObject
{
    Q_OBJECT

private:
    QString _baseName;
    QDateTime _createdAt;
    QsSpinRunner::Status _status;


    // end properties
private:
    QFileInfo _fileInfo;
    QThread t;
    QPointer<QsSpinRunner> _runner;

public:
    explicit QueuedVerification(QFileInfo info, QDateTime createdAt,QObject* parent= nullptr);
    virtual ~QueuedVerification();

    QString name()const;
    QDateTime createdAt()const;
    QString statusLabel()const;

    QsSpinRunner::Status status()const;
    void setStatus(QsSpinRunner::Status value);


public slots:
    void terminate();
    void start(QDir workingdir);
    void remove();
private slots:
    void verificationStarted();

    void verificationFinished();
    void statusUpdated(QsSpinRunner::Status update );
signals:
    void variablesChanged(QueuedVerification* item);
    void removedFromQueue(QueuedVerification* item);

};





#endif // QUEUEDVERIFICATION_H
