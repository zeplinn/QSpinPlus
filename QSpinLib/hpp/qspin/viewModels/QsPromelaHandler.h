#ifndef QSPROMELAHANDLER_H
#define QSPROMELAHANDLER_H
#include <QObject>
#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include "qspin/Qs.h"
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"
#include "qspin/eventObjects/ProjectSaved.h"
#include "qspin/eventObjects/PrintToConsole.h"
class QsPromelaHandler : public QObject{
		Q_OBJECT

		Q_PROPERTY(QsCodeEditorHandler* editor READ editor WRITE setEditor NOTIFY editorChanged)
		QsCodeEditorHandler* _editor;

	public:
		QsCodeEditorHandler* editor()const;
		void setEditor(QsCodeEditorHandler* value);
	signals:
		void editorChanged();
	private:
		EventAggregator* _msgService;

		EventAggregator& msgService();
	public:
		explicit QsPromelaHandler(QObject* parent=nullptr,
								  EventAggregator* msgService = &Qs::instance().msgService());
	signals:
		void projectSaved(QUrl url);
	public slots:
		void saveDocument(QUrl fileUrl);
		void openDocument(QUrl fileUrl){
			editor()->open(fileUrl);
		}
		void closeDocument(QUrl fileUrl){
			Q_UNUSED(fileUrl)
		}


};

#endif // QSPROMELAHANDLER_H
