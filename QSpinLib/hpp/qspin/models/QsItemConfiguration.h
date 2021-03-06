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
/// Is the base class of all of all types of item configurations
/// an item configuration is represent a single command in spin


class ItemConfiguration: public QObjectBase, public IQXmlSerialization{
    Q_OBJECT
    Q_PROPERTY(Arg::Type command READ command NOTIFY commandChanged)
    Arg::Type _command;
    Q_PROPERTY(QString name READ name CONSTANT)
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
protected:
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
    void writeDefaultXmlAttributes(QXmlStreamWriter &xml);

};


///////////////////////////////////////////////////////////////////////////////////////
/// \brief The ItemValueConfiguration class
///
///

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
/// item configuration specficly created for the ltl command
///

class ItemLTLConfiguration
        :public ItemConfiguration
        ,public ISubscriber<ProjectSaved>
{
    Q_OBJECT
    Q_PROPERTY(QString document READ document WRITE setDocument NOTIFY documentChanged)
    QString _document="";
//    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
//    QString _name;

public: // properties
    QString document()const;
    void setDocument(QString value);
//    QString name()const;
//    void setName(QString value);

signals:
    void documentChanged();
    void nameChanged();
public:
    explicit ItemLTLConfiguration(Arg::Type commandId, QObject* parent =nullptr, EventAggregator* msgService=nullptr);
   // explicit ItemLTLConfiguration(Arg::Type defaultCommand=Arg::None,QObject* parent=nullptr);
    ItemLTLConfiguration(ItemLTLConfiguration* item);

    virtual void subscriber(const ProjectSaved& event) override;
    virtual void read(QXmlStreamReader& xml)override;
    virtual void write(QXmlStreamWriter& xml)override;
    virtual QString writeCommand()const override;
};

///////////////////////////////////////////////////////////
/// \brief The ItemAdvancedStringConfiguration class
///  This class is ment as a temporary fix until all spin commands commands are implemented as visual components
///

class ItemAdvancedStringConfiguration: public ItemConfiguration{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    QString _text;
public:
    explicit ItemAdvancedStringConfiguration(Arg::Type cmd,QObject* parent = nullptr, EventAggregator* msg = nullptr);
    ItemAdvancedStringConfiguration(ItemAdvancedStringConfiguration* item);
    QString text()const;
    void setText(QString value);
    virtual void read(QXmlStreamReader& xml)override;
    virtual void write(QXmlStreamWriter& xml)override;
    virtual QString writeCommand()const override;

signals:
    void textChanged();

};
#endif // QSITEMCONFIGURATION_H
