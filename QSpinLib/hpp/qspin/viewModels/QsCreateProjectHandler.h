#ifndef QSCREATEPROJECTHANDLER_H
#define QSCREATEPROJECTHANDLER_H

#include <QObject>
#include <QDir>
#include <QUrl>
#include "qspin/QObjectBase.h"
//#include "qspin/viewModels/EventAggregator.h"
//#include "qspin/Qs.h"
class QsCreateProjectHandler: public QObjectBase{
        Q_OBJECT
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        QString _name="";
		Q_PROPERTY(QUrl folder READ folder WRITE setFolder NOTIFY folderChanged)
        QUrl _folder= QUrl(QDir::currentPath());
		Q_PROPERTY(QString absolutePath READ absolutePath NOTIFY absolutePathChanged)


	public:// properties
		QString name()const;
		void setName(QString value);

		QUrl folder()const;
		void setFolder(QUrl value);

		QString absolutePath()const;
	signals: // properties
		void nameChanged();
		void folderChanged();
		void absolutePathChanged();
public:
        using QObjectBase:: QObjectBase;
//		explicit QsCreateProjectHandler(QObject* parent=nullptr,EventAggregator& msgService = Qs::instance().msgService());

};

#endif // QSCREATEPROJECTHANDLER_H
