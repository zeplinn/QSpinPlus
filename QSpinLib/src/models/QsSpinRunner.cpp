#include "qspin/models/QsSpinRunner.h"

EventAggregator &QsSpinRunner::msgService(){ return * _msgService;}

void QsSpinRunner::toConsole(QString msg){
    _msgService->publish(PrintToConsole(msg));
}

QsSpinRunner::QsSpinRunner(QFileInfo file,QDir workingDir)
    :QObject(nullptr)
    ,p(new QProcess(this))
    ,_file(file)
    ,_workingDir(workingDir)
{

    QObject::connect(&p,&QProcess::readyReadStandardOutput,this,&QsSpinRunner::stdOutUpdated);
    QObject::connect(&p,&QProcess::readyReadStandardError,this,&QsSpinRunner::stdErrUpdated);

}

void QsSpinRunner::run(){
    p.setWorkingDirectory(_workingDir.absolutePath());
    auto result = new VerificationResultContainer();
    if(!result->open(_file.absoluteFilePath())){
        emit statusUpdated(FileNotFound);
        return;
    }
    auto cmds = result->commands().writeCommands();
    // windows use the build in linux subsystem (wsl) to run spin
    //windows shell ->  wsl spin ....
    // linux shell  ->  spin ...
#ifdef Q_OS_WIN
    cmds.spin.prepend("spin");
    cmds.gcc.prepend("gcc");
    cmds.pan.prepend("./pan");
#endif
    p.start(QS_SPIN,cmds.spin);
    while (!p.waitForFinished()) {
        return;
    }
    p.start(QS_GCC,cmds.gcc);
    while (!p.waitForFinished()) {
        return;
    }


    p.start(QS_PAN,cmds.pan);
    while (!p.waitForFinished()) {
        return;
    }


    emit statusUpdated(Finished);
}

void QsSpinRunner::stdOutUpdated(){
    msgService().publish(PrintToConsole(p.readAllStandardOutput()));
}

void QsSpinRunner::stdErrUpdated(){
    msgService().publish(PrintToConsole(p.readAllStandardError()));
}
