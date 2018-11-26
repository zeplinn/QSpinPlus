#ifndef QSCONSOLEHANDLER_H
#define QSCONSOLEHANDLER_H
#include <QObject>
#include <QQuickTextDocument>
#include <QTextDocument>
#include "qspin/QObjectBase.h"
class QsConsoleHandler: public QObjectBase, public ISubscriber<PrintToConsole>{
		Q_OBJECT

		Q_PROPERTY(QQuickTextDocument* document READ document WRITE setDocument NOTIFY documentChanged)
		QQuickTextDocument* _txtDocument;
	public:
		QQuickTextDocument* document()const;
		void setDocument(QQuickTextDocument* value);
	signals:
        void documentChanged();
	public:
        using QObjectBase::QObjectBase;
        explicit QsConsoleHandler(QObject* parent = nullptr, EventAggregator* msgService=nullptr);

		virtual void subscriber(const PrintToConsole& event) override;
	signals:
		void messageSend(QString messsage);

};

#endif // QSCONSOLEHANDLER_H
