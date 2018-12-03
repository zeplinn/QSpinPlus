#include "qspin/Qs.h"

Qs::Qs()

{
    _aggregator = new EventAggregator();
    _colorScheme = new ColorScheme(&dummy,_aggregator);
}


Qs&Qs::instance() {
    static Qs self;
    return  self;
}

EventAggregator *Qs::msgService() {
    return _aggregator;
}

ColorScheme *Qs::colorScheme() {
    return  _colorScheme;
}

QString Qs::readTextFile(QFileInfo fileInfo){
    if(!fileInfo.exists()){
        qCritical("file do not exist");
        return "";
    }
    QFile f(fileInfo.absoluteFilePath());
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical("failed to open file");
        return "";
    }
    QString t = f.readAll();
    f.close();
    return t;
}

bool Qs::writeTextFile(QString document, QString filepath){
    QFile f(filepath);

    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        qCritical("failed to open file");
        return false;
    }
    QTextStream write(&f);
    write << document;
    f.close();
    return true;
}

void Qs::WriteXml(IQXmlSerialization *object, const QString &filePath){
    QFile f(filePath);
    if(! f.open(QIODevice::WriteOnly | QIODevice::Text)){
        qCritical("failed to open xml file");
    }
    QXmlStreamWriter writer(&f);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    object->write(writer);
    f.close();
}
void Qs::OpenXml(IQXmlSerialization *object, const QString &filePath){
    QFile f(filePath);
    if(! f.open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical("failed to open xml file");
    }
    QXmlStreamReader reader(&f);
    reader.readNextStartElement();
    object->read(reader);
    f.close();
}

bool Qs::isValidFileName(QString name){
    static QRegularExpression regex("^([a-zA-Z]|_[a-zA-Z])[_a-zA-Z0-9]{0,128}");
    auto m = regex.match(name);
    return m.hasMatch();
}

bool Qs::isValidVerification(QString filename){
    static QRegularExpression regex("error(?=(\\.qspr))");
    auto m = regex.match(filename);
    return m.hasMatch();
}

QDir Qs::appDir(){ return QDir(QCoreApplication::applicationDirPath());}

QFileInfo Qs::constructResultFileName(QDir destination, QString basename, QDateTime time, bool isOk){
    if(!destination.exists())
        destination.mkpath(destination.absolutePath());
    if(!destination.exists()){
        qCritical("destination folder did not exist and faild to create it");
        return QFileInfo();
    }
    QString str = QString("%1_%2%3.qspr")
            .arg(basename)
            .arg(Qs::getTimeSinceEpochFrom(time))
            .arg(isOk ? "" :".error");
    return QFileInfo(destination.absoluteFilePath(str));
}

QDateTime Qs::extractEpochSinceFromFile(const QString &filename, bool *isValid){
    static QRegularExpression regex("[0-9]{5,24}(?=((\\.error)?\\.qspr))");
    auto m = regex.match(filename);
    (*isValid) = true;
    if(m.hasMatch())
        return  QDateTime::fromMSecsSinceEpoch(m.captured().toLongLong());
    (*isValid)=false;
    return QDateTime();
}

qint64 Qs::getTimeSinceEpochFrom(const QDateTime &time){
    return time.toMSecsSinceEpoch();
}

QString Qs::extractResultFileBaseName(QString filename){
    static QRegularExpression regex("[a-zA-Z]?[_a-zA-Z0-9]*(?=(_[0-9]{5,24}(\\.error)?\\.qspr))");
    auto m = regex.match(filename);
    return m.captured();
}

QString Qs::nameof(QObject *obj){
    return obj->metaObject()->className();
}



void Qs::copyFiles(QDir from, QDir to) {

    if(!from.exists()|| !to.exists()){
        return qCritical("a folder do not exist");
    }
    auto files = from.entryInfoList(QDir::Files);

    for (auto f : files){
        if(!QFile::copy(f.filePath(),to.absoluteFilePath(f.fileName()))){
            auto s = QString("failed to copy file %1, to %2")
                    .arg(f.absoluteFilePath())
                    .arg(to.absoluteFilePath(f.fileName()));
            qCritical(s.toLocal8Bit());
        }
    }
}

void Qs::copyFolder(QDir from, QDir to, QStringList filter){
    if(!from.exists()){
        auto s ="from folder do not exist "+ from.absolutePath();
        qCritical(s.toLocal8Bit());
        return;
    }
    if(!to.exists() && !to.mkpath(to.absolutePath())){
        auto s = "failed to create destination folder: "+to.absolutePath();
        qCritical(s.toLocal8Bit());
        return;
    }

    auto dest = to.entryInfoList(filter, QDir::Dirs| QDir::NoDotAndDotDot);
    for( auto d : dest)
        d.absoluteDir().removeRecursively();


    auto dirs = from.entryInfoList(filter, QDir::Dirs| QDir::NoDotAndDotDot);
    for (auto d : dirs){
        QDir newDir = to;
        newDir.mkdir(d.baseName());
        newDir.cd(d.baseName());
        auto f = d.absoluteDir();
        f.cd(d.baseName());
        copyFolder(f,newDir);
    }
    copyFiles(from,to);
}

void Qs::removeFile(const QString &file){
    QFile::remove(file);
}

void Qs::removeFiles(QDir folder, QStringList filter){

    auto files = folder.entryInfoList(filter,QDir::Files |QDir::NoDotAndDotDot);
    for( auto file : files){
        removeFile(file.absoluteFilePath());
    }
}








