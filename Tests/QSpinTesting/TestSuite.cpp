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

QJsonDocument TestSuite::openJsonDocument(const QString fn){
    QFile f(fn);
    if(!f.open(QIODevice::ReadOnly))
        throw QString("failed to open %1").arg(fn);
    QByteArray txtfile = f.readAll();

    QJsonDocument jdoc = QJsonDocument::fromJson(txtfile);
    if(!jdoc.isObject())
        throw QString("%1 document is not a json object").arg(fn);
    return jdoc;
}
