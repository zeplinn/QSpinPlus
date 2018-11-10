#ifndef VERIFICATIONMENUHANDLER_H
#define VERIFICATIONMENUHANDLER_H

#include <QObject>
#include "qspin/models/QsVerificationResults.h"
#include <QQmlEngine>
#include <memory>
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/Qs.h"
#include "qspin/QmlImportNames.h"
#include <QAbstractListModel>
#include <qspin/models/QsVerificationConfiguration.h>
#include "qspin/models/Arg.h"
class QsVerifyHandler : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(VerificationConfiguration* currentConfiguration READ currentConfiguration NOTIFY currentConfigurationChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    int _currentIndex;
    VerificationConfiguration* _currentItem;
    //#################### result properties end #########################
    EventAggregator& msgService;
    QList<VerificationConfiguration*> _configurations;
public: //properties
    VerificationConfiguration* currentConfiguration()const;
    int currentIndex()const;
    Q_INVOKABLE void setCurrentIndex(int value);
signals: // properties
    void currentConfigurationChanged(VerificationConfiguration* currentConfig);
    void currentIndexChanged();
public:
    enum Role{
        SaftyRoleMode = Qt::UserRole,
        ProgressMode,
        AcceptanceMode,
        VerifyMode,
        Name
    };
    Q_ENUMS(ResultCode)
    explicit QsVerifyHandler(QObject *parent = nullptr);
    //Q_INVOKABLE qreal verifyResults(ResultCode code);

    virtual QVariant data(const QModelIndex& index,int role = Qt::DisplayRole)const override;
    virtual int rowCount(const QModelIndex& index = QModelIndex())const override;
    virtual QHash<int,QByteArray> roleNames()const override;

public slots:
    void addConfiguration(QString name);
    void removeConfiguration(VerificationConfiguration* item);
private slots:
    void verifyModeUpdated(Arg::Type mode);
};

#endif // VERIFICATIONMENUHANDLER_H
