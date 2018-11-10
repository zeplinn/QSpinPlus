#ifndef QSITEMCONFIGURATION_H
#define QSITEMCONFIGURATION_H
#include "qspin/models/Arg.h"
#include <QObject>
#include <QDebug>
#include "qspin/QpropertyHelper.h"

class ItemConfiguration: public QObject{
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
    void setEnabled(bool value){
        _enabled = value;
        emit enabledChanged();
    }
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
    explicit ItemConfiguration(Arg::Type commandId,QObject* parent= nullptr);
    Arg::Category category()const{return  _category;}
protected:
    void setCommand(Arg::Type value);

};

class ItemValueConfiguration: public ItemConfiguration{
    Q_OBJECT
    Q_PROPERTY(int commandValue READ commandValue WRITE setCommandValue NOTIFY commandValueChanged)
    Q_PROPERTY(int maxValue READ maxValue CONSTANT)
    Q_PROPERTY(int minValue READ minValue CONSTANT)
    int _commandValue, _minValue,_maxValue;
public://properties
    int commandValue()const;
    void setCommandValue(int value);
    int maxValue()const{ return _maxValue;}
    int minValue()const{ return _minValue;}

signals: // properties
    void commandValueChanged();

public:
    explicit ItemValueConfiguration(Arg::Type command,int value,int minValue,int maxValue,QObject* parent = nullptr);
    Q_INVOKABLE virtual QString argument()const override;
};

class ItemTextFileConfiguration:public ItemConfiguration{
    Q_OBJECT
    Q_PROPERTY(Arg::Type choice READ choice WRITE setChoice NOTIFY choiceChanged)
public: // properties
    Arg::Type choice()const;
    void setChoice(Arg::Type value);
signals:
    void choiceChanged();
public:
    explicit ItemTextFileConfiguration(Arg::Type defaultCommand=Arg::None,QObject* parent=nullptr);
};
#endif // QSITEMCONFIGURATION_H
