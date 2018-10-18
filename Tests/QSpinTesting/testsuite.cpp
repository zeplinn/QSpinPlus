#include "TestSuite.h"

TestSuite::TestSuite(){
	tests().push_back(this);
}

QLinkedList<TestSuite*>& TestSuite::tests(){
	static QLinkedList <TestSuite*> t;
	return  t;
}

void TestSuite::safeTest(const std::function<void ()>&body){
	try {
		body();
	} catch (QString msg) {
		QVERIFY2(false,QString("error: %1").arg(msg).toLocal8Bit().constData());
	}
	catch(const std::error_code e){
		QVERIFY2(false,QString("%1 %2:\t%3")
				 .arg(e.category().name())
				 .arg(e.value())
				 .arg(e.message().c_str())
				 .toLocal8Bit().constData());
	}
}
