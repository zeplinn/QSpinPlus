#ifndef COLORSCHEME_H
#define COLORSCHEME_H
#include <QObject>
#include <QColor>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
class QObjectBase;
#include "qspin/QObjectBase.h"
#include "qspin/models/IQsSerialization.h"
#include "qspin/models/jsonQspinPlusSchemeIds.h"

//static constexpr jsonQspinPlusSchemeIds jsonIds;
class QObjectBase;
struct colorProperty{
    QColor color;
    QString id;
};


// style types
///////////////////////////////////////////////////
/// \brief The StyleRoot class
//////////////////////////////////////////////////

class StyleRoot: public QObjectBase, public IQJsonSerialization{
    Q_OBJECT
    Q_INTERFACES(IQJsonSerialization)
public:
    using QObjectBase::QObjectBase;
    ~StyleRoot(){}
protected:
    jsonQspinPlusSchemeIds jsonIds;
protected:
};

////////////////////////////////////////////////
/// \brief The BaseStyle class
/////////////////////////////////////////////////


class BaseStyle : public StyleRoot
{
    Q_OBJECT

    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground NOTIFY foregroundChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
    colorProperty _foreground, _background;
public: // properties
    QColor foreground()const;
    void setForeground(QColor value);
    QColor background()const;
    void setBackground(QColor value);
signals:
    void foregroundChanged();
    void backgroundChanged();
public:
    using StyleRoot::StyleRoot;
    virtual void read(const QJsonObject& obj) override;
    virtual void write(QJsonObject& obj)const override;
    virtual bool isValidJsonObject(QJsonObject& obj)override;
protected:

};


//////////////////////////////////////////////////
/// \brief The GeneralStyle class
//////////////////////////////////////////////////

class GeneralStyle : public BaseStyle{
    Q_OBJECT
    Q_PROPERTY(QColor hovered READ hovered NOTIFY hoveredChanged)
    Q_PROPERTY(QColor border READ border NOTIFY borderChanged)
    Q_PROPERTY(QColor menubarGradiant0 READ menubarGradiant0 NOTIFY menubarGradiant0Changed)
    Q_PROPERTY(QColor menubarGradiant1 READ menubarGradiant1 NOTIFY menubarGradiant1Changed)
    colorProperty _hovered, _border, _menubarGradiant0, _menubarGradiant1;
public: // properties
    QColor hovered()const;

    QColor border()const;

    QColor menubarGradiant0()const;

    QColor menubarGradiant1()const;

signals: // properties
    void hoveredChanged();
    void borderChanged();
    void menubarGradiant0Changed();
    void menubarGradiant1Changed();
public:
    using BaseStyle::BaseStyle;
    virtual void read(const QJsonObject& obj) override;
    virtual void write(QJsonObject& obj)const override;
    virtual bool isValidJsonObject(QJsonObject& obj) override;
};


/////////////////////////////////////////////////////
/// \brief The ButtonStyle class
/////////////////////////////////////////////////////


class ButtonStyle: public BaseStyle{
    Q_OBJECT
    Q_INTERFACES(IQJsonSerialization)
    Q_PROPERTY(QColor pressed READ pressed NOTIFY pressedChanged)
    Q_PROPERTY(QColor border READ border  NOTIFY borderChanged)
    colorProperty _pressed, _border;
public: // properties
    QColor pressed()const;
    void setPressed(QColor value);
    QColor border()const;
    void setBorder(QColor value);
signals:
    void pressedChanged();
    void borderChanged();
public:
    using BaseStyle:: BaseStyle;
    virtual void read(const QJsonObject& obj)override;
    virtual void write(QJsonObject& obj)const override;
    virtual bool isValidJsonObject(QJsonObject& obj) override;
private:// member functions

};


//////////////////////////////////////////////////////////
/// \brief The SpinBoxStyle class
/////////////////////////////////////////////////////////

class SpinBoxStyle: public ButtonStyle{
    Q_OBJECT
    Q_PROPERTY(QColor input READ input NOTIFY inputChanged)
    Q_PROPERTY(QColor spinner READ spinner NOTIFY spinnerChanged)
    QColor _input, _spinner;
public:// properties
    QColor input()const{ return _input;}
    QColor spinner()const{return _spinner;}
signals: // properties
    void inputChanged();
    void spinnerChanged();
public:
    using ButtonStyle::ButtonStyle;
    virtual bool isValidJsonObject(QJsonObject& obj)override;
    virtual void read(const QJsonObject& obj)override;
};



///////////////////////////////////////////////////////////
/// \brief The ComboBoxStyle class
////////////////////////////////////////////////////////////

class ComboBoxStyle: public ButtonStyle{
    Q_OBJECT
    Q_PROPERTY(QColor icon READ icon NOTIFY iconChanged)
    QColor _icon;
public: // properties
    QColor icon()const{return _icon;}
signals: // properties;
    void iconChanged();
public:
    using ButtonStyle::ButtonStyle;
    virtual bool isValidJsonObject(QJsonObject& obj)override;
    virtual void read(const QJsonObject& obj)override;

};


////////////////////////////////////////////////////////////
/// \brief The PromelaTextHighlighter class
/////////////////////////////////////////////////////////

class PromelaTextHighlighter:public IQJsonSerialization{
    QColor _classes, _keywords, _operators, _comments,_strings,_numbers,_types;
    jsonQspinPlusSchemeIds jsonIds;
public:
    QColor classes()const{ return  QColor(_classes);}
    QColor keywords()const{ return QColor(_keywords);}
    QColor operators()const{ return QColor(_operators);}
    QColor comments()const{ return QColor(_comments);}
    QColor strings()const{ return QColor(_strings);}
    QColor numbers()const{ return QColor(_numbers);}
    QColor types()const{ return _types;}
    // IQJsonSerialization interface
public:
    virtual void  read(const QJsonObject &obj)override;
    virtual bool isValidJsonObject(QJsonObject& obj)override;
    virtual void  write(QJsonObject &obj)const override;
};

Q_DECLARE_METATYPE(PromelaTextHighlighter);
// begin promela editor

////////////////////////////////////////////////////
/// \brief The PromelaEditor class
///////////////////////////////////////////////////

class PromelaEditor: public BaseStyle{
    Q_OBJECT
    Q_PROPERTY(int pointSize READ pointSize NOTIFY pointSizeChanged)
    Q_PROPERTY(int tabIndents READ tabIndents NOTIFY tabIndentsChanged)
    int _pointSize =10,_tabIndents=4;
    Q_PROPERTY(QString fontFamily READ fontFamily NOTIFY fontFamilyChanged)
    QString _fontFamily;
    Q_PROPERTY(QColor selectedText READ selectedText NOTIFY selectedTextChanged)
    QColor _selectedText;
    Q_PROPERTY(PromelaTextHighlighter syntaxHighlighter READ syntaxHighlighter NOTIFY syntaxHighlighterChanged)
    PromelaTextHighlighter _syntaxHighlighter;
public:
    int pointSize()const;
    int tabIndents()const;
    QString fontFamily()const;
    QColor selectedText()const;
    PromelaTextHighlighter syntaxHighlighter()const;
signals:
    void pointSizeChanged();
    void tabIndentsChanged();
    void fontFamilyChanged();
    void selectedTextChanged();
    void syntaxHighlighterChanged();

public:
    using BaseStyle::BaseStyle;
    // IQJsonSerialization interface
public:
    void virtual read(const QJsonObject &obj)override;
    void virtual write(QJsonObject &obj) const override;
    bool virtual isValidJsonObject(QJsonObject &obj)override;
};

// end promela editor

// Style Container

///////////////////////////////////////////////
/// \brief The ColorScheme class
/////////////////////////////////////////////

class ColorScheme: public QObjectBase{
    Q_OBJECT
    ButtonStyle* _btnStyle;
    ComboBoxStyle* _comboStyle;
    SpinBoxStyle* _spinboxStyle;
    GeneralStyle* _genereralStyle;
    PromelaEditor* _promelaEditor;
    jsonQspinPlusSchemeIds jsonIds;

public:
    explicit ColorScheme(QObject* parent=nullptr, EventAggregator* msgService= nullptr);
    void open(const QString file, bool checkIsValidColorScheme=true);
    void save(const QString filename);
    ButtonStyle* button()const;
    SpinBoxStyle* spinbox()const;
    ComboBoxStyle* combobox()const;
    GeneralStyle* general()const;
    PromelaEditor* promelaEditor()const;
};



#include "qspin/QObjectBase.h"
#endif // COLORSCHEME_H
