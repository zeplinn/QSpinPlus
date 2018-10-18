#ifndef QSPROCESSHANDLER_H
#define QSPROCESSHANDLER_H

#include <QObject>
#include <QStringList>
#include <QAbstractListModel>
#include <QHash>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QDir>
#include <QProcess>
#include "qspin/models/QsProject.h"
#include <system_error>

class QsProcessHandler : public QAbstractListModel
{
	Q_OBJECT
	QStringList _messages;
	enum roles{
		msg_role =Qt::UserRole+1
	};
	QsProject* project =nullptr;
public:
	explicit QsProcessHandler(QObject *parent = nullptr);

	virtual QVariant data(const QModelIndex& index, int role =Qt::DisplayRole) const override;
	virtual int rowCount(const QModelIndex &parent =QModelIndex())const override;
	QHash<int,QByteArray> roleNames()const override;
	Q_INVOKABLE void addMsg(const QString& msg);
	Q_INVOKABLE void addMsgs(const QList<QByteArray>& msg);

signals:
	void messagesChanged();
	void newMesssageUpdated(const QString msg);
public slots:
	void testMsgSystem();
	void currentDir(){
		addMsg( QDir::currentPath());
	}
	void runSpin();
	void runPan();
	void openProject(QUrl file);
};

#endif // QSPROCESSHANDLER_H
