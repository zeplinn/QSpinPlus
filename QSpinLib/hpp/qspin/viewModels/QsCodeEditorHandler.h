#ifndef CODEEDITORHANDLER_H
#define CODEEDITORHANDLER_H

#include <QObject>
#include <QUrl>
#include <QTextDocument>
#include <QQuickTextDocument>
#include <QQmlEngine>
#include <QFileSelector>
#include <QQmlFileSelector>
#include <QQmlFile>
#include <QTextCodec>
#include "qspin/QObjectBase.h"
#include "QsError.h"
#include "qspin/QmlImportNames.h"
#include <QSyntaxHighlighter>

class QsCodeEditorHandler : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QQuickTextDocument* textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
		QQuickTextDocument* _textDocument; // only safe if used with CodeEditor.qml
		Q_PROPERTY(QSyntaxHighlighter* syntaxHighlighter READ syntaxHighlighter WRITE setSyntaxHighlighter NOTIFY syntaxHighlighterChanged)
		QSyntaxHighlighter *_highlighter;
		Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
		QUrl _fileUrl;

		Q_PROPERTY(bool canUndo READ canUndo NOTIFY canUndoChanged)
		Q_PROPERTY(bool canRedo READ canRedo NOTIFY canRedoChanged)
		bool _canUndo, _canRedo;
	public: //properties
		QQuickTextDocument* textDocument()const;
		void setTextDocument(QQuickTextDocument* value);

		QUrl fileUrl()const;
		void setFileUrl(QUrl value);
		QSyntaxHighlighter* syntaxHighlighter()const;
		void setSyntaxHighlighter(QSyntaxHighlighter* value);
		bool canUndo()const{ return _canUndo;}
		bool canRedo()const{ return _canRedo;}
	private slots: // properties
		void setCanUndo(bool value){
			_canUndo = value;
			emit canUndoChanged();
		}
		void setCanRedo(bool value){
			_canRedo = value;
			emit canRedoChanged();
		}
	signals:// properties
		void textDocumentChanged();
		void fileUrlChanged();
		void syntaxHighlighterChanged();
		void canUndoChanged();
		void canRedoChanged();
	public:
		explicit QsCodeEditorHandler(QObject *parent = nullptr);
		static void registerAsQml();

	Q_SIGNALS:
		void error(QsError::Errors code);
		void loaded(QString doc);
	public slots:
		void saveAs(const QUrl fileUrl);
		void open(const QUrl fileUrl);
		void redo(){
			document()->redo();
		}
		void undo(){
			document()->undo();
		}

	private: // functions
		QTextDocument* document()const;

};
class CodeEditorHandlerExposedMembers:public QObject{
	Q_OBJECT
	QsCodeEditorHandler* _editor;
public:
	explicit CodeEditorHandlerExposedMembers(QsCodeEditorHandler* parent=nullptr):QObject(parent){

	}

public slots:

};

#endif // CODEEDITORHANDLER_H
