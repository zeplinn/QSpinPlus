#ifndef QSDIVIDER_H
#define QSDIVIDER_H

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QDebug>
//#include <QMetaObject>
#include <QColor>
#include <QQmlEngine>
#include "qspin/QmlImportNames.h"

class QsDivider:public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(int oritentation READ oritentation WRITE setOritentation NOTIFY oritentationChanged)
	int _orientation= Qt::Horizontal;
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	QColor _color=QColor("#333333");
	Q_PROPERTY(bool isDottedLine READ isDottedLine WRITE setIsDottedLine NOTIFY isDottedLineChanged)
	bool _isDottedLine=false;
    Q_PROPERTY(int thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
    int _thickness =4;
public:
	int oritentation()const;
	void setOritentation(int value);
	QColor color()const;
	void setColor(QColor value);
	bool isDottedLine()const;
	void setIsDottedLine(bool value);
    int thickness()const{return _thickness;}
    void setThickness(int value){
        _thickness = value;
        setHeight(value);setWidth(value);
        emit thicknessChanged();
    }
signals:
	void oritentationChanged();
	void colorChanged();
	void isDottedLineChanged();
    void thicknessChanged();
public:
	static void registerAsQml();
	QsDivider(QQuickItem* parent=nullptr);
	void paint(QPainter* painter)override;
};

#endif
