#ifndef QSCONSOLEHANDLER_H
#define QSCONSOLEHANDLER_H
#include <QObject>
#include <QQuickTextDocument>
#include <QTextDocument>
#include "qspin/Qs.h"
#include "qspin/viewModels/EventAggregator.h"
#include <qspin/eventObjects/PrintToConsole.h>
class QsConsoleHandler: public QObject, public ISubscriber<PrintToConsole>{
		Q_OBJECT

		Q_PROPERTY(QQuickTextDocument* document READ document WRITE setDocument NOTIFY documentChanged)
		QQuickTextDocument* _txtDocument;
	public:
		QQuickTextDocument* document()const;
		void setDocument(QQuickTextDocument* value);
	signals:
		void documentChanged();
	public:
		explicit QsConsoleHandler(QObject* parent= nullptr, EventAggregator* msgService= &Qs::instance().msgService());

		virtual void subscriber(const PrintToConsole& event) override;
	signals:
		void messageSend(QString messsage);

};

#endif // QSCONSOLEHANDLER_H
