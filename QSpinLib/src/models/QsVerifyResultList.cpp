#include "qspin/models/QsVerifyResultList.h"

QsVerifyResultList::QsVerifyResultList(QObject *parent, EventAggregator *msg)
    : QObjectListBase(parent,msg)
    ,_lookup(QHash<qint64,QsVerifyResultListItem*>())
{}

void QsVerifyResultList::append(qint64 key, QsVerifyResultListItem *item){
    auto idx = _results.count();
    emit itemRemovedAt(idx);

    // used for easy cleanup when list is cleared

    connect(this,&QsVerifyResultList::itemsCleared
            ,item,&VerificationResultContainer::deleteLater);
    beginInsertRows(QModelIndex(),idx,idx);
    item->setParent(this);
    _lookup[key] = item;
    _results << item;
    endInsertRows();
}

void QsVerifyResultList::remove(qint64 key){
    if(_lookup.contains(key)){

        auto item = _lookup[key];
        int idx = _results.indexOf(item);

        beginRemoveRows(QModelIndex(),idx,idx);
        _lookup.remove(key);
        _results.removeOne(item);
        endRemoveRows();
        item->deleteLater();
    }
}

void QsVerifyResultList::clear(){
    beginResetModel();

    _lookup.clear();
    _results.clear();
    endResetModel();
    emit itemsCleared();
}

VerificationResultContainer *QsVerifyResultList::get(int idx){
    if(idx<0 || idx>=_results.count()) return  nullptr;
    return  _results[idx]->results();
}

int QsVerifyResultList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _results.count();
}

QVariant QsVerifyResultList::data(const QModelIndex &index, int role) const
{
    int idx = index.row();
    if(idx<0 || idx >= _results.count()) return QVariant();

    auto item = _results[idx];

    switch (role) {
    case Name_Role: return item->name();
    case CreatedAt_role: return item->createdAt();
    case Item_Role: return QVariant::fromValue(item->results());
//    case SpinCommands_role: return  cmds->spin.join(" ");
//    case GccCommands_role: return  cmds->gcc.join(" ");
//    case PanCommands_role: return cmds->pan.join(" ");
//    case Document_Role: return item->document();
//    case verifyReport_role: return QVariant::fromValue(item->VerificationReport());
    }

    return QVariant();
}

QHash<int, QByteArray> QsVerifyResultList::roleNames() const
{
    QHash<int,QByteArray> r;
    r[Name_Role]="name_role";
    r[CreatedAt_role]="createdAt_role";
    return r;

}

QsVerifyResultListItem::QsVerifyResultListItem(QFileInfo filepath, QObject *parent, EventAggregator *msg)
    : QObjectBase(parent,msg)
    ,_results(nullptr)
    ,_filepath(filepath)
{
    _name = qs().extractResultFileBaseName(filepath.fileName());
    bool isvalid =true;
    _createdAt = QDateTime(qs().extractEpochSinceFromFile(filepath.fileName(),&isvalid));
    if(!isvalid)
        toConsole(" queued file contains invalid time format",PrintToConsole::Error);
}

VerificationResultContainer *QsVerifyResultListItem::results(){
    if(_results== nullptr){
        _results = new VerificationResultContainer(this,msgService());
        _results->setFile(_filepath);
        qs().OpenXml(_results,_filepath.absoluteFilePath());
        if(!results()->createdAt().isValid())
            qDebug()<< "result container contains no creation date" << _results->createdAt();
    }
    return  _results;

}

QString QsVerifyResultListItem::name() const { return _name;}

QDateTime QsVerifyResultListItem::createdAt() const{ return _createdAt; }
