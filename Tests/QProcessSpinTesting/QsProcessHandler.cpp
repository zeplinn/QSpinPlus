#include "QsProcessHandler.h"

QsProcessHandler::QsProcessHandler(QObject *parent) : QAbstractListModel(parent)
{

}

QVariant QsProcessHandler::data(const QModelIndex &index, int role) const {
    Q_UNUSED(role)
    int idx = index.row();
    if(idx <0 || idx >= _messages.count())
        return QVariant(QVariant::Invalid);

    if( role == msg_role) return _messages[idx];
    return QVariant(QVariant::Invalid);
}

int QsProcessHandler::rowCount(const QModelIndex &parent) const{Q_UNUSED(parent); return _messages.count();}

QHash<int, QByteArray> QsProcessHandler::roleNames() const{
    QHash<int,QByteArray> r;
    r[msg_role]="msg_role";
    return r;
}

void QsProcessHandler::addMsg(const QString &msg){
    beginInsertRows(QModelIndex(),_messages.count(),_messages.count());
    _messages << msg;
    endInsertRows();
}

void QsProcessHandler::addMsgs(const QList<QByteArray> &msg){
    beginInsertRows(QModelIndex(),_messages.count(),_messages.count()+ msg.count()-1);
    for(int i=0; i<msg.count();i++){
        _messages << msg[i];
    }
    endInsertRows();
}

void QsProcessHandler::testMsgSystem(){
    for(int i=0;i<10; i++){
        addMsg(QString("test %1").arg(i));
    }
}

void QsProcessHandler::runSpin(){
    addMsg("run spin verify");
    QProcess p;

    QDir d(QDir::current().path()+"/bin");

    if(!d.exists())
        d.mkdir(d.path());
    p.setWorkingDirectory(d.path());
    currentDir();
    QString promFile = project->promelaFile().fileName();
    QFile::copy(promFile,"bin/"+promFile);
    addMsg("promelaFile: "+promFile);
    p.start("powershell",QStringList()<<"wsl"<< "spin"<<"-a" << promFile);
    p.waitForFinished();
    addMsgs(p.readAllStandardError().split('\n'));
    addMsgs(p.readAllStandardOutput().split('\n'));

    if(p.isOpen())
        p.close();

    p.start("powershell",QStringList()<<"wsl"<<"gcc"<<"pan.c"<<"-DSafty"<<"-DNFAIR=2"<<"-o"<<"pan");
    p.waitForFinished();
    addMsgs(p.readAllStandardError().split('\n'));
    addMsgs(p.readAllStandardOutput().split('\n'));
}

void QsProcessHandler::runPan(){
    addMsg("run pan");
    QProcess p;
    QDir d(QDir::currentPath()+"/bin");
    if( !d.exists()){
        addMsg("error: running pan cant find target dir: "+d.path());
        return;
    }
    p.setWorkingDirectory(d.path());
    p.start("powershell",QStringList()<<"wsl"<<"./pan");
    p.waitForFinished();
    addMsgs(p.readAllStandardError().split('\n'));
    addMsgs(p.readAllStandardOutput().split('\n'));
}

void QsProcessHandler::openProject(QUrl file){
    if(project)
        delete project;
    try {
        addMsg(file.toLocalFile());
        project = new QsProject();
        QsProject::open(*project,file.toLocalFile());

        addMsg(QDir::currentPath());
    }
    catch(const QString& e){
        addMsg(e);
    }
    catch (const std::error_code& e) {
        addMsg(QString(e.message().c_str()));
    }
}
