#include "qspin/models/VerificationQueue.h"


void VerificationQueue::setProject(QSpinPlus *project){
    _project = project;
}

void VerificationQueue::append(QueuedVerification *item){
    beginInsertRows(QModelIndex(),_queue.count(),_queue.count());
    item->setParent(this);
    connect(item,&QueuedVerification::variablesChanged,this,&VerificationQueue::itemDataChanged);
    connect(this,&VerificationQueue::allQueuedItemsCanceled
            ,item,&QueuedVerification::cancelVerifcation);
    connect(this,&VerificationQueue::allitemsCleared
            ,item,&QueuedVerification::deleteLater);
    _queue << item;
    endInsertRows();
}

void VerificationQueue::removeItem(int index){
    if(index<0 || index>= _queue.count()) return;
    beginRemoveRows(QModelIndex(),index,index);
    auto item = _queue[index];
    _queue.removeAt(index);
    endRemoveRows();
    item->deleteLater();
}

int VerificationQueue::position(QueuedVerification *item){
    return  _queue.indexOf(item);
}

QueuedVerification *VerificationQueue::get(int index){
    return _queue[index];
}



int VerificationQueue::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _queue.count();
}

QVariant VerificationQueue::data(const QModelIndex &index, int role) const
{
    int idx = index.row();
    if(idx<0 || idx>=_queue.count())
        return  QVariant();

    auto item = _queue[idx];
    switch (role) {
    case Name_role: return item->name();   // not properly implemented yet
    case CreatedAt_role: return item->createdAt();
    case StartedAt_role: return item->startedAt();
    case statusLabelRole: return  item->statusLabel();
    }


    return QVariant();

}



QHash<int, QByteArray> VerificationQueue::roleNames() const
{
    QHash<int,QByteArray> r;
    r[Name_role] = "name_role";
    r[CreatedAt_role] ="createdAt_role";
    r[statusLabelRole]= "statusLabel_role";
    return r;
}
