#include "qspin/viewModels/ColorScheme.h"
ColorScheme::ColorScheme(QObject *parent):QObject(parent)
  ,_btnStyle(new ButtonStyle(this))
  ,_comboStyle(new ComboBoxStyle(this))
  ,_spinboxStyle(new SpinBoxStyle())
  ,_genereralStyle(new GeneralStyle(this)){}

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
        QJsonObject obj = objRoot[propIds.general].toObject();
         bool flag = _genereralStyle->isValidJsonObject(obj);
        obj = objRoot[propIds.button].toObject();
        flag = flag && _btnStyle->isValidJsonObject(obj); // no error handling
        obj = objRoot[propIds.spinbox].toObject();
        flag = flag && _spinboxStyle->isValidJsonObject(obj);
        obj = objRoot[propIds.combobox].toObject();
        flag = flag && _comboStyle->isValidJsonObject(obj);
        if(!flag) throw QString("invalid color scheme");
    }
    _genereralStyle->read(objRoot[propIds.general].toObject());
    _btnStyle->read(objRoot[propIds.button].toObject()); // no error handling
    _spinboxStyle->read(objRoot[propIds.spinbox].toObject());
    _comboStyle->read(objRoot[propIds.combobox].toObject());

}

void ColorScheme::save(const QString filename){
    Q_UNUSED(filename)
}

ButtonStyle *ColorScheme::button() const{ return  _btnStyle;}

SpinBoxStyle *ColorScheme::spinbox() const{return _spinboxStyle;}

ComboBoxStyle *ColorScheme::combobox() const{return _comboStyle;}

GeneralStyle *ColorScheme::general() const{ return _genereralStyle;}

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
    _pressed.color = jsonToColor(propIds.pressed,obj);
    _border.color   = jsonToColor(propIds.border,obj);

}

void ButtonStyle::write(QJsonObject &obj) const{
    Q_UNUSED(obj)
}

bool ButtonStyle::isValidJsonObject(QJsonObject &obj){
    return BaseStyle::isValidJsonObject(obj)
            && isValidRGBArray(obj,propIds.pressed)
            && isValidRGBArray(obj,propIds.border);

}

QColor GeneralStyle::hovered() const{return _hovered.color;}

QColor GeneralStyle::border() const{return _border.color;}

QColor GeneralStyle::menubarGradiant0() const{return _menubarGradiant0.color;}

QColor GeneralStyle::menubarGradiant1() const{return _menubarGradiant1.color;}

GeneralStyle::GeneralStyle(QObject *parent):BaseStyle(parent){}

void GeneralStyle::read(const QJsonObject &obj){
    BaseStyle::read(obj);
    _border.color   = jsonToColor(propIds.border,obj);
    _hovered.color = jsonToColor(propIds.hovered,obj);
    qDebug()<<"menu bar before"<< _menubarGradiant0.color << _menubarGradiant1.color;
    _menubarGradiant0.color = jsonToColor(propIds.menubarGradiant0,obj);
    _menubarGradiant1.color = jsonToColor(propIds.menubarGradiant1,obj);
    qDebug()<< "menubar after" <<_menubarGradiant0.color << _menubarGradiant1.color;
}

void GeneralStyle::write(QJsonObject &obj) const{
    Q_UNUSED(obj)
}

bool GeneralStyle::isValidJsonObject(QJsonObject &obj){
    return BaseStyle::isValidJsonObject(obj)
            && isValidRGBArray(obj,propIds.border)
            && isValidRGBArray(obj,propIds.hovered)
            && isValidRGBArray(obj,propIds.menubarGradiant0)
            && isValidRGBArray(obj,propIds.menubarGradiant1);
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

BaseStyle::BaseStyle(QObject *parent):QObject(parent){

}

void BaseStyle::read(const QJsonObject &obj){
    _foreground.color = jsonToColor(propIds.foreground,obj);
    _background.color   = jsonToColor(propIds.background,obj);
}

void BaseStyle::write(QJsonObject &obj) const{
    Q_UNUSED(obj)
}

bool BaseStyle::isValidJsonObject(QJsonObject &obj){
    return  isValidRGBArray(obj,propIds.foreground)
            &&  isValidRGBArray(obj,propIds.background);
}



QColor BaseStyle::jsonToColor(const char id[], const QJsonObject &obj){
    QJsonArray jrgb = obj[id].toArray();
    if(jrgb.count()<3){
        //notify
        throw QString("invalid rgb array: %1").arg(id);

    }
    // red, green, blue (rgb)
    return  QColor(jrgb[0].toInt(255), jrgb[1].toInt(255), jrgb[2].toInt(255));
}

bool BaseStyle::isValidRGBArray(QJsonObject &obj, const char id[]){
    QJsonArray j = obj[id].toArray();
    if(j.count()!=3) // r,g,b color channels
    {
        // notify gui
        return false;
    }
    for(auto jvalue : j){
        int colorCode = jvalue.toInt(-1);
        if(colorCode<0 || colorCode >256) // single color channel range [ 0..255 ]
        {
            // notify gui
            return false;
        }
    }
    return true;
}

SpinBoxStyle::SpinBoxStyle(QObject *parent):ButtonStyle(parent){}

bool SpinBoxStyle::isValidJsonObject(QJsonObject &obj){
    return ButtonStyle::isValidJsonObject(obj)
            && isValidRGBArray(obj,propIds.input)
            && isValidRGBArray(obj,propIds.spinner);
}

void SpinBoxStyle::read(const QJsonObject &obj){
    ButtonStyle::read(obj);
    _input = jsonToColor(propIds.input,obj);
    _spinner = jsonToColor(propIds.spinner,obj);
}

ComboBoxStyle::ComboBoxStyle(QObject *parent):ButtonStyle(parent){}

bool ComboBoxStyle::isValidJsonObject(QJsonObject &obj){
    return ButtonStyle::isValidJsonObject(obj)
            && isValidRGBArray(obj,propIds.icon);
}

void ComboBoxStyle::read(const QJsonObject &obj){
    ButtonStyle::read(obj);
    _icon = jsonToColor(propIds.icon,obj);
}
