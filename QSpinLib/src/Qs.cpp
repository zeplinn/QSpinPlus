#include "qspin/Qs.h"

Qs::Qs()

{
    _aggregator = new EventAggregator(&dummy);
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

QDir Qs::appDir(){ return QDir(QCoreApplication::applicationDirPath());}

QString Qs::nameof(QObject *obj){
    return obj->metaObject()->className();
}

void QsCopy::copyFiles(QDir from, QDir to) {

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

void QsCopy::copyFolder(QDir from, QDir to,QStringList filter){
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
