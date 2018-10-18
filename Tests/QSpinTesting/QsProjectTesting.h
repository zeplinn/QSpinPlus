//#ifndef QSPROJECTTESTING_H
//#define QSPROJECTTESTING_H
//#include <QtTest>
//#include <QObject>
//#include "TestSuite.h"
//#include "qspin/models/QsProject.h"
//#include "qspin/models/QsSpinConfig.h"
//class QsProjectTesting: public QObject
//{
//	Q_OBJECT
//public:
//	explicit QsProjectTesting(QObject* parent=nullptr);
//	~QsProjectTesting(){}

//private slots:
//	void test_addConfigurations();
//	void test_saveConfiguration(){



//	}
//	void test_removeConfigurations(){}
//	void test_saveProject(){
//		QsHelper::safeTest([](){

//			// prepare save file;
//			QString f = "tst_saveConfig.json";

//			QsProject pro;
//			pro.addNewConfiguration("testConfig");
//			QVERIFY2( QsProject::saveAs(pro,f),"project saved succesfully");

//			QFile file(f);
//			QVERIFY2(file.exists(),"saved file exist on disk, at expected location");

//			QVERIFY2(file.remove(),"test file failed to be deleted at end");
//		});

//	}
//	void test_open_testProject(){
//		QsHelper::safeTest([](){

//			// prepare save file;
//			QString f = "tst_openConfig.json";

//			QsProject saveproInstance;
//			saveproInstance.addNewConfiguration("testConfig");
//			QVERIFY2( QsProject::saveAs(saveproInstance,f),"project saved succesfully");

//			QsProject openedProInstance;
//			QsProject::open(openedProInstance,f);
//			QCOMPARE(openedProInstance.getConfiguration(0)->name()
//					 ,saveproInstance.getConfiguration(0)->name());

//		});
//	}
//};
//ADD_TEST(QsProjectTesting)
//#endif // QSPROJECTTESTING_H
