#include "qspin/viewModels/QsCodeEditorHandler.h"

QQuickTextDocument*QsCodeEditorHandler::textDocument() const{ return _textDocument; }

void QsCodeEditorHandler::setTextDocument(QQuickTextDocument*value){
	if(_textDocument !=value){
		_textDocument = value;
        if(_textDocument!=nullptr)
            connect(document(),&QTextDocument::modificationChanged
                    ,this,&QsCodeEditorHandler::setModified
                    );

        if(_textDocument != nullptr && _highlighter !=nullptr){
//            QObject::connect(document(),&QTextDocument::undoAvailable,this,&QsCodeEditorHandler::setCanUndo);
//            QObject::connect(document(),&QTextDocument::redoAvailable,this,&QsCodeEditorHandler::setCanRedo);
			_highlighter->setDocument(document());
        }
	}
	emit textDocumentChanged();
}

QString QsCodeEditorHandler::fileUrl() const{ return _fileUrl; }

void QsCodeEditorHandler::setFileUrl(QString value){ _fileUrl=value; emit fileUrlChanged(); }

QSyntaxHighlighter* QsCodeEditorHandler::syntaxHighlighter() const{ return _highlighter;}

void QsCodeEditorHandler::setSyntaxHighlighter(QSyntaxHighlighter *value){
	if(_highlighter!=value){
		_highlighter=value;
		if(_highlighter != nullptr && _textDocument!= nullptr){
			_highlighter->setDocument(document());
		}
		emit syntaxHighlighterChanged();
	}
}

bool QsCodeEditorHandler::modified() const{ return _modified; }

void QsCodeEditorHandler::setModified(bool value){
    if(_modified != value){
        _modified = value;
        emit modifiedChanged();
    }
}

void QsCodeEditorHandler::setText(QString text){
    document()->setPlainText(text);
}

void QsCodeEditorHandler::clearText(){
    document()->clear();
}
QsCodeEditorHandler::QsCodeEditorHandler(QObject *parent) : QObject(parent),_textDocument(nullptr)
  ,_highlighter(nullptr)
  ,_modified(false)
  //,_canUndo(false),_canRedo(false)
{

}

void QsCodeEditorHandler::registerAsQml(){
	qmlRegisterType<QsCodeEditorHandler>(QsImpports::cppItems(),1,0,"QsCodeEditorHandler");
}

void QsCodeEditorHandler::saveAs(const QString& fileUrl){
	QTextDocument *doc = document();
	if (!doc)
		return;

    const QString filePath = fileUrl;
	//const bool isHtml = QFileInfo(filePath).suffix().contains(QLatin1String("htm"));
	QFile file(filePath);
	if(!file.open(QIODevice::WriteOnly|QFile::Text)){
		emit error(QsError::SaveDocument);
	}

	file.write(doc->toPlainText().toUtf8());
	file.close();

	if (fileUrl == _fileUrl)
		return;

	_fileUrl = fileUrl;
	emit fileUrlChanged();
}

void QsCodeEditorHandler::open(const QUrl fileUrl){
	if (fileUrl == _fileUrl)
		return;
	QString filePath =fileUrl.toLocalFile();

	if(!QFile::exists(filePath)){
		qCritical()<< "file do no exist:"<<filePath;
		return;
	}
	QFile f (filePath);
	if(!f.open(QFile::ReadOnly)){
		qCritical()<<" failed to open file" << filePath;
		return;
	}

	document()->setPlainText(f.readAll());
	f.close();


//	QQmlEngine *engine = qmlEngine(this);
//	if (!engine) {
//		emit error(QsError::OpenDocument);
//		return;
//	}

//	const QUrl path = QQmlFileSelector::get(engine)->selector()->select(fileUrl);
//	const QString fileName = QQmlFile::urlToLocalFileOrQrc(path);
//	if (QFile::exists(fileName)) {
//		QFile file(fileName);
//		if (file.open(QFile::ReadOnly)) {
//			QByteArray data = file.readAll();
//			QTextCodec *codec = QTextCodec::codecForHtml(data);
//			if (QTextDocument *doc = document())
//				doc->setModified(false);

//			emit loaded(codec->toUnicode(data));
//		}
//	}

//	_fileUrl = fileUrl;
//	emit fileUrlChanged();
}

QTextDocument*QsCodeEditorHandler::document() const{
	if (!_textDocument)
		return nullptr;
	return _textDocument->textDocument();
}
