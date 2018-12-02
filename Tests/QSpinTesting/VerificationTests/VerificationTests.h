#ifndef VERIFICATIONTESTS_H
#define VERIFICATIONTESTS_H

#include <QObject>
#include <TestSuite.h>
#include "qspin/QObjectBase.h"

#include "qspin/viewModels/QsSpinQueueHandler.h"

class VerificationTests : public TestSuite
{
    Q_OBJECT
public:
    using TestSuite::TestSuite;

signals:

private slots:
};

#endif // VERIFICATIONTESTS_H
