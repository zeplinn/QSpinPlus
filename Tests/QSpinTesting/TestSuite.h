
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

class TestSuite: public QObject{
		Q_OBJECT
	public:
		TestSuite();
		static QLinkedList<TestSuite*>&tests();
        static QJsonDocument openJsonDocument(const QString fn);
        static void safeTest(const std::function<void()>& body);
	protected:
};

#endif // TESTCOLLECTOR_H
