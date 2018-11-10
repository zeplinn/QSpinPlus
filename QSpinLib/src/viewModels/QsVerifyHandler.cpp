#include "qspin/viewModels/QsVerifyHandler.h"



VerificationConfiguration *QsVerifyHandler::currentConfiguration() const{ return _currentItem;}

int QsVerifyHandler::currentIndex() const{return _currentIndex;}

void QsVerifyHandler::setCurrentIndex(int value){
    //if( _currentIndex != value){

    _currentIndex = value;
    emit currentIndexChanged();
    if(_currentIndex < 0 || _currentIndex>= _configurations.count() ) return;
    _currentItem = _configurations[_currentIndex];
    emit currentConfigurationChanged(_currentItem);
    //}
}

QsVerifyHandler::QsVerifyHandler(QObject *parent) : QAbstractListModel(parent)
  ,_currentIndex(0)
  ,_currentItem(nullptr)
  ,msgService(Qs::instance().msgService())
{
    addConfiguration("demo 1");
    addConfiguration("demo 2");
    addConfiguration("demo 3");
}

QVariant QsVerifyHandler::data(const QModelIndex &index, int role) const{
    int idx = index.row();
    if(idx<0 || idx >= _configurations.count()) return  QVariant();

    auto config = _configurations[idx];
    switch (role) {
    case SaftyRoleMode: return QVariant::fromValue(config->safetyMode());
    case ProgressMode: return QVariant::fromValue(config->progressMode());
    case AcceptanceMode: return QVariant::fromValue(config->acceptanceMode());
    case VerifyMode:
        return config->currentMode();
    case Name: return config->name();
    }
    return QVariant();
}

int QsVerifyHandler::rowCount(const QModelIndex &index) const{
    Q_UNUSED(index)
    return _configurations.count();
}

QHash<int, QByteArray> QsVerifyHandler::roleNames() const{
    QHash<int,QByteArray> r;
    r[SaftyRoleMode]="saftyMode_role";
    r[ProgressMode]="progresMode_role";
    r[AcceptanceMode]="acceptanceMode_role";
    r[VerifyMode] ="verifyMode_role";
    r[Name]="name_role";
    return r;
}

void QsVerifyHandler::addConfiguration(QString name){
    auto c = new VerificationConfiguration(this);
    c->setName(name);
    QObject::connect(c,&VerificationConfiguration::verifyModeChanged,this,&QsVerifyHandler::verifyModeUpdated);
    beginInsertRows(QModelIndex(),_configurations.count(),_configurations.count());
    _configurations<< c;
    endInsertRows();
}

void QsVerifyHandler::removeConfiguration(VerificationConfiguration *item){
    if(_configurations.count()==1) return;
    int idx = currentIndex()-1 <0 ? 0 : currentIndex()-1;
    beginRemoveRows(QModelIndex(),currentIndex(),currentIndex());
    _configurations.removeAt(currentIndex());
    setCurrentIndex(idx);
    endRemoveRows();
    item->deleteLater();
}

void QsVerifyHandler::verifyModeUpdated(Arg::Type mode){
    dataChanged(index(currentIndex()),index(currentIndex()),{VerifyMode});
}


