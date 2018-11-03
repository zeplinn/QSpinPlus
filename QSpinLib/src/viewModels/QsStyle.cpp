#include "qspin/viewModels/QsStyle.h"

//int QsStyle::buttonHeight() const{return _buttonHeight;}

//void QsStyle::setButtonHeight(int value){_buttonHeight=value;emit buttonHeightChanged();}

//QColor QsStyle::panelBackground() const {return _panelBackground; }

//QColor QsStyle::textColor() const{return _textColor;}

//QColor QsStyle::headerColor() const{return _headerColor;}

//QColor QsStyle::smallHeaderColor() const{return _smallHeaderColor;}

//QColor QsStyle::borderBackground() const{ return _borderBackground; }

//QColor QsStyle::highlightColor() const{return _highlightColor;}

ButtonStyle *QsStyle::button() const{return _colorScheme.button();}

SpinBoxStyle *QsStyle::spinbox() const{return _colorScheme.spinbox();}

ComboBoxStyle *QsStyle::combobox() const{return _colorScheme.combobox();}

GeneralStyle *QsStyle::general() const{return _colorScheme.general();}

void QsStyle::registerAsQml(){
    qmlRegisterUncreatableType<QsStyle>(QsImpports::cppItems(),1,0,"QsStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<ButtonStyle>(QsImpports::cppItems(),1,0,"ButtonStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<GeneralStyle>(QsImpports::cppItems(),1,0,"GeneralStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<ComboBoxStyle>(QsImpports::cppItems(),1,0,"ComboBoxStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<SpinBoxStyle>(QsImpports::cppItems(),1,0,"SpinBoxStyle","no Instance of style object allowed");
}

QsStyle::QsStyle(QObject *parent,ColorScheme& colorScheme) : QObject(parent), _colorScheme(colorScheme)
//  ,_panelBackground("#1e1e1e")// dark grey
//  ,_borderBackground("#353637")// medium grey rgb(53,54,55)
//  ,_textColor("#d4d4d4")// light grey
//  ,_headerColor("#757575") // light medium grey
//  ,_smallHeaderColor("#757575")
//  ,_highlightColor("#f25608")// orange
{

}

QsStyle*QsStyle::qmlAttachedProperties(QObject*parent){
    return new QsStyle(parent);
}

//ColorScheme::ColorScheme(QObject *parent):QObject(parent)
//  ,_btnStyle(new ButtonStyle(this))
//,_comboStyle(new ComboBoxStyle(this))
//,_spinboxStyle(new SpinBoxStyle())
//,_genereralStyle(new GeneralStyle(this)){}

//void ColorScheme::open(const QString file){
//    QFile scheme(file);
//    if(!scheme.open(QIODevice::ReadOnly)){
//        return;// throw some error
//    }
//    QByteArray txtDoc = scheme.readAll();
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(txtDoc);
//    if(!jsonDoc.isObject()){
//        return; // throw some error
//    }
//    _btnStyle = new ButtonStyle();
//    QJsonObject obj = jsonDoc.object();

//    _btnStyle->read(obj["button"].toObject()); // no error handling


//}

//void ColorScheme::save(const QString filename){
//    Q_UNUSED(filename)
//}

//QColor ButtonStyle::pressed() const{ return _pressed.color;}

//void ButtonStyle::setPressed(QColor value){
//    if(_pressed.color!= value){
//        _pressed.color = value;
//        emit pressedChanged();
//    }
//}

//QColor ButtonStyle::border() const{ return _border.color;}

//void ButtonStyle::setBorder(QColor value){
//    if(_border.color != value){
//        _border.color = value;
//        emit borderChanged();
//    }
//}

//ButtonStyle::ButtonStyle(QObject *parent):BaseStyle(parent){}

//void ButtonStyle::read(const QJsonObject &obj){
//    //BaseStyle::read(obj);
//    _pressed.color = jsonToColor(propIds.pressed,obj);
//    _border.color   = jsonToColor(propIds.border,obj);
//}

//void ButtonStyle::write(QJsonObject &obj) const{
//    Q_UNUSED(obj)
//}

//bool ButtonStyle::isValidJsonObject(QJsonObject &obj){
//    return BaseStyle::isValidJsonObject(obj)
//        && isValidRGBArray(obj,propIds.pressed)
//        && isValidRGBArray(obj,propIds.border);

//}

//QColor GeneralStyle::hovered() const{return _hovered.color;}

//QColor GeneralStyle::border() const{return _border.color;}

//QColor GeneralStyle::menubarGradiant0() const{return _menubarGradiant0.color;}

//QColor GeneralStyle::menubarGradiant1() const{return _menubarGradiant1.color;}

//GeneralStyle::GeneralStyle(QObject *parent):BaseStyle(parent){}

//void GeneralStyle::read(const QJsonObject &obj){
//    BaseStyle::read(obj);
//    _border.color   = jsonToColor(propIds.border,obj);
//}

//void GeneralStyle::write(QJsonObject &obj) const{
//    Q_UNUSED(obj)
//}

//bool GeneralStyle::isValidJsonObject(QJsonObject &obj){
//    return BaseStyle::isValidJsonObject(obj)
//            && isValidRGBArray(obj,propIds.border)
//            && isValidRGBArray(obj,propIds.hovered)
//            && isValidRGBArray(obj,propIds.menubarGradiant0)
//            && isValidRGBArray(obj,propIds.menubarGradiant1);
//}

//QColor BaseStyle::foreground() const{ return _foreground.color;}

//void BaseStyle::setForeground(QColor value){
//    if(_foreground.color!=value){
//        _foreground.color = value;
//        emit foregroundChanged();
//    }
//}

//QColor BaseStyle::background() const{ return _background.color;}

//void BaseStyle::setBackground(QColor value){
//    if(_background.color != value){
//        _background.color = value;
//        emit backgroundChanged();
//    }
//}

//BaseStyle::BaseStyle(QObject *parent):QObject(parent){

//}

//void BaseStyle::read(const QJsonObject &obj){
//    _foreground.color = jsonToColor(propIds.foreground,obj);
//    _background.color   = jsonToColor(propIds.background,obj);
//}

//void BaseStyle::write(QJsonObject &obj) const{
//    Q_UNUSED(obj)
//}

//bool BaseStyle::isValidJsonObject(QJsonObject &obj){
//    return  isValidRGBArray(obj,propIds.foreground)
//            &&  isValidRGBArray(obj,propIds.background);
//}



//QColor BaseStyle::jsonToColor(const char id[], const QJsonObject &obj){
//    QJsonArray jrgb = obj[id].toArray();
//    if(jrgb.count()<3){
//        //notify
//        throw QString("invalid rgb array: %1").arg(id);

//    }
//    // red, green, blue (rgb)
//    return  QColor(jrgb[0].toInt(255), jrgb[1].toInt(255), jrgb[2].toInt(255));
//}

//bool BaseStyle::isValidRGBArray(QJsonObject &obj, const char id[]){
//    QJsonArray j = obj[id].toArray();
//    if(j.count()!=3) // r,g,b color channels
//    {
//        // notify gui
//        return false;
//    }
//    for(auto jvalue : j){
//        int colorCode = jvalue.toInt(-1);
//        if(colorCode<0 || colorCode >256) // single color channel range [ 0..255 ]
//        {
//            // notify gui
//            return false;
//        }
//    }
//    return true;
//}

//SpinBoxStyle::SpinBoxStyle(QObject *parent):ButtonStyle(parent){}

//bool SpinBoxStyle::isValidJsonObject(QJsonObject &obj){
//    return ButtonStyle::isValidJsonObject(obj)
//            && isValidRGBArray(obj,propIds.input)
//            && isValidRGBArray(obj,propIds.spinner);
//}

//ComboBoxStyle::ComboBoxStyle(QObject *parent):ButtonStyle(parent){}

//bool ComboBoxStyle::isValidJsonObject(QJsonObject &obj){
//    return ButtonStyle::isValidJsonObject(obj)
//            && isValidRGBArray(obj,propIds.icon);
//}
