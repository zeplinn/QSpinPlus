#ifndef QSITEMCONFIGURATION_H
#define QSITEMCONFIGURATION_H
#include "qspin/models/Arg.h"
#include <QObject>
#include <QDebug>
#define SET_QPROP(QPROP_OLDVALUE, QPROP_NEWVALUE,QPROP_SIGNALSEMITTED) if( QPROP_OLDVALUE != QPROP_NEWVALUE ){ QPROP_OLDVALUE = QPROP_NEWVALUE ; QPROP_SIGNALSEMITTED }
struct requirement{
    Arg::Type command;
    bool inverse;
    // compare
    requirement(Arg::Type command, bool inverse):command(command), inverse(inverse){}
};

class ItemConfiguration: public QObject{
    Q_OBJECT
    Q_PROPERTY(Arg::Type command READ command NOTIFY commandChanged)
    Arg::Type _command;
    Q_PROPERTY(QString name READ name CONSTANT)
    QString _name;
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    bool _checked =false;
    // requirements
    QList<requirement> _requirements;
public:// properties
    Arg::Type command()const;
    QString name()const;
    bool checked()const;
    void setChecked(bool value);
signals:// propertise
    void checkedChanged();
    void commandChanged();
    // Checked
    // enabled
    // compile to string
public:
    // used for making arguments chaining
    explicit ItemConfiguration(Arg::Type command,QObject* parent= nullptr);
    ItemConfiguration* onlyIf(Arg::Type command);
    ItemConfiguration* notIf(Arg::Type command);
protected:
    void setCommand(Arg::Type value);

};

class ItemValueConfiguration: public ItemConfiguration{
    Q_OBJECT
    Q_PROPERTY(int commandValue READ commandValue WRITE setCommandValue NOTIFY commandValueChanged)
    int _commandValue;
public://properties
    int commandValue()const;
    void setCommandValue(int value);
signals: // properties
    void commandValueChanged();

public:
    explicit ItemValueConfiguration(Arg::Type command,int value,QObject* parent = nullptr);
};

class ItemChoiceConfiguration:public ItemConfiguration{
    Q_OBJECT
    Q_PROPERTY(Arg::Type choice READ choice WRITE setChoice NOTIFY choiceChanged)
public: // properties
    Arg::Type choice()const;
    void setChoice(Arg::Type value);
signals:
    void choiceChanged();
public:
    explicit ItemChoiceConfiguration(Arg::Type defaultCommand=Arg::None,QObject* parent=nullptr);
};

#endif // QSITEMCONFIGURATION_H
