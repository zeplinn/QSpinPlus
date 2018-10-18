#ifndef QSSPINRUNNER_H
#define QSSPINRUNNER_H

#include <QObject>
#include "qspin/Qs.h"
#include "qspin/viewModels/EventAggregator.h"
#include <QFuture>
#include <QProcess>
class QsSpinRunner : public QObject
{
	Q_OBJECT
	EventAggregator* msgService;
	bool _isStarted = false;
	QProcess spin;

    public:
	explicit QsSpinRunner(QObject *parent = nullptr, EventAggregator *msgService= nullptr);

    signals:
    public:
	void run(){
	    spin.start("powershell",QStringList()<<"wsl"<<"spin");
	    spin.waitForFinished();

	    spin.readAllStandardOutput();
	}
	Q_INVOKABLE void start(){

	}
	Q_INVOKABLE void stop(){}
	bool isStarted(){
	    return _isStarted;
	}
    private slots:

    private:

};

#endif // QSSPINRUNNER_H
