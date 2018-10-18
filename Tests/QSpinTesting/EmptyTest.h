#ifndef EMPTYTEST_H
#define EMPTYTEST_H
#include <QtTest>
#include <QObject>
class EmptyTest: public QObject{
    Q_OBJECT
public:
    explicit EmptyTest(QObject* parent = nullptr):QObject(parent){}
private slots:
    void test_dummy(){
        QVERIFY(true);
    }
};

#endif // EMPTYTEST_H
