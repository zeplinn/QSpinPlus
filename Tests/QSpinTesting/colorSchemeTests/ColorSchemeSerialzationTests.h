#ifndef COLORSCHEMETESTS_H
#define COLORSCHEMETESTS_H

#include <QObject>
#include <QtTest>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>
#include "TestSuite.h"
#include "qspin/viewModels/QsStyle.h"
#include "qspin/models/IQsSerialization.h"
class ColorSchemeSerialzationTests : public TestSuite
{
    Q_OBJECT

public:
    using TestSuite::TestSuite;

signals:

private slots:
   // void test_openIsValidStyleScheme_data();
    void isValidButtonStyleScheme();
    void isValidGeneralStyleScheme();
    void isValidSpinBoxStyleScheme();
    void isValidComboBoxStyleScheme();
};

#endif // COLORSCHEMETESTS_H
