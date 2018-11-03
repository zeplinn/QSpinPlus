#ifndef QSSPINRUN_H
#define QSSPINRUN_H
#include <QObject>
#include <QProcess>
#include <QSharedPointer>
#include <QList>
#include "qspin/models/QsSpinConfig.h"
#include "qspin/models/QsVerificationResults.h"
#include <memory>
#include <QDir>
#include "qspin/models/Arg.h"
#include <QMutex>
class QsSpinRun{
	bool is_pan_build;
	QStringList spinOptions;
	QStringList gccOptions;
	QStringList panOptions;
	QDir buildDir;
	QSharedPointer<QProcess> process;
	bool isBuilding= false, isRunning=false;
	QMutex mutex;
public:
	//explicit QsSpinRun(QsSpinConfig& config, const QDir buildPath, const QString projectname);
	//QsSpinRun(const QsSpinConfig& copy,const QDir buildPath,const QString promelaFile);
	//void buildPan(const QString& path,QsSpinConfig& configs);
	void setArguments(QsSpinConfig &config, const QString& filename );
	void buildPan(){
		mutex.lock();
		if(isBuilding || isRunning){
			// emit some message
			mutex.unlock();
			return;
		}
		mutex.unlock();
		isBuilding = true;
		if(process->isOpen())
			process->close();


		// generate pan files
		process->start("powershell",spinOptions);

		start("spin",panOptions);

		process->waitForFinished(-1); // no timeout

		// emit some message report

		// if an error occured close and return

		process->close();

		// compile pan

		start("gcc",gccOptions);

		process->waitForFinished(-1); // no timeout

		// emit some message report

		// if an error occured close and return

		process->close();

		// pan is now ready to run
		mutex.lock();
		isBuilding = false;
		mutex.unlock();
	}
	void run(){
		mutex.lock();
		if(isBuilding || isRunning){
			// emit some message
			mutex.unlock();
			return;
		}
		isRunning=true;
		mutex.unlock();
		if(process->isOpen())
			process->close();

		start("./pan",panOptions);

		process->waitForFinished(-1);

		//emit some message;
		if(process->exitStatus()==QProcess::CrashExit){
		// if error close and return
			process->close();
			mutex.lock();
			isRunning=false;
			mutex.unlock();
			return;
		}

		process->close();
		isRunning = false;
	}
	verifyResult_ptr result()const{
		return verifyResult_ptr(new QsVerificationResults(""));
	}
private:
    void start(const QString& _unix,const QStringList& options){
#ifdef Q_OS_WIN
        Q_UNUSED(_unix)
		process->start("powershell",options);
#else
        process->start(_unix,options);
#endif
	}

	QStringList defaultGccArgs(QsSpinConfig &config);
	QStringList getLtlArguments(QsSpinConfig& config);
};

#endif // QSSPINRUN_H
