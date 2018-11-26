#include "qspin/cppView/TextGutterArea.h"

QQuickTextDocument *TextGutterArea::textDocument() const{return _textDocument;}

void TextGutterArea::setTextDocument(QQuickTextDocument *doc){
	_textDocument = doc;
	if(textDocumentExists()){
		// attach draw update to event blockCountChanged
		_totalBlockCountConnection
				= connect(document(),&QTextDocument::blockCountChanged
                          ,[=](int newBlockCount){Q_UNUSED(newBlockCount) update(boundingRect().toRect()); } );
		// ensure gutter is updated when document is set for initial first line display
		update(boundingRect().toRect());
	}
	emit textDocumentChanged();
}

int TextGutterArea::rightMargin(){return _rightMargin;}

void TextGutterArea::setRightMargin(int value){_rightMargin = value; emit rightMarginChanged();}

void TextGutterArea::registerAsQml(){         qmlRegisterType<TextGutterArea>("QSpin.CppItems",1,0,"TextGutterArea");  }

QTextDocument *TextGutterArea::document() const{return textDocument()->textDocument();}

QAbstractTextDocumentLayout *TextGutterArea::layout() const{return document()->documentLayout();}

int TextGutterArea::fontHeight(){
	return QFontMetrics(document()->defaultFont()).height();
}

TextGutterArea::TextGutterArea(QQuickItem *parent)
	: QQuickPaintedItem(parent),_textDocument(nullptr)
	,_self(this)
{
}

bool TextGutterArea::textDocumentExists(){return _textDocument!=nullptr;}

void TextGutterArea::paint(QPainter *painter){
	painter->setRenderHint(QPainter::Antialiasing);
    painter->setFont(font());
    painter->setPen(textColor());
	if(!textDocumentExists()) return;

	QTextBlock block = firstVisibleTextBlock();
	QRect blockRect = layout()->blockBoundingRect(block).toRect();
	//QRect documentRect= parentItem()->boundingRect().toRect();
	int bTop = blockRect.top()-_visibleTop;
	int bBottom = bTop +blockRect.height();
	int textWidth = width()- rightMargin();
	while (block.isValid()) {

		if( bBottom >= y()){
			QString num = QString::number(block.blockNumber()+1);
			painter->drawText(0,bTop,textWidth,bBottom,Qt::AlignRight,num);
		}
		else if(bTop < height()){
			QString num = QString::number(block.blockNumber()+1);
			painter->drawText(0,bTop,textWidth,bBottom,Qt::AlignRight,num);
		}
		else break;
		// get next block
		block = block.next();
		bTop = bBottom;
		bBottom += (int) layout()->blockBoundingRect(block).height();
	}
}

void TextGutterArea::documentViewportVerticalupdate(qreal vTop, qreal vBottom, bool isPanning){
    _visibleTop = (int) vTop;
	_visibleBottom = (int) vBottom;

	QTextBlock block = firstVisibleTextBlock();
	QRect blockBounds = layout()->blockBoundingRect(block).toRect();
	// update first visible block
	while (block.isValid()) {
		if	(blockBounds.top()<=_visibleTop && blockBounds.bottom()>= _visibleTop){
			_firstVisibleBlock= block.blockNumber();
			break;
		}
		else if(blockBounds.bottom()<_visibleTop && blockBounds.top()< _visibleTop)
			block = block.next();
		else if(blockBounds.top()>_visibleTop && blockBounds.bottom() > _visibleTop)
			block = block.previous();

		blockBounds = layout()->blockBoundingRect(block).toRect();
	}
	if (_firstVisibleBlock< 0) _firstVisibleBlock = 0;
    if(isPanning){
		update(boundingRect().toRect());
	}
}












