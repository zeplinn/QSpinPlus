#include "ColorSchemeSerialzationTests.h"


namespace  {
ColorSchemeSerialzationTests __T;
static constexpr jsonQspinPlusSchemeIds propIds;

void isValidStyleScheme(IQJsonSerialization& style,const QString fn,const char groupId[]){
    //const QString fn("qrc:/colorScheme/buttonStyle.scheme");
    QJsonDocument jdoc(TestSuite::openJsonDocument(fn));
    if(!jdoc.isObject())
        throw QString("%1 json document is not an object");
    QJsonObject jobj = jdoc.object(); // root
    jobj = jobj[groupId].toObject();
    auto errMsg = QString("%1: not a valid json format: %2").arg(fn).arg(groupId).toLocal8Bit();
    QVERIFY2(style.isValidJsonObject(jobj),errMsg);
}
}



void ColorSchemeSerialzationTests::isValidButtonStyleScheme(){
    TestSuite::safeTest([](){
        ButtonStyle style;
        ::isValidStyleScheme(style,":/test/files/colorscheme/buttonStyle.scheme",propIds.button);
    });
}

void ColorSchemeSerialzationTests::isValidGeneralStyleScheme(){
    TestSuite::safeTest([](){
        GeneralStyle style;
        ::isValidStyleScheme(style,":/test/files/colorscheme/generalStyle.scheme",propIds.general);
    });
}
void ColorSchemeSerialzationTests::isValidSpinBoxStyleScheme(){
    TestSuite::safeTest([](){
        SpinBoxStyle style;
        ::isValidStyleScheme(style,":/test/files/colorscheme/spinboxStyle.scheme",propIds.spinbox);
    });
}
void ColorSchemeSerialzationTests::isValidComboBoxStyleScheme(){
    TestSuite::safeTest([](){
        ComboBoxStyle style;
        ::isValidStyleScheme(style,":/test/files/colorscheme/comboboxStyle.scheme",propIds.combobox);
    });
}
