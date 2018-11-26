#ifndef VERIFICATIONQUEUE_H
#define VERIFICATIONQUEUE_H
#include <QObject>
#include <QDir>
#include "qspin/QObjectListBase.h"
#include "QsSpinRunner.h"
#include "QueuedVerification.h"
class VerificationQueue:  public QObjectListBase
{
    Q_OBJECT
public:
    enum Members{
        Name_role = Qt::UserRole,
        CreatedAt_role,
        statusLabelRole
    };
private:
    QList<QueuedVerification*> _queue;
    QDir _binDir;
public:
    using QObjectListBase::QObjectListBase;
   // explicit VerificationQueue(QObject* parent = nullptr);
    void setbuildDir(QDir dir);
public slots:
    void append (QueuedVerification* item);
    void removeItem(int index);
    QueuedVerification* get(int index);
private slots:
    void startNewVerification();
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    virtual QHash<int, QByteArray> roleNames() const override;



};

#endif // VERIFICATIONQUEUE_H
