#ifndef VERIFICATIONQUEUE_H
#define VERIFICATIONQUEUE_H
#include <QObject>
#include <QDir>
#include "qspin/QObjectListBase.h"
#include "qspin/models/QSpinPlus.h"
#include "QsSpinRunner.h"
#include "QueuedVerification.h"
class VerificationQueue:  public QObjectListBase
{
    Q_OBJECT
public:
    enum Members{
        Name_role = Qt::UserRole,
        CreatedAt_role,
        StartedAt_role,
        statusLabelRole
    };
private:
    QList<QueuedVerification*> _queue;
    QSpinPlus* _project=nullptr;
public:
    using QObjectListBase::QObjectListBase;
   // explicit VerificationQueue(QObject* parent = nullptr);
    void setProject(QSpinPlus* project);
    void clear(){
        emit allQueuedItemsCanceled(QsSpinRunner::Canceled);
        beginResetModel();
        _queue.clear();
        endResetModel();
        emit allitemsCleared();
    }
signals:
    void allQueuedItemsCanceled(QsSpinRunner::Status);
    void allitemsCleared();
public slots:
    void append (QueuedVerification* item);
    void removeItem(int index);
    int position(QueuedVerification* item);
    QueuedVerification* get(int index);
private slots:
    ////////////////////////////////////////////////////////
    /// \brief itemDataChanged
    /// all members of QueuedObject with a setter for visual display
    /// must have its role added here otherwise changes wont be updated
    /// \param item
    ///
    void itemDataChanged(QueuedVerification *item){
        int idx = position(item);
        auto m_idx = index(idx,0);
        dataChanged(m_idx,m_idx,{ statusLabelRole,StartedAt_role });
    }
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    virtual QHash<int, QByteArray> roleNames() const override;



};

#endif // VERIFICATIONQUEUE_H
