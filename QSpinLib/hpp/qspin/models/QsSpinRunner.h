

#ifndef QSSPINRUNNER_H
#define QSSPINRUNNER_H

#ifdef QS_OS_UNIX
#define QS_SPIN "spin"
#define QS_GCC "gcc"
#define QS_PAN "pan"
#else
#define QS_SPIN "wsl"
#define QS_GCC "wsl"
#define QS_PAN "wsl"
#endif

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QProcess>
//#include "qspin/Qs.h"
#include "qspin/QObjectBase.h"
//#include "qspin/eventObjects/PrintToConsole.h"
#include "VerificationResultContainer.h"

class QsSpinRunner : public QObject
{
    Q_OBJECT
public:
    enum Status{
        Waiting,
        Running,
        Finished,
        FileNotFound,
        Error
    };
private:
    EventAggregator* _msgService;
    EventAggregator& msgService();
    void toConsole(QString msg);
    QProcess p;
    QFileInfo _file;
    QDir    _workingDir;
public:
    // qthread objects can not be moved to a thread if it have parent
    explicit QsSpinRunner(QFileInfo file, QDir workingDir);
public slots:
    void run();

private slots:
    void stdOutUpdated();
    void stdErrUpdated();

signals:
    void finished();
    void statusUpdated(Status variable);
};


#endif // QSSPINRUNNER_H
