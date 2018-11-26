#ifndef QSITEMCONFIGURATION_H
#define QSITEMCONFIGURATION_H
#include <QObject>
#include <QXmlStreamReader>
#include <QDebug>
#include <QRegularExpression>
#include <QDir>
//#include "qspin/Qs.h"
#include "qspin/QObjectBase.h"
class QSpinPlus;
#include "qspin/models/QSpinPlus.h"
#include "qspin/models/Arg.h"
#include "qspin/QpropertyHelper.h"
#include "qspin/models/IQsSerialization.h"


////////////////////////////////////////////////////////////////////
/// \brief The ItemConfiguration class
///////////////////////////////////////////////////////////////////


class ItemConfiguration: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    Q_PROPERTY(Arg::Type command READ command NOTIFY commandChanged)
    Arg::Type _command;
    Q_PROPERTY(QString name READ name CONSTANT)
    QString _name;
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    bool _checked, _enabled;
    // requirements
public:// properties
    Arg::Type command()const;
    QString name()const;
    bool checked()const;

    bool enabled()const;
    void setEnabled(bool value);
    Q_INVOKABLE virtual QString argument()const;
public slots:
    void setChecked(bool value);
private:

signals:// propertise
    void checkedChanged();
    void commandChanged();
    void enabledChanged();
private:
    Arg::Category _category;
public:
    // used for making arguments chaining
    explicit ItemConfiguration(Arg::Type commandId,QObject* parent= nullptr, EventAggregator* msgService=nullptr);
    ItemConfiguration(ItemConfiguration* item);
    Arg::Category category()const;
    virtual void read(QXmlStreamReader& xml) override;
    virtual void write(QXmlStreamWriter& xml)override;

    virtual QString writeCommand()const;
protected:
    void setCommand(Arg::Type value);
    void readXmlAttributes(QXmlStreamAttributes attr);

};


///////////////////////////////////////////////////////////////////////////////////////
/// \brief The ItemValueConfiguration class
//////////////////////////////////////////////////////////////////////////////////


class ItemValueConfiguration: public ItemConfiguration{
    Q_OBJECT
    Q_PROPERTY(int commandValue READ commandValue WRITE setCommandValue NOTIFY commandValueChanged)
    Q_PROPERTY(int maxValue READ maxValue CONSTANT)
    Q_PROPERTY(int minValue READ minValue CONSTANT)
    int _commandValue, _minValue,_maxValue;
public://properties
    int commandValue()const;
    void setCommandValue(int value);
    int maxValue()const;
    int minValue()const;

signals: // properties
    void commandValueChanged();

public:
    explicit ItemValueConfiguration(Arg::Type command,int value,int minValue,int maxValue
                                    ,QObject* parent = nullptr, EventAggregator* msgService = nullptr);
   ItemValueConfiguration(ItemValueConfiguration* item);
    Q_INVOKABLE virtual QString argument()const override;
    virtual void read(QXmlStreamReader& xml)override;
    virtual void write(QXmlStreamWriter& xml)override;

    virtual QString writeCommand()const override{
        return Arg::val(command(),commandValue());
    }
};


////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The ItemLTLConfiguration class
////////////////////////////////////////////////////////////////////////////////////////


class ItemLTLConfiguration
        :public ItemConfiguration
        ,public ISubscriber<ProjectOpened>
        ,public ISubscriber<ProjectSaved>
{
    Q_OBJECT
    Q_PROPERTY(QString document READ document WRITE setDocument NOTIFY documentChanged)
    QString _document;
public: // properties
    QString document()const{ return _document; }
    void setDocument(QString value){
        if(_document != value){
            _document = value;
            emit documentChanged();
        }
    }
signals:
    void documentChanged();
private:
    QDir _destinationDir;
public:
    using ItemConfiguration::ItemConfiguration;
    explicit ItemLTLConfiguration(Arg::Type commandId, QObject* parent =nullptr, EventAggregator* msgService=nullptr);
   // explicit ItemLTLConfiguration(Arg::Type defaultCommand=Arg::None,QObject* parent=nullptr);
    ItemLTLConfiguration(ItemLTLConfiguration* item);

    virtual void subscriber(const ProjectOpened& event) override;
    virtual void subscriber(const ProjectSaved& event) override;

    virtual QString writeCommand()const override;
};
/*#include "qspin/eventObjects/ProjectOpened.h"
#include "qspin/eventObjects/ProjectSaved.h*/
#endif // QSITEMCONFIGURATION_H
