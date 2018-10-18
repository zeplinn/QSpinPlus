#ifndef QSPINSTYLE_H
#define QSPINSTYLE_H

#include <QObject>
#include <QtQml>
#include <QColor>
#include <QQmlEngine>
#include "qspin/QmlImportNames.h"

class QsStyle : public QObject
{
		Q_OBJECT
		Q_PROPERTY(int buttonHeight READ buttonHeight WRITE setButtonHeight NOTIFY buttonHeightChanged)
		int _buttonHeight=20;
		Q_PROPERTY(QColor panelBackground READ panelBackground CONSTANT)
		QColor _panelBackground;
		Q_PROPERTY(QColor borderBackground READ borderBackground CONSTANT)
		QColor _borderBackground;
		Q_PROPERTY(QColor textColor READ textColor CONSTANT)
		QColor _textColor;
		Q_PROPERTY(QColor headerColor READ headerColor CONSTANT)
		QColor _headerColor;
		Q_PROPERTY(QColor smallHeaderColor READ smallHeaderColor CONSTANT)
		QColor _smallHeaderColor;
		Q_PROPERTY(QColor highlightColor READ highlightColor CONSTANT)
		QColor _highlightColor;

	public: // properties
		int buttonHeight()const;
		void setButtonHeight(int value);

		QColor panelBackground()const;
		QColor textColor()const;
		QColor headerColor()const;
		QColor smallHeaderColor()const;
		QColor borderBackground()const;
		QColor highlightColor()const;
	signals:// properties
		void buttonHeightChanged();
	public:
        static void registerAsQml();
        explicit QsStyle(QObject *parent = nullptr);
        static QsStyle* qmlAttachedProperties(QObject* parent=nullptr);


	public slots:
};
QML_DECLARE_TYPEINFO(QsStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QSPINSTYLE_H
