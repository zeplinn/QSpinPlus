#ifndef QSPROJECT_H
#define QSPROJECT_H

#include <QObject>
#include "qspin/models/IQsSerialization.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrl>
#include <QDir>
#include <QList>
#include <QMap>
#include <memory>
#include <QListIterator>
#include <QFile>
#include <QDebug>
#include "Arg.h"
#include "qspin/models/QsSpinConfig.h"
#include "qspin/qsErrors.h"

class QsProject : public IQsSerialization
{
    void documentChanged();
    QString _name;
    QUrl _promelaFile;
    QDir _projectDir;
    QList<qsSpinConfig_ptr> _configs;
    qsSpinConfig_ptr makeNewConfig()const;
public:
    explicit QsProject(const QString name="new_project");

    void read(const QJsonObject& obj) override;
    void write(QJsonObject& obj)const override;
    static bool open(QsProject& project, const QString fileDest);
    static bool saveAs(const QsProject& pro, const QString fileDest);
    int configCount()const;
    qsSpinConfig_ptr & getConfiguration(int idx);
    bool removeConfiguration(int idx);
    bool addNewConfiguration(QString name);
    QDir & projectDir();
    QUrl & promelaFile();
    QString & name();
signals:

public slots:
};
typedef std::shared_ptr<QsProject> qsProject_ptr;
struct newProjectLoaded{
    qsProject_ptr project;
    newProjectLoaded(qsProject_ptr project):project(project){}
};

#endif // QSPROJECT_H
