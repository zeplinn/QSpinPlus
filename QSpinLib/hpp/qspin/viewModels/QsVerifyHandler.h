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
    QPointer<VerificationConfiguration> _currentItem;
    Q_PROPERTY(bool isProjectOpen READ isProjectOpen NOTIFY isProjectOpenChanged)
    bool _isProjectOpen=false;
    //#################### result properties end #########################

    QPointer<QSpinPlus> _project;
public: //properties
    VerificationConfiguration* currentConfiguration()const;
    int currentIndex()const;
    Q_INVOKABLE void setCurrentIndex(int value);
    bool isProjectOpen()const;
signals: // properties
    void currentConfigurationChanged(VerificationConfiguration* currentConfig);
    void currentIndexChanged();
    void isProjectOpenChanged();
public:

    explicit QsVerifyHandler(QObject *parent = nullptr,EventAggregator* msgService=nullptr);
    //Q_INVOKABLE qreal verifyResults(ResultCode code);

    virtual QVariant data(const QModelIndex& index,int role = Qt::DisplayRole)const override;
    virtual int rowCount(const QModelIndex& index = QModelIndex())const override;
    virtual QHash<int,QByteArray> roleNames()const override;
    void setIsProjectOpen(bool value);
    virtual void subscriber(const ProjectOpened& event)override;
    virtual void subscriber(const ProjectSaved& event)override;
    virtual void subscriber(const ProjectClosed& event)override;
public slots:
    void addConfiguration(QString name);
    void removeConfiguration(VerificationConfiguration* item);
    void queueVerification(VerificationConfiguration* item);

private slots:
    void verifyModeUpdated(Arg::Type mode);

    void checkSyntax();
};

#endif // VERIFICATIONMENUHANDLER_H
