#ifndef QSERROR_H
#define QSERROR_H
#include <QQmlEngine>
#include <QObject>
#include "qspin/QmlImportNames.h"
class QsError : public QObject
{
		Q_OBJECT
	public:
		enum Errors{
			SaveDocument,
			OpenDocument
		};
		Q_ENUMS(Errors)
		explicit QsError(QObject *parent = nullptr);
		static void registerAsQml();
		Q_INVOKABLE QString message(Errors code);
	signals:

	public slots:
};

#endif // QSERROR_H
