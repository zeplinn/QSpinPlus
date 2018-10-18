#ifndef QSCREATEPROJECTHANDLER_H
#define QSCREATEPROJECTHANDLER_H

#include <QObject>
#include <QDir>
#include <QUrl>
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/Qs.h"
class QsCreateProjectHandler: public QObject{
		Q_OBJECT
		EventAggregator& msgService;
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		QString _name;
		Q_PROPERTY(QUrl folder READ folder WRITE setFolder NOTIFY folderChanged)
		QUrl _folder;
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
		explicit QsCreateProjectHandler(QObject* parent=nullptr,EventAggregator& msgService = Qs::instance().msgService());

};

#endif // QSCREATEPROJECTHANDLER_H
