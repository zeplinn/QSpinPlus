#include "qspin/cppView/QsDivider.h"

int QsDivider::oritentation() const{return _orientation;}

void QsDivider::setOritentation(int value){_orientation=value; emit oritentationChanged();}

QColor QsDivider::color() const{return _color;}

void QsDivider::setColor(QColor value){_color=value; emit colorChanged();}

bool QsDivider::isDottedLine() const{return _isDottedLine;}

void QsDivider::setIsDottedLine(bool value){_isDottedLine = value; emit isDottedLineChanged();}

void QsDivider::registerAsQml(){
    qmlRegisterType<QsDivider>("QSpin.CppItems",1,0,"QsDivider");
}

QsDivider::QsDivider(QQuickItem *parent):QQuickPaintedItem(parent) {setHeight(1); setWidth(1);}

void QsDivider::paint(QPainter *painter){
    QPen pen(color());

    if(_isDottedLine)
        pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    if(oritentation()==Qt::Horizontal){

        painter->drawLine(0,0,width(),0);
    }
    else if(oritentation()==Qt::Vertical){
        painter->drawLine(0,0,0,height());
    }
}
