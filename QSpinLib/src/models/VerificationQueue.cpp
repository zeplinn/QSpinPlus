#include "qspin/models/VerificationQueue.h"


void VerificationQueue::setbuildDir(QDir dir){
    _binDir = dir;
}

void VerificationQueue::append(QueuedVerification *item){
    beginInsertRows(QModelIndex(),_queue.count(),_queue.count());
    item->setParent(this);
    //QObject::connect(item,&QueuedVerification::removedFromQueue,this,&VerificationQueue::removeItem);
    _queue << item;
    endInsertRows();
    startNewVerification();
}

void VerificationQueue::removeItem(int index){
    if(index<0 || index>= _queue.count()) return;
    beginRemoveRows(QModelIndex(),index,index);
    auto item = _queue[index];
    _queue.removeAt(index);
    endRemoveRows();
    item->deleteLater();
}

QueuedVerification *VerificationQueue::get(int index){
    return _queue[index];
}

void VerificationQueue::startNewVerification(){
    _queue.takeFirst();
    if(_queue.count()>0 && _queue[0]->status()==QsSpinRunner::Waiting){
        _queue[0]->start(_binDir);
    }
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
