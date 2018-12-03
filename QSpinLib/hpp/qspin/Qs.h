#ifndef QS_H
#define QS_H
class EventAggregator;
class ColorScheme;
#include "qspin/models/IQsSerialization.h"
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/viewModels/ColorScheme.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QRegularExpression>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QDateTime>
#include <QFileInfo>
#include <QCoreApplication>

struct ProjectInfo{
    QFileInfo project, pml;
    QDir resultsFolder, binFolder, queuedFolder;
    ProjectInfo(){}
    explicit ProjectInfo(QFileInfo pml, QFileInfo project,
                         QDir results,QDir bin, QDir queuedFolder)
        :project(project)
        ,pml(pml)
        ,resultsFolder(results)
        ,binFolder(bin)
        ,queuedFolder(queuedFolder)
    {}

};
class Qs{
        EventAggregator* _aggregator;
        ColorScheme* _colorScheme;
        ProjectInfo _info;
        QObject dummy;
        Qs();
    public:
        Qs(Qs const&)               = delete;
        void operator=(Qs const&)   = delete;

        static Qs& instance();
        // member functions
        EventAggregator* msgService();
        ColorScheme* colorScheme();

        QDir appDir();
        // static memember functions
        static QFileInfo constructResultFileName(QDir destination, QString basename, QDateTime time=QDateTime::currentDateTime(), bool isOk=true);
        static QDateTime extractEpochSinceFromFile(const QString& filename,bool* isValid);
        static qint64 getTimeSinceEpochFrom(const QDateTime& time);
        static QString extractResultFileBaseName(QString filename);
        static QString readTextFile(QFileInfo fileInfo);
        static bool writeTextFile(QString document, QString fileInfo);
        static void WriteXml(IQXmlSerialization* object,const QString& filePath);
        static void OpenXml(IQXmlSerialization *object, const QString &filePath);
        static bool isValidFileName(QString name);
        template<typename T>
        static bool isClassName(const QStringRef& compare){
            QString str = typeid (T).name();
            auto s = QStringRef(&str,6,str.count()-7);
            return s==compare;

        }
        static bool isValidVerification(QString filename);

        template<typename T>
        static QString  nameof(){
            QString str = typeid (T).name();
            auto s = QStringRef(&str,6,str.count()-7);
            return s.toString();

        }

        static QString nameof(QObject* obj);

    static void copyFiles(QDir from, QDir to);
static void copyFolder(QDir from, QDir to, QStringList filter= QStringList());
static void removeFile(const QString& file);
static void removeFiles(QDir folder, QStringList filter=QStringList());
};

#endif // QS_H
