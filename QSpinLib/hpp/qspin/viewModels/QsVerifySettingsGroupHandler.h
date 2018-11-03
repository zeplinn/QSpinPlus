#ifndef QSVERIFYSETTINGSGROUPHANDLER_H
#define QSVERIFYSETTINGSGROUPHANDLER_H
#include <QObject>
#include "qspin/models/QsVerificationConfiguration.h"
class QsVerifySettingsGroupHandler: public QObject{
    Q_OBJECT
    Q_PROPERTY(VerificationConfiguration* item READ item NOTIFY referenceChanged)
    Q_PROPERTY(VerificationConfiguration* reference READ reference WRITE setReference NOTIFY referenceChanged)
    VerificationConfiguration* _item;
public:
    VerificationConfiguration* item()const;
    VerificationConfiguration* reference()const{return _item;}
    void setReference(VerificationConfiguration* value);
    explicit QsVerifySettingsGroupHandler(QObject* parent = nullptr);
signals:
    void referenceChanged();
};

#endif // QSVERIFYSETTINGSGROUPHANDLER_H
