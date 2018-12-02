#ifndef QSVERIFYRESULTLIST_H
#define QSVERIFYRESULTLIST_H
#include <QObject>
#include <QDateTime>
#include "qspin/QObjectBase.h"
#include "qspin/QObjectListBase.h"
class VerificationResultContainer;
#include "qspin/models/VerificationResultContainer.h"

class QsVerifyResultListItem: public QObjectBase
{
    Q_OBJECT
    VerificationResultContainer* _results;
    QString _name;
    QDateTime _createdAt;
    QFileInfo _filepath;
public:
    QsVerifyResultListItem(QFileInfo filepath,QObject* parent=nullptr, EventAggregator* msg =nullptr);
    VerificationResultContainer* results();
    QString name()const;
    QDateTime createdAt()const;
};

class QsVerifyResultList: public QObjectListBase
{
    Q_OBJECT

    enum Roles{
        Name_Role = Qt::UserRole,
        CreatedAt_role,
        Item_Role,
        Document_Role,
        verifyReport_role,
        SpinCommands_role,
        GccCommands_role,
        PanCommands_role
    };

    QList<QsVerifyResultListItem*> _results;
    QHash<qint64,QsVerifyResultListItem*> _lookup;

public:
    QsVerifyResultList(QObject* parent =nullptr ,EventAggregator* msg = nullptr);

    void append(qint64 key, QsVerifyResultListItem *item);
    void remove(qint64 key);
    void clear();
    VerificationResultContainer* get(int idx);
signals:
    void itemRemovedAt(int index);
    void itemsCleared();
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

};
#endif // QSVERIFYRESULTLIST_H
