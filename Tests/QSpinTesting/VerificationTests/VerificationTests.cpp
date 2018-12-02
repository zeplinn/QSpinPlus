#include "VerificationTests.h"

void VerificationTests::runVerification_test(){
    safeTest([this](){
        auto msg = new EventAggregator();
        auto promela = new QsPromelaHandler(this,msg);
        auto verify = new QsVerifyHandler(this,msg);
        auto queue = new QsSpinQueueHandler(this,msg);

        promela->openDocument(QUrl("verify:spinTest.pml"));
        verify->queueVerification(verify->currentConfiguration());
    });
}
