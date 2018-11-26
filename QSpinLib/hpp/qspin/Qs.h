#ifndef QS_H
#define QS_H
class EventAggregator;
class ColorScheme;
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/viewModels/ColorScheme.h"
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>

class Qs{
        EventAggregator* _aggregator;
        ColorScheme* _colorScheme;
    QObject dummy;
        Qs();
    public:
        Qs(Qs const&)               = delete;
        void operator=(Qs const&)   = delete;

        static Qs& instance();
        // member functions
        EventAggregator* msgService();
        ColorScheme* colorScheme();


        // static memember functions
        QDir appDir();

        template<typename T>
        static bool isClassName(const QStringRef& compare){
            QString str = typeid (T).name();
            auto s = QStringRef(&str,6,str.count()-7);
            return s==compare;

        }

        template<typename T>
        static QString  nameof(){
            QString str = typeid (T).name();
            auto s = QStringRef(&str,6,str.count()-7);
            return s.toString();

        }

        static QString nameof(QObject* obj);


};

class QsCopy{
    explicit QsCopy(){}

public:
static void copyFiles(QDir from, QDir to);
static void copyFolder(QDir from, QDir to, QStringList filter= QStringList());
};

#endif // QS_H
