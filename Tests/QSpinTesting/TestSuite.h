
/* BASED ON
 * http://qtcreator.blogspot.de/2009/10/running-multiple-unit-tests.html
 */
#ifndef TESTCOLLECTOR_H
#define TESTCOLLECTOR_H

#include <QtTest>
#include <QFile>
#include <functional>
#include "qspin/qsErrors.h"
#include <system_error>
#include <QLinkedList>
//namespace TestCollector{
//typedef std::map<std::string, std::shared_ptr<QObject> > TestList;
//inline TestList& GetTestList()
//{
//   static TestList list;
//   return list;
//}

//inline int RunAllTests(int argc, char **argv) {
//	int result = 0;
//	for (const auto&i:GetTestList()) {
//		QTEST_SET_MAIN_SOURCE_PATH
//		result |= QTest::qExec(i.second.get(), argc, argv);
//	}
//	return result;
//}


//template <class T>
//class UnitTestClass {
//public:
//	UnitTestClass(const std::string& pTestName) {
//		auto& testList = TestCollector::GetTestList();
//		if (0==testList.count(pTestName)) {
//			testList.insert(std::make_pair(pTestName, std::make_shared<T>()));
//		}
//	}
//};
//}

//#define ADD_TEST(className) static TestCollector::UnitTestClass<className> \
//	className ##_test_suite_object (#className);
//class QsHelper{
//public:
//	static QString loadFileToString(const QString relPath){

//		QFile file(relPath);
//		if(!file.open(QIODevice::ReadOnly)){
//			throw QString("couldent open file: qrc:%1").arg(relPath);
//			return QString();
//		}
//		QTextStream ts(&file);
//		QString str = ts.readAll();
//		file.close();
//		return  str;
//	}

//	static void safeTest(const std::function<void()>& body){
//		try {
//			body();
//		} catch (QString msg) {
//			QVERIFY2(false,QString("error: %1").arg(msg).toLocal8Bit().constData());
//		}
//		catch(const std::error_code e){
//			QVERIFY2(false,QString("%1 %2:\t%3")
//					 .arg(e.category().name())
//					 .arg(e.value())
//					 .arg(e.message().c_str())
//					 .toLocal8Bit().constData());
//		}
//	}
//};
class TestSuite: public QObject{
		Q_OBJECT
	public:
		TestSuite();
		static QLinkedList<TestSuite*>&tests();
	protected:
		void safeTest(const std::function<void()>& body);
};

#endif // TESTCOLLECTOR_H
