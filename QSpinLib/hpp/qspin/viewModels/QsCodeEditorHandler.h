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
#include "QsError.h"
#include <QTextCodec>
#include "qspin/QmlImportNames.h"

class QsCodeEditorHandler : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QQuickTextDocument* textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
		QQuickTextDocument* _textDocument; // only safe if used with CodeEditor.qml
		Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
		QUrl _fileUrl;
	public: //properties
		QQuickTextDocument* textDocument()const;
		void setTextDocument(QQuickTextDocument* value);

		QUrl fileUrl()const;
		void setFileUrl(QUrl value);
	signals:// properties
		void textDocumentChanged();
		void fileUrlChanged();
	public:
        explicit QsCodeEditorHandler(QObject *parent = nullptr);
		static void registerAsQml();

	Q_SIGNALS:
		void error(QsError::Errors code);
		void loaded(QString doc);
	public slots:
		void saveAs(const QUrl fileUrl);
		void open(const QUrl fileUrl);

	private: // functions
		QTextDocument* document()const;

};

#endif // CODEEDITORHANDLER_H
