#include "qspin/viewModels/QsSpinQueueHandler.h"
namespace{
enum{
    Name_role = Qt::UserRole,
    Created_role,
    Status_role,
    Started_Role
};
}
QsSpinQueueHandler::QsSpinQueueHandler(QObject *parent, EventAggregator &msgService) : QAbstractListModel (parent), msgService(msgService)
{
}

QVariant QsSpinQueueHandler::data(const QModelIndex &index, int role) const{
    int idx = index.row()+role;
    if(idx<0 || idx>= _itemsQueued.count()) return QVariant(QVariant::Invalid);

    auto item = _itemsQueued[idx];
    switch (role) {
    case Name_role: return item->name();
    case Created_role: return  item->createdTimeStamp();
    case Status_role: return  item->status();
    case Started_Role: return item->status();
    }

    return QVariant();
}

QHash<int, QByteArray> QsSpinQueueHandler::roleNames() const{
    QHash<int, QByteArray> r;
    r[Name_role] = "name_role";
    r[Created_role] = "created_role";
    r[Status_role] = "status_role";
    r[Started_Role] = "started_role";
    r[Status_role] = "status_role";
    return r;
}

int QsSpinQueueHandler::rowCount(const QModelIndex &index) const{
    Q_UNUSED(index)
    return _itemsQueued.count();
}

void QsSpinQueueHandler::run(){
    spin.start("powershell",QStringList()<<"wsl"<<"spin");
    spin.waitForFinished();

    spin.readAllStandardOutput();
}

void QsSpinQueueHandler::start(){

}

void QsSpinQueueHandler::stop(){}

bool QsSpinQueueHandler::isStarted(){
    return _isStarted;
}
