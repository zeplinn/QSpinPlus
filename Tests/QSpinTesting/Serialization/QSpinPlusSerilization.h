#ifndef QSPINPLUSSERILIZATION_H
#define QSPINPLUSSERILIZATION_H

#include <QObject>
#include "../TestSuite.h"
#include "qspin/models/QsItemConfiguration.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "qspin/models/Arg.h"
#include <QFile>
#include <QDebug>
#include "qspin/models/QsVerificationConfiguration.h"
class QSpinPlusSerilization : public TestSuite
{
    Q_OBJECT
public:
    using TestSuite::TestSuite;

signals:

private slots:
    void readItemConfiguration();
    void writeItemConfiguration();

    void readItemValueConfiguration();
    void writeValueConfiguration();
    void readVerificationConfiguration();
    void writeVerificationCOnfiguration();

};

#endif // QSPINPLUSSERILIZATION_H
