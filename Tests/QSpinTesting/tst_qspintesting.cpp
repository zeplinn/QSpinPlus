#include <QtTest>
#include <QObject>
#include "QsProjectTesting.h"
#include "QsSpinRunTesting.h"
#include "TestSuite.h"
#include "EmptyTest.h"
#include <QCoreApplication>
// add necessary includes here
//int construct(int argc,char** argv){
//    return 0;

int main(int argc, char** argv){
	int status=0;
	// only added so qt creators test result tab is working.
	QCoreApplication app(argc,argv);
    QDir::addSearchPath("verify","D:/projects/Bachelor/QSpinPlus/Tests/QSpinTesting/files/verification");
	auto tests = TestSuite::tests();
	EmptyTest tst2;
	status |=  QTest::qExec(&tst2,argc,argv);
	while (!tests.isEmpty()) {
		status |=QTest::qExec(tests.takeFirst(),argc,argv);
	}
	//QTEST_SET_MAIN_SOURCE_PATH
	app.exec();
	return status;
//    int status =0;
////    auto init_test = [&status,argc,argv](QObject* obj){
////        status |= QTest::qExec(obj,argc,argv);
////        delete obj;
////    };

//    //init_test(new QsProjectTesting());
//    //init_test(new QsSpinRunTesting());
////    QsSpinRunTesting tst1;
////    status |=  QTest::qExec(&tst1,argc,argv);

//    status |=TestCollector::RunAllTests(argc,argv);



//    return  status;
}
