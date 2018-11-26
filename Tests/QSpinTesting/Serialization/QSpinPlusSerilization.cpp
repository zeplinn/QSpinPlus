#include "QSpinPlusSerilization.h"


namespace  {
static QSpinPlusSerilization ___TEST;
}

void QSpinPlusSerilization::readItemConfiguration(){
    safeTest([](){

        // checked is true enabled is false, command is safetyMode
        QFile f(":/test/files/QSpinPlusSerialization/ItemConfiguration.xml");
        f.open(QIODevice::ReadOnly);
        auto ic = new ItemConfiguration(Arg::SafetyMode);

        QXmlStreamReader reader(&f);
        if(reader.readNextStartElement()){
            ic->read(reader);
            f.close();
            QCOMPARE(ic->checked(),true);
            QCOMPARE(ic->enabled(),false);

        }else QVERIFY2(false,"failed to read first element");
    });
}

void QSpinPlusSerilization::writeItemConfiguration(){
    safeTest([](){

        QFile f("itemconfig.xml");
        QVERIFY2(f.open(QIODevice::WriteOnly | QIODevice::Text), "failed to open file");
        auto ic = new ItemConfiguration(Arg::SafetyMode);
        ic->setChecked(true);
        QXmlStreamWriter writer(&f);
        writer.setAutoFormatting(true);
        //writer.writeStartDocument();
        ic->write(writer);
        //writer.writeEndDocument();
        f.close();
        QVERIFY(QFile::exists("itemconfig.xml"));
        f.remove("itemconfig.xml");
    });



}

void QSpinPlusSerilization::readItemValueConfiguration(){
    safeTest([](){

        // checked is true enabled is false, command is searchDepth, commandvalue = 10
        QFile f(":/test/files/QSpinPlusSerialization/ItemValueConfiguration.xml");
        QVERIFY2(f.open(QIODevice::ReadOnly),"faild to open file");
        auto ic = new ItemValueConfiguration(Arg::SearchDepth,-2,0,10);

        QXmlStreamReader reader(&f);
        if(reader.readNextStartElement()){
            ic->read(reader);
            f.close();
            QCOMPARE(ic->checked(),true);
            QCOMPARE(ic->enabled(),false);
            QCOMPARE(ic->commandValue(),10);

        }else QVERIFY2(false,"failed to read first element");
    });
}

void QSpinPlusSerilization::writeValueConfiguration(){
    safeTest([](){
        QFile f("itemvalconfig.xml");
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        auto ic = new ItemValueConfiguration(Arg::SearchDepth,10,0,10);
        ic->setChecked(true);
        QXmlStreamWriter writer(&f);
        writer.setAutoFormatting(true);
        //writer.writeStartDocument();
        ic->write(writer);
        //writer.writeEndDocument();
        f.close();
        QVERIFY(QFile::exists("itemvalconfig.xml"));
        f.remove("itemvalconfig.xml");
    });
}

void QSpinPlusSerilization::readVerificationConfiguration(){
    safeTest([](){

        // item configurations checked / enabled is by default false
        // file is based on writeConfiguration test
        // progress mode is enabled
        // weak fairnes checked
        // safety checked but is not enabled
        QFile f(":/test/files/QSpinPlusSerialization/VerificationConfiguration.xml");
        f.open(QIODevice::ReadOnly);
        auto ic = new VerificationConfiguration();

        QXmlStreamReader reader(&f);
        if(reader.readNextStartElement()){
            if(reader.name()!= "VerificationConfiguration")
                throw QString("invalid out xml object: %1").arg(reader.name());
            ic->read(reader);
            f.close();
            QCOMPARE(ic->safety()->checked(),true);
            QCOMPARE(ic->safety()->enabled(),false);
            QCOMPARE(ic->weakFairness()->checked(),true);
            QCOMPARE(ic->weakFairness()->enabled(),true);
            QCOMPARE(ic->progressMode()->checked(),true);
            QCOMPARE(ic->progressMode()->enabled(),true);

        }else QVERIFY2(false,"failed to read first element");
    });

}

void QSpinPlusSerilization::writeVerificationCOnfiguration(){
    safeTest([](){
        QFile f("verifyconfig.xml");
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        auto vc = new VerificationConfiguration();
        //vc->safetyMode()->setChecked(true);
        vc->updateConfigurations();
        vc->safety()->setChecked(true);
        vc->progressMode()->setChecked(true);
        vc->weakFairness()->setChecked(true);
        vc->updateConfigurations();
        QXmlStreamWriter writer(&f);
        writer.setAutoFormatting(true);
        //writer.writeStartDocument();
        vc->write(writer);
        //writer.writeEndDocument();
        f.close();
        QVERIFY(QFile::exists("verifyconfig.xml"));
        //f.remove("verifyconfig.xml");
    });
}
