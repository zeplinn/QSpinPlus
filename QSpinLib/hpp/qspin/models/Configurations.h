#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H
#include <QObject>
#include <QList>
#include <QHash>
#include <QAbstractListModel>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "qspin/QObjectBase.h"
#include "qspin/models/IQsSerialization.h"
class VerificationConfiguration;
class Configurations: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    // --> ########### begin properties ####################
    Q_PROPERTY(VerificationConfiguration* currentItem READ currentItem NOTIFY currentItemChanged)
    VerificationConfiguration* _currentItem;
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    int _currentIndex=-1;
public:
    VerificationConfiguration* currentItem()const;
    int currentIndex()const;
    void setCurrentIndex(int value);
signals:
    void currentItemChanged();
    void currentIndexChanged();
    // <-- ########### end properties ####################
private:
    QList<VerificationConfiguration*> _configurations;

public:
    enum Role{
        SaftyRoleMode = Qt::UserRole,
        ProgressMode,
        AcceptanceMode,
        VerifyMode,
        Name
    };
    using QObjectBase::QObjectBase;
    //explicit Configurations(QObject* parent =nullptr);
    int count()const;
    VerificationConfiguration* get(int index);



    // QAbstractList implemented
public slots:
    void append(VerificationConfiguration* item);
    void removeAt(int index);
    int itemAt(VerificationConfiguration* item)const;
private slots:
public:

    // IQXMlSerilization implemented
    virtual void read(QXmlStreamReader& xml) override;
    virtual void write(QXmlStreamWriter& xml)override;


};
#include "qspin/models/QsVerificationConfiguration.h"


#endif // CONFIGURATIONS_H
