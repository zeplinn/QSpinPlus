#ifndef VERIFICATIONMENUHANDLER_H
#define VERIFICATIONMENUHANDLER_H


#include <QObject>
#include <QQmlEngine>
#include <memory>
#include <QProcess>
#include <QPointer>

#include "qspin/QObjectListBase.h"
#include "qspin/models/QSpinPlus.h"
#include "qspin/models/QsVerificationResults.h"
#include "qspin/QmlImportNames.h"
#include <QAbstractListModel>
#include <qspin/models/QsVerificationConfiguration.h>
#include "qspin/models/Arg.h"

#include "qspin/models/VerificationResultContainer.h"
class QsVerifyHandler : public QObjectListBase
        , public ISubscriber<ProjectSaved>
        , public ISubscriber<ProjectOpened>
        , public ISubscriber<ProjectClosed>
{
    Q_OBJECT
public:
    enum Role{
        SaftyRoleMode = Qt::UserRole,
        ProgressMode,
        AcceptanceMode,
        VerifyMode,
        Name
    };
    Q_ENUMS(ResultCode)
private:
    Q_PROPERTY(VerificationConfiguration* currentConfiguration READ currentConfiguration NOTIFY currentConfigurationChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    int _currentIndex;
    VerificationConfiguration* _currentItem;
    Q_PROPERTY(bool isProjectOpen READ isProjectOpen NOTIFY isProjectOpenChanged)
    bool _isProjectOpen=false;
    //#################### result properties end #########################

    QPointer<QSpinPlus> _project;
public: //properties
    VerificationConfiguration* currentConfiguration()const;
    int currentIndex()const;
    Q_INVOKABLE void setCurrentIndex(int value);
    bool isProjectOpen()const{ return _isProjectOpen;}
signals: // properties
    void currentConfigurationChanged(VerificationConfiguration* currentConfig);
    void currentIndexChanged();
    void isProjectOpenChanged();
protected:

    explicit QsVerifyHandler(QObject *parent = nullptr,EventAggregator* msgService=nullptr);
    //Q_INVOKABLE qreal verifyResults(ResultCode code);

    virtual QVariant data(const QModelIndex& index,int role = Qt::DisplayRole)const override;
    virtual int rowCount(const QModelIndex& index = QModelIndex())const override;
    virtual QHash<int,QByteArray> roleNames()const override;
    void setIsProjectOpen(bool value){
        _isProjectOpen = value;
        emit isProjectOpenChanged();
    }
    virtual void subscriber(const ProjectOpened& event)override{
        beginResetModel();
        _project = event.project();
        auto c = _project->configurations();
        endResetModel();
        if(c->count()>0){
            setCurrentIndex(0);
        }
        setIsProjectOpen(true);
    }
    virtual void subscriber(const ProjectSaved& event)override{
        Q_UNUSED(event)
    }
    virtual void subscriber(const ProjectClosed& event)override{
        Q_UNUSED(event)
        setIsProjectOpen(false);
    }
public slots:
    void addConfiguration(QString name);
    void removeConfiguration(VerificationConfiguration* item);
    void queueVerification(VerificationConfiguration* item);
private slots:
    void verifyModeUpdated(Arg::Type mode);

    void checkSyntax(){
        QProcess p;
        QDir workDir = _project->projectDir();
        QString tmpDir ="sc_check_"+currentConfiguration()->name();
        workDir.mkdir(tmpDir);
        workDir.cd(tmpDir);
        p.setWorkingDirectory(workDir.absolutePath());
        auto vResult = new VerificationResultContainer();
        auto spinCommands = new SpinCommands();
        auto vc = currentConfiguration();

//        for ( auto ic : _project->configurations())
//            set
//        spinCommands->append()

    }
};

#endif // VERIFICATIONMENUHANDLER_H
