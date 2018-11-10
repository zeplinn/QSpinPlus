#include "qspin/viewModels/ColorScheme.h"


ColorScheme::ColorScheme(QObject *parent):QObject(parent)
  ,_btnStyle(new ButtonStyle(this))
  ,_comboStyle(new ComboBoxStyle(this))
  ,_spinboxStyle(new SpinBoxStyle(this))
  ,_genereralStyle(new GeneralStyle(this))
  ,_promelaEditor(new PromelaEditor(this)){}

void ColorScheme::open(const QString file, bool checkIsValidColorScheme){
    QFile scheme(file);
    if(!scheme.open(QIODevice::ReadOnly)){
        return;// throw some error
    }
    QByteArray txtDoc = scheme.readAll();
    scheme.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(txtDoc);
    QJsonObject objRoot = jsonDoc.object();
    if(checkIsValidColorScheme){
        QJsonObject obj = objRoot[jsonIds.general].toObject();
        bool flag = _genereralStyle->isValidJsonObject(obj);
        obj = objRoot[jsonIds.button].toObject();
        flag = flag && _btnStyle->isValidJsonObject(obj); // no error handling
        obj = objRoot[jsonIds.spinbox].toObject();
        flag = flag && _spinboxStyle->isValidJsonObject(obj);
        obj = objRoot[jsonIds.combobox].toObject();
        flag = flag && _comboStyle->isValidJsonObject(obj);
        obj = objRoot[jsonIds.promelaEditor].toObject();
        flag = flag && _promelaEditor->isValidJsonObject(obj);
        if(!flag) throw QString("invalid color scheme");
    }
    _genereralStyle->read(objRoot[jsonIds.general].toObject());
    _btnStyle->read(objRoot[jsonIds.button].toObject()); // no error handling
    _spinboxStyle->read(objRoot[jsonIds.spinbox].toObject());
    _comboStyle->read(objRoot[jsonIds.combobox].toObject());
    _promelaEditor->read(objRoot[jsonIds.promelaEditor].toObject());

}

void ColorScheme::save(const QString filename){
    Q_UNUSED(filename)
}

ButtonStyle *ColorScheme::button() const{ return  _btnStyle;}

SpinBoxStyle *ColorScheme::spinbox() const{return _spinboxStyle;}

ComboBoxStyle *ColorScheme::combobox() const{return _comboStyle;}

GeneralStyle *ColorScheme::general() const{ return _genereralStyle;}

PromelaEditor *ColorScheme::promelaEditor() const { return _promelaEditor;}

QColor ButtonStyle::pressed() const{ return _pressed.color;}

void ButtonStyle::setPressed(QColor value){
    if(_pressed.color!= value){
        _pressed.color = value;
        emit pressedChanged();
    }
}

QColor ButtonStyle::border() const{ return _border.color;}

void ButtonStyle::setBorder(QColor value){
    if(_border.color != value){
        _border.color = value;
        emit borderChanged();
    }
}

ButtonStyle::ButtonStyle(QObject *parent):BaseStyle(parent){}

void ButtonStyle::read(const QJsonObject &obj){
    BaseStyle::read(obj);
    _pressed.color = jsonIds.toColor(jsonIds.pressed,obj);
    _border.color   = jsonIds.toColor(jsonIds.border,obj);

}

void ButtonStyle::write(QJsonObject &obj) const{
    Q_UNUSED(obj)
}

bool ButtonStyle::isValidJsonObject(QJsonObject &obj){
    return BaseStyle::isValidJsonObject(obj)
            && jsonIds.isValidRGBArray(obj,jsonIds.pressed)
            && jsonIds.isValidRGBArray(obj,jsonIds.border);

}

QColor GeneralStyle::hovered() const{return _hovered.color;}

QColor GeneralStyle::border() const{return _border.color;}

QColor GeneralStyle::menubarGradiant0() const{return _menubarGradiant0.color;}

QColor GeneralStyle::menubarGradiant1() const{return _menubarGradiant1.color;}

GeneralStyle::GeneralStyle(QObject *parent):BaseStyle(parent){}

void GeneralStyle::read(const QJsonObject &obj){
    BaseStyle::read(obj);
    _border.color   = jsonIds.toColor(jsonIds.border,obj);
    _hovered.color = jsonIds.toColor(jsonIds.hovered,obj);
    _menubarGradiant0.color = jsonIds.toColor(jsonIds.menubarGradiant0,obj);
    _menubarGradiant1.color = jsonIds.toColor(jsonIds.menubarGradiant1,obj);
}

void GeneralStyle::write(QJsonObject &obj) const{
    Q_UNUSED(obj)
}

bool GeneralStyle::isValidJsonObject(QJsonObject &obj){
    return BaseStyle::isValidJsonObject(obj)
            && jsonIds.isValidRGBArray(obj,jsonIds.border)
            && jsonIds.isValidRGBArray(obj,jsonIds.hovered)
            && jsonIds.isValidRGBArray(obj,jsonIds.menubarGradiant0)
            && jsonIds.isValidRGBArray(obj,jsonIds.menubarGradiant1);
}

QColor BaseStyle::foreground() const{ return _foreground.color;}

void BaseStyle::setForeground(QColor value){
    if(_foreground.color!=value){
        _foreground.color = value;
        emit foregroundChanged();
    }
}

QColor BaseStyle::background() const{ return _background.color;}

void BaseStyle::setBackground(QColor value){
    if(_background.color != value){
        _background.color = value;
        emit backgroundChanged();
    }
}

BaseStyle::BaseStyle(QObject *parent):StyleRoot (parent){

}

void BaseStyle::read(const QJsonObject &obj){
    _foreground.color = jsonIds.toColor(jsonIds.foreground,obj);
    _background.color   = jsonIds.toColor(jsonIds.background,obj);
}

void BaseStyle::write(QJsonObject &obj) const{
    Q_UNUSED(obj)
}

bool BaseStyle::isValidJsonObject(QJsonObject &obj){
    return  jsonIds.isValidRGBArray(obj,jsonIds.foreground)
            &&  jsonIds.isValidRGBArray(obj,jsonIds.background);
}







SpinBoxStyle::SpinBoxStyle(QObject *parent):ButtonStyle(parent){}

bool SpinBoxStyle::isValidJsonObject(QJsonObject &obj){
    return ButtonStyle::isValidJsonObject(obj)
            && jsonIds.isValidRGBArray(obj,jsonIds.input)
            && jsonIds.isValidRGBArray(obj,jsonIds.spinner);
}

void SpinBoxStyle::read(const QJsonObject &obj){
    ButtonStyle::read(obj);
    _input = jsonIds.toColor(jsonIds.input,obj);
    _spinner = jsonIds.toColor(jsonIds.spinner,obj);
}

ComboBoxStyle::ComboBoxStyle(QObject *parent):ButtonStyle(parent){}

bool ComboBoxStyle::isValidJsonObject(QJsonObject &obj){
    return ButtonStyle::isValidJsonObject(obj)
            && jsonIds.isValidRGBArray(obj,jsonIds.icon);
}

void ComboBoxStyle::read(const QJsonObject &obj){
    ButtonStyle::read(obj);
    _icon = jsonIds.toColor(jsonIds.icon,obj);
}

StyleRoot::StyleRoot(QObject *parent):QObject(parent){
    //    if(_msgService==nullptr)
    //        _msgService = &Qs::instance().msgService();
}









int PromelaEditor::pointSize() const{return  _pointSize;}

int PromelaEditor::tabIndents() const{return _tabIndents;}

QString PromelaEditor::fontFamily() const{ return _fontFamily;}

QColor PromelaEditor::selectedText() const{ return _selectedText;}

PromelaTextHighlighter PromelaEditor::syntaxHighlighter() const{return _syntaxHighlighter;}

PromelaEditor::PromelaEditor(QObject *parent):BaseStyle(parent)
  ,_syntaxHighlighter(PromelaTextHighlighter()){}

void PromelaEditor::read(const QJsonObject &obj){
    BaseStyle::read(obj);
    _pointSize = obj[jsonIds.pointSize].toInt(10);
    _tabIndents = obj[jsonIds.tabIndents].toInt(4);
    _fontFamily = obj[jsonIds.fontFamily].toString("");
    _selectedText = jsonIds.toColor(jsonIds.selectedText,obj);
    _syntaxHighlighter.read(obj[jsonIds.syntaxHighlighter].toObject());
}

void PromelaEditor::write(QJsonObject &obj) const{Q_UNUSED(obj)}

bool PromelaEditor::isValidJsonObject(QJsonObject &obj) {
    bool flag =BaseStyle::isValidJsonObject(obj);
    flag = jsonIds.isValidInt(obj,jsonIds.pointSize);
    flag = jsonIds.isValidInt(obj,jsonIds.tabIndents);
    flag = jsonIds.isValidString(obj,jsonIds.fontFamily);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.selectedText);
    auto syntaxObj = obj[jsonIds.syntaxHighlighter].toObject();
    flag = _syntaxHighlighter.isValidJsonObject(syntaxObj);
    return flag;
}

void PromelaTextHighlighter::read(const QJsonObject &obj){
    _classes = jsonIds.toColor(jsonIds.classes,obj);
    _keywords = jsonIds.toColor(jsonIds.keywords,obj);
    _comments = jsonIds.toColor(jsonIds.comments,obj);
    _types = jsonIds.toColor(jsonIds.types,obj);
    _numbers = jsonIds.toColor(jsonIds.numbers,obj);
    _operators = jsonIds.toColor(jsonIds.operators,obj);
    _strings = jsonIds.toColor(jsonIds.strings,obj);
    qDebug()<< _classes << keywords() << _types;

}

bool PromelaTextHighlighter::isValidJsonObject(QJsonObject &obj)
{
    bool flag = jsonIds.isValidRGBArray(obj,jsonIds.classes);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.keywords);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.operators);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.comments);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.strings);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.numbers);
    flag = jsonIds.isValidRGBArray(obj,jsonIds.types);
    return flag;
}

void PromelaTextHighlighter::write(QJsonObject &obj) const{Q_UNUSED(obj)}
