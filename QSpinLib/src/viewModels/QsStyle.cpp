#include "qspin/viewModels/QsStyle.h"

int QsStyle::buttonHeight() const{return _buttonHeight;}

void QsStyle::setButtonHeight(int value){_buttonHeight=value;emit buttonHeightChanged();}

QColor QsStyle::panelBackground() const {return _panelBackground; }

QColor QsStyle::textColor() const{return _textColor;}

QColor QsStyle::headerColor() const{return _headerColor;}

QColor QsStyle::smallHeaderColor() const{return _smallHeaderColor;}

QColor QsStyle::borderBackground() const{ return _borderBackground; }

QColor QsStyle::highlightColor() const{return _highlightColor;}

void QsStyle::registerAsQml(){
	qmlRegisterUncreatableType<QsStyle>(QsImpports::cppItems(),1,0,"QsStyle","no Instance of style object allowed");
}

QsStyle::QsStyle(QObject *parent) : QObject(parent)
  ,_panelBackground("#1e1e1e")// dark grey
  ,_borderBackground("#353637")// medium grey rgb(53,54,55)
  ,_textColor("#d4d4d4")// light grey
  ,_headerColor("#757575") // light medium grey
  ,_smallHeaderColor("#757575")
  ,_highlightColor("#f25608")// orange
{

}

QsStyle*QsStyle::qmlAttachedProperties(QObject*parent){
	return new QsStyle(parent);
}
