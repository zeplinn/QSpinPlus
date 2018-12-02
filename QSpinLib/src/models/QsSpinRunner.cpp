#include "qspin/models/QsSpinRunner.h"

QsSpinRunner::QsSpinRunner(QFileInfo queuedFile, ProjectInfo projectInfo, EventAggregator *msgService)
    :QObjectBase (nullptr,msgService)
    ,_spinProcess(new QProcess(this))
    ,_queuedFile(queuedFile)
    ,_projectInfo(projectInfo)
    ,_isTerminated(false)

    ,SPIN("spin")
    ,GCC("gcc")
    ,PAN("./pan") // not apart of system paths
{
    _spinProcess.setParent(this);
    _gccProcess.setParent(this);
    _panProcess.setParent(this);
    if(QSysInfo::productType() == "windows")
    {
        _isWindows = true;
        SPIN = GCC = PAN = "wsl";
    }
    else{
        _isWindows = false;
    }
}
/*!
 * \brief QsSpinRunner::runVerify
 * running this slot will start verifcation of running spin , gcc and the genearated pan file
 *
 */
void QsSpinRunner::runVerify(){
    emit statusUpdated(QsSpinRunner::Running);
    auto files =_projectInfo.binFolder.entryList(QDir::Files);
    QDir workDir = _projectInfo.binFolder;
    if(!workDir.exists())
        workDir.mkpath(workDir.absolutePath());
    auto folders = workDir.entryList({_queuedFile.baseName()},QDir::Dirs|QDir::NoDotAndDotDot);
    if(!folders.isEmpty()){
        workDir.mkdir(_queuedFile.baseName());
    }
    workDir.cd(_queuedFile.baseName());
    if(!workDir.isEmpty())
        qs().removeFiles(workDir);
    connectProceses(&_spinProcess);
    connectProceses(&_gccProcess);
    connectProceses(&_panProcess);

    //connect process verification chain
    connect(&_spinProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished)
            ,this,&QsSpinRunner::startGCC);
    connect(&_gccProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished)
            ,this,&QsSpinRunner::startPan);
    connect(&_panProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished)
            ,this,&QsSpinRunner::panFinished);

    // prepare queued verifcation file for execution
    _spinProcess.setWorkingDirectory(workDir.absolutePath());
    _gccProcess.setWorkingDirectory(_spinProcess.workingDirectory());
    _panProcess.setWorkingDirectory(_spinProcess.workingDirectory());

    _result = new VerificationResultContainer(this,msgService());
    _report = new VerificationResults(this,msgService());
    Qs::OpenXml(_result,_queuedFile.absoluteFilePath());
    _commands = _result->commands().CommandsToStringLists();
    if(!_commands.ltl.isNull()){
        Qs::writeTextFile(_commands.ltl->document()
                          ,workDir.absoluteFilePath( SpinCommands::tmpLtlFileName())
                          );
    }
    Qs::writeTextFile(_result->document()
                      ,workDir.absoluteFilePath(SpinCommands::tmpSpinFileName())
                      );
    startSpin();
}

void QsSpinRunner::stdOutUpdated(){
    auto str = _runningProcess->readAllStandardOutput();
    if(!_startCollectReport){
        _startCollectReport = _report->isFirstMatch(str);
        if(_startCollectReport)
            _report->constructRegexPatterns();
        _report->extractVerificationResults(str);
        QString assertions = _report->assertionViolations(str);
        if(!assertions.isEmpty())
            emit stdErrOutReady(assertions);
    }
    else {
        _report->extractVerificationResults(str);
    }
    emit stdOutReady(_spinProcess.readAllStandardOutput());

}

void QsSpinRunner::stdErrUpdated(){
    emit stdErrOutReady(_runningProcess->readAllStandardError());
}

/////////////////////////////////////////////////////////////////////////////////
///     start verification section
/////////////////////////////////////////////////////////////////////////////////


void QsSpinRunner::startSpin(){
    QStringList cmds;
    if(_isWindows){
        cmds << "spin";
    }
    emit stdOutReady(QString("start spin: %1").arg(cmds.join(" ")));
    cmds << _commands.spin;
    _runningProcess =& _spinProcess;
    _spinProcess.start(SPIN,cmds);
}


void QsSpinRunner::startGCC(int exitCode, QProcess::ExitStatus exitStatus){
    Q_UNUSED(exitCode)
    if(_isTerminated) return;
    if(exitStatus != QProcess::NormalExit){
        emit stdErrOutReady("spin process crashed");
        terminateProcess(Error);

    }
    else{
        QStringList cmds;
        if(_isWindows){
            cmds << "gcc";
        }
        cmds << _commands.gcc;
        emit stdOutReady(QString("start gcc: %1").arg(cmds.join(" ")));
        _runningProcess = &_gccProcess;
        _gccProcess.start(GCC,cmds);
    }

}

void QsSpinRunner::startPan(int exiCode, QProcess::ExitStatus exitStatus){
    Q_UNUSED(exiCode)
    if(_isTerminated) return;


    if(exitStatus != QProcess::NormalExit){
        emit stdErrOutReady("Gcc process crashed");
        terminateProcess(Error);
    }
    else{

        QStringList cmds;
        if(_isWindows){
            cmds << "./pan" ;
        }
        cmds << _commands.pan;
        emit stdOutReady(QString("start pan: %1").arg(cmds.join(" ")));
        _runningProcess = &_panProcess;

        _panProcess.start(PAN,cmds);
    }



}

void QsSpinRunner::panFinished(int exitCode, QProcess::ExitStatus exitStatus){
    Q_UNUSED(exitCode)
    if(_isTerminated) return;

    if(exitStatus != QProcess::NormalExit){
        statusUpdated(Error);
        emit stdErrOutReady("pan process crashed");
        return;
    }
    else{
        // process results and send them to the verify result handler

        _result->addResults(_report);

        auto path =_projectInfo.resultsFolder.absoluteFilePath(_queuedFile.fileName());
        QDir wDir(_panProcess.workingDirectory());
        auto trail = wDir.entryInfoList({"*.trail"},QDir::Files| QDir::NoDotAndDotDot);
        if(!trail.isEmpty()){

            _result->setTrailDocument(
                        qs().readTextFile(trail.takeFirst())
                        );
        }
        qs().WriteXml(_result,path);

        emit resultCreated(path,VerificationResultFileChanged::Created);

        terminateProcess(Finished);
    }
}

void QsSpinRunner::connectProceses(QProcess *from){

    _connections << QObject::connect(from,&QProcess::readyReadStandardOutput
                                     ,this,&QsSpinRunner::stdOutUpdated);
    _connections << QObject::connect(from,&QProcess::readyReadStandardError
                                     ,this,&QsSpinRunner::stdErrUpdated);
}

/////////////////////////////////////////////////////////////////////////////////
///     end verification section
/////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
/// \brief QsSpinRunner::terminateThread
/// terminate the process running safely
/// \param status
//////////////////////////////////////////////////////////////////////////////

void QsSpinRunner::terminateProcess(QsSpinRunner::Status status){
    //
    _isTerminated = true;
    if(_spinProcess.open()){
        _spinProcess.close();
    }
    if(_gccProcess.open()){
        _gccProcess.close();
    }
    if(_panProcess.open()){
        _panProcess.close();
    }
    emit statusUpdated(status);
    qs().removeFile(_queuedFile.absoluteFilePath());
    QDir d(_panProcess.workingDirectory());
    if(d.exists())
        _projectInfo.binFolder.rmdir(_queuedFile.baseName());
    emit finished();
}
