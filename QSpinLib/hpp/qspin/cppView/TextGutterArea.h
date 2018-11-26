#ifndef TEXTGUTTER_H
#define TEXTGUTTER_H

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QQuickTextDocument>
#include <QTextBlock>
#include <QFontMetrics>
#include <QDebug>
#include <QMetaObject>
#include <QColor>
#include <QFont>
#include <QQmlEngine>
//#include "qspin/Qs.h"
class TextGutterArea : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(QQuickTextDocument* textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
	QQuickTextDocument* _textDocument;
	Q_PROPERTY(int rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
	int _rightMargin=0;
	Q_PROPERTY(int visibleTop READ visibleTop WRITE setVisibleTop NOTIFY visibleTopChanged)
	Q_PROPERTY(int scrollViewHeight READ scrollViewHeight WRITE setScrollViewHeight NOTIFY scrollViewHeightChanged)
	int _scrollviewHeight=0;
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    QColor _textColor;
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    QFont _font;
public: // properties
	QQuickTextDocument* textDocument()const;
	void setTextDocument(QQuickTextDocument* doc);

	int rightMargin();
	void setRightMargin(int value);

	int visibleTop(){return _visibleTop;}
	void setVisibleTop(int value){
		_visibleTop=value;
		emit visibleTopChanged();}

	int scrollViewHeight(){return _scrollviewHeight;}
    void setScrollViewHeight(int value){_scrollviewHeight=value; emit scrollViewHeightChanged();}

    QColor textColor()const{return _textColor;}
    void setTextColor(QColor color){_textColor=color; emit textColorChanged();}

    QFont font()const{return _font;}
    void setFont(QFont value){_font=value;emit fontChanged();}
signals: //properties
	void textDocumentChanged();
	void rightMarginChanged();
	void visibleTopChanged();
	void scrollViewHeightChanged();
    void textColorChanged();
    void fontChanged();

private: // fields
    TextGutterArea* _self;
	int _firstVisibleBlock =0, _visibleTop=0, _visibleBottom=0;
	QMetaObject::Connection _totalBlockCountConnection; // owner
public:static void registerAsQml();
        explicit TextGutterArea(QQuickItem *parent = nullptr);
    ~TextGutterArea(){
		if(textDocumentExists())
			disconnect(_totalBlockCountConnection);
	}
	QTextDocument* document()const;
	QAbstractTextDocumentLayout* layout()const;
	int fontHeight();
	bool textDocumentExists();
private: // fucntions
	QTextBlock firstVisibleTextBlock(){
		return document()->findBlockByNumber(_firstVisibleBlock);
	}
	void paint(QPainter *painter)override;
signals:

public slots:
	/*!
	 * \brief blockCountUpdated updates gutter on creation/deletion of a new line
	 * \param count is the new total block count
	 * \obsolete replcaed by internal lambda
	 */
	void blockCountUpdated(int count){
        Q_UNUSED(count)
		update(boundingRect().toRect());
	}
	/*!
	 * \brief documentViewportVerticalupdate keeps track of the first visible text block and visible viewport area (vertical only).
	 * \param top coordinate of the visible text areas visible part
	 * \param bottom coordinate of the visible text areas visible part
	 * \param isPanning used to only update the gutter when panning occours.
	 */
	void documentViewportVerticalupdate(qreal vTop, qreal vBottom, bool isPanning);
private:
	void paintBrute(QPainter* painter);
	void paintGuess(QPainter* painter);
};


#endif // TEXTGUTTER_H
