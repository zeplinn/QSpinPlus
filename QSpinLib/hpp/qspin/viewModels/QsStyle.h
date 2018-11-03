#ifndef QSPINSTYLE_H
#define QSPINSTYLE_H

#include <QObject>
#include <QtQml>
#include <QColor>
#include <QQmlEngine>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "qspin/QmlImportNames.h"
#include "qspin/models/IQsSerialization.h"
#include <QSharedPointer>
#include "qspin/viewModels/ColorScheme.h"


#include "qspin/Qs.h"
// color scheme serialization identifiers
//struct propertyIds{
//    // group members
//    static constexpr const char  button[]           = "button";
//    static constexpr const char  spinbox[]          = "spinbox";
//    static constexpr const char  combobox[]         = "combobox";
//    static constexpr const char  general[]          = "general";
//    static constexpr const char  editor[]          = "editor";

//    //value members
//    static constexpr const char  foreground[]       = "foreground";
//    static constexpr const char  background[]       = "background";
//    static constexpr const char  pressed[]          = "pressed";
//    static constexpr const char  border[]           = "border";
//    static constexpr const char  input[]            = "input";
//    static constexpr const char  spinner[]          = "spinner";
//    static constexpr const char  icon[]             = "icon";
//    static constexpr const char  hovered[]          = "hovered";
//    static constexpr const char  menubarGradiant0[] = "menubarGradiant0";
//    static constexpr const char  menubarGradiant1[] = "menubarGradiant1";
//    static constexpr const char  font[]             = "font";
//    static constexpr const char  class_[]           = "class";
//    static constexpr const char  keyword[]          = "keyword";
//    static constexpr const char  comment[]          = "comment";
//    static constexpr const char  type[]             = "type";
//    static constexpr const char  operator_[]        = "operator";
//    static constexpr const char  number[]           = "number";
//    static constexpr const char  string_[]          = "string";
//};
//static constexpr propertyIds propIds;

//struct colorProperty{
//    QColor color;
//    QString id;
//};
//// style types

//class BaseStyle : public QObject, public IQJsonSerialization
//{
//    Q_OBJECT
//    Q_INTERFACES(IQJsonSerialization)
//    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground NOTIFY foregroundChanged)
//    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
//    colorProperty _foreground, _background;
//public: // properties
//    QColor foreground()const;
//    void setForeground(QColor value);
//    QColor background()const;
//    void setBackground(QColor value);
//signals:
//    void foregroundChanged();
//    void backgroundChanged();
//public:
//    explicit BaseStyle(QObject *parent = nullptr);
//    virtual void read(const QJsonObject& obj) override;
//    virtual void write(QJsonObject& obj)const override;
//    virtual bool isValidJsonObject(QJsonObject& obj)override;
//protected:
//    QColor jsonToColor(const char id[],const QJsonObject& obj);
//    bool isValidRGBArray( QJsonObject& obj,const char id[]);
//};

//class GeneralStyle : public BaseStyle{
//Q_OBJECT
//    Q_PROPERTY(QColor hovered READ hovered NOTIFY hoveredChanged)
//    Q_PROPERTY(QColor border READ border NOTIFY borderChanged)
//    Q_PROPERTY(QColor menubarGradiant0 READ menubarGradiant0 NOTIFY menubarGradiant0Changed)
//    Q_PROPERTY(QColor menubarGradiant1 READ menubarGradiant1 NOTIFY menubarGradiant1Changed)
//    colorProperty _hovered, _border, _menubarGradiant0, _menubarGradiant1;
//public: // properties
//    QColor hovered()const;
////    void setHovered(QColor value){
////        if(_hovered.color != value){
////            _hovered = value;
////            emit hoveredChanged();
////        }
////    }
//    QColor border()const;
////    void setborder(QColor value){
////        if(_border.color != value){
////            _border = value;
////            emit borderChanged();
////        }
////    }
//    QColor menubarGradiant0()const;
////    void setMenubarUp(QColor value){
////        if(_menubarUp.color != value){
////            _menubarUp.color = value;
////            emit menubarUpChanged();
////        }
////    }
//    QColor menubarGradiant1()const;
////    void setHovered(QColor value){
////        if(_hovered.color != value){
////            _hovered = value;
////            emit hoveredChanged();
////        }
////    }

//signals: // properties
//    void hoveredChanged();
//    void borderChanged();
//    void menubarGradiant0Changed();
//    void menubarGradiant1Changed();
//public:
//    explicit GeneralStyle(QObject* parent = nullptr);
//    virtual void read(const QJsonObject& obj) override;
//    virtual void write(QJsonObject& obj)const override;
//    virtual bool isValidJsonObject(QJsonObject& obj) override;
//};

//class ButtonStyle: public BaseStyle{
//    Q_OBJECT
//    Q_INTERFACES(IQJsonSerialization)
//    Q_PROPERTY(QColor pressed READ pressed NOTIFY pressedChanged)
//    Q_PROPERTY(QColor border READ border  NOTIFY borderChanged)
//    colorProperty _pressed, _border;
//public: // properties
//    QColor pressed()const;
//    void setPressed(QColor value);
//    QColor border()const;
//    void setBorder(QColor value);
//signals:
//    void pressedChanged();
//    void borderChanged();
//public:
//    explicit ButtonStyle(QObject* parent = nullptr);
//    virtual void read(const QJsonObject& obj)override;
//    virtual void write(QJsonObject& obj)const override;
//    virtual bool isValidJsonObject(QJsonObject& obj) override;
//private:// member functions

//};

//class SpinBoxStyle: public ButtonStyle{
//    Q_OBJECT
//    Q_PROPERTY(QColor input READ input NOTIFY inputChanged)
//    Q_PROPERTY(QColor spinner READ spinner NOTIFY spinnerChanged)
//    QColor _input, _spinner;
//public:// properties
//    QColor input()const{ return _input;}
//    QColor spinner()const{return _spinner;}
//signals: // properties
//    void inputChanged();
//    void spinnerChanged();
//public:
//    explicit SpinBoxStyle(QObject* parent = nullptr);
//    virtual bool isValidJsonObject(QJsonObject& obj)override;
//};
//class ComboBoxStyle: public ButtonStyle{
//    Q_OBJECT
//    Q_PROPERTY(QColor icon READ icon NOTIFY iconChanged)
//    QColor _icon;
//public: // properties
//    QColor icon()const{return _icon;}
//signals: // properties;
//    void iconChanged();
//public:
//    explicit ComboBoxStyle(QObject* parent= nullptr);
//    virtual bool isValidJsonObject(QJsonObject& obj)override;

//};

//class ColorScheme: public QObject{
//    Q_OBJECT
//    ButtonStyle* _btnStyle;
//    ComboBoxStyle* _comboStyle;
//    SpinBoxStyle* _spinboxStyle;
//    GeneralStyle* _genereralStyle;

//public:
//    explicit ColorScheme(QObject* parent=nullptr);
//    void open(const QString file);
//    void save(const QString filename);
//};

// QsStyle object
class QsStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ButtonStyle* button READ button CONSTANT)
    Q_PROPERTY(GeneralStyle* general READ general CONSTANT)
    Q_PROPERTY(SpinBoxStyle* spinbox READ spinbox CONSTANT)
    Q_PROPERTY(ComboBoxStyle* combobox READ combobox CONSTANT)
    ColorScheme& _colorScheme;
public:
public: // properties
  ButtonStyle* button()const;
  SpinBoxStyle* spinbox()const;
  ComboBoxStyle* combobox()const;
  GeneralStyle* general()const;


public:
    static void registerAsQml();
    explicit QsStyle(QObject *parent = nullptr,ColorScheme& colorScheme = Qs::instance().colorScheme());
    static QsStyle* qmlAttachedProperties(QObject* parent=nullptr);


public slots:
};
QML_DECLARE_TYPEINFO(QsStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QSPINSTYLE_H
