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
        QUrl _folder= QDir::homePath();
		Q_PROPERTY(QString absolutePath READ absolutePath NOTIFY absolutePathChanged)

        QString _absolutePath;

        Q_PROPERTY(QString filename READ filename NOTIFY nameChanged)
        QString _filename;

        QString filename()const;

        Q_PROPERTY(bool isValidName READ isValidName NOTIFY isValidNameChanged)
        Q_PROPERTY(bool isValidFolder READ isValidFolder NOTIFY isValidFolderChanged)
        bool _isValidName=false, _isValidFolder =true;
	public:// properties
		QString name()const;
		void setName(QString value);

        QUrl folder()const;
        void setFolder(QUrl value);
        QString absolutePath()const;
        void updateAbsolutePath();
        bool isValidName()const;
        bool isValidFolder();
	signals: // properties
		void nameChanged();
		void folderChanged();
		void absolutePathChanged();
        void isValidNameChanged();
        void isValidFolderChanged();
public:
        using QObjectBase:: QObjectBase;
//		explicit QsCreateProjectHandler(QObject* parent=nullptr,EventAggregator& msgService = Qs::instance().msgService());

public slots:
        void setIsValidName(QString name);
        void setIsValidFolder(QUrl folder);

};

#endif // QSCREATEPROJECTHANDLER_H
