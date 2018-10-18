//#include "QsProjectTesting.h"

//QsProjectTesting::QsProjectTesting(QObject *parent):QObject (parent)
//{

//}

//void QsProjectTesting::test_addConfigurations(){
//    QsHelper::safeTest([](){

//        QsProject p;
//        QCOMPARE(p.configCount(),0);// no configs added
//        p.addNewConfiguration("newConfig");
//        QCOMPARE(p.configCount(),1);
//        //is the added returned config the same instance
//        qsSpinConfig_ptr
//                ref1 = p.getConfiguration(0),
//                ref2 = p.getConfiguration(0);
//        QCOMPARE(ref1.get(),ref2.get());
//    });
//}
