#include "qspin/viewModels/QsCodeEditorHandler.h"

QQuickTextDocument*QsCodeEditorHandler::textDocument() const{ return _textDocument; }

void QsCodeEditorHandler::setTextDocument(QQuickTextDocument*value){_textDocument = value; emit textDocumentChanged();}

QUrl QsCodeEditorHandler::fileUrl() const{ return _fileUrl; }

void QsCodeEditorHandler::setFileUrl(QUrl value){ _fileUrl=value; emit fileUrlChanged(); }

QsCodeEditorHandler::QsCodeEditorHandler(QObject *parent) : QObject(parent),_textDocument(nullptr)
{

}

void QsCodeEditorHandler::registerAsQml(){
    qmlRegisterType<QsCodeEditorHandler>(QsImpports::cppItems(),1,0,"QsCodeEditorHandler");
}

void QsCodeEditorHandler::saveAs(const QUrl fileUrl){
	QTextDocument *doc = document();
	if (!doc)
		return;

	const QString filePath = fileUrl.toLocalFile();
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

	QQmlEngine *engine = qmlEngine(this);
	if (!engine) {
		emit error(QsError::OpenDocument);
		return;
	}

	const QUrl path = QQmlFileSelector::get(engine)->selector()->select(fileUrl);
	const QString fileName = QQmlFile::urlToLocalFileOrQrc(path);
	if (QFile::exists(fileName)) {
		QFile file(fileName);
		if (file.open(QFile::ReadOnly)) {
			QByteArray data = file.readAll();
			QTextCodec *codec = QTextCodec::codecForHtml(data);
			if (QTextDocument *doc = document())
				doc->setModified(false);

			emit loaded(codec->toUnicode(data));
		}
	}

	_fileUrl = fileUrl;
	emit fileUrlChanged();
}

QTextDocument*QsCodeEditorHandler::document() const{
	if (!_textDocument)
		return nullptr;
	return _textDocument->textDocument();
}
