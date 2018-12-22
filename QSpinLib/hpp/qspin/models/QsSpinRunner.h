

#ifndef QSSPINRUNNER_H
#define QSSPINRUNNER_H


#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QSysInfo>
#include <QDir>
#include <QThread>
#include <QProcess>
#include <QMetaObject>
#include <functional>
#include <QRegularExpression>
#include "qspin/QObjectBase.h"
#include "VerificationResultContainer.h"
#include "QsItemConfiguration.h"

class QsSpinRunner : public QObjectBase
{
    Q_OBJECT
public:
    enum Status{
        Waiting,
        Starting,
        Running,
        Finished,
        FileNotFound,
        Error,
        Canceled
    };
    Q_ENUMS(Status)
private:
    QProcess _spinProcess;
    QProcess _gccProcess;
    QProcess _panProcess;
    QProcess* _runningProcess;
    QFileInfo _queuedFile;
    ProjectInfo _projectInfo;
    compiledCommands _commands;
    VerificationResultContainer* _result;
    bool _isTerminated;
    QList<QMetaObject::Connection>_connections;
    QString SPIN,GCC,PAN;
    bool _isWindows= false, _startCollectReport = false;
    QPointer<VerificationResults> _report;
    QDir workDir;

public:
    // qthread objects can not be moved to a thread if it have parent
    explicit QsSpinRunner(QFileInfo queuedFile, ProjectInfo projectInfo, EventAggregator* msgService);
    ~QsSpinRunner(){
        for(auto c : _connections){
            disconnect(c);
        }
    }
    // returns an error string if any errors
    // else it returns an empty string
    static QString checkSyntax(ProjectInfo info,QString path,compiledCommands commands){
        QProcess p;
        QDir d = info.project.absoluteDir();
        auto folder = QString::number( QDateTime::currentMSecsSinceEpoch() );
        d.mkdir(folder);
        d.cd(folder);

        p.setWorkingDirectory(d.absolutePath());
        QFileInfo fi(path);
        QFile::copy(path,d.absoluteFilePath(fi.fileName()));

        QString app =QSysInfo::productType();
        QStringList cmds;
        if(app == "windows"){
            app = "wsl";
            cmds << "spin";
        }
        else{
            app= "spin";
        }
        cmds << "-a" << commands.spin << "-o7" << fi.fileName();
        Qs::instance().msgService()
                ->publish(PrintToConsole(
                              QString("check syntax using:")
                              .arg(cmds.join(" ")
                                   )));
        p.start(app,cmds);
        p.waitForFinished();
        QString err = p.readAllStandardError();
        if( !err.isEmpty())
            err.prepend("Spin commands used" + cmds.join( "")+"\n");
        p.close();
        d.removeRecursively();
        return  err;
    }
public slots:
    void runVerify();
    void terminateProcess(QsSpinRunner::Status status);
private slots:
    void stdOutUpdated();
    void stdErrUpdated();

    void startSpin();
    void startGCC(int exitCode,QProcess::ExitStatus exitStatus);
    void startPan(int exiCode,QProcess::ExitStatus exitStatus);
    void panFinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void finished();
    void statusUpdated(QsSpinRunner::Status variable);
    void stdOutReady(QString text);
    void stdErrOutReady(QString text);
    void resultCreated(QFileInfo resultFile,VerificationResultFile::Status status);
private:
    void connectProceses(QProcess* from);

};

#endif // QSSPINRUNNER_H
