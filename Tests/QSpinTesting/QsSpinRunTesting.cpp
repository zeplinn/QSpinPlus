//#include "QsSpinRunTesting.h"

//QsSpinRunTesting::QsSpinRunTesting(QObject *parent) : QObject(parent)
//{

//}
//// only tests for one case more variations should be added later.
//void QsSpinRunTesting::test_init_spin_result_to_object(){
//	int a =0;
//	a=1;
//	safeTest([](){
//		QsProject project;
//		//QDir d("qrc:test/files/spin");
//		QsProject::open(project,":test/files/spin/simple.json");
//		qDebug()<< QDir::current().path();
//		QString xml = QsHelper::loadFileToString(":test/files/spin/mutual_peterson_result.xml");
//		if(xml.isEmpty())
//			throw QString("file is empty");
//		QXmlStreamReader reader(xml);
//		QStringList items;
//		while (reader.readNextStartElement()) {
//			while (reader.readNextStartElement()) {
//				items<<reader.readElementText();
//			}
//		}
//		QJsonDocument jDoc = QJsonDocument::fromJson(items[1].toUtf8());
//		if(!jDoc.isObject())
//			throw QString("json document is not an object");
//		QJsonObject jobj = jDoc.object();

//		QsVerificationResults results(items[0]);

//		QCOMPARE(results.fullStatespaceFor().partialOrderReduction,jobj["partialOrderReduction"].toBool());
//		QCOMPARE(results.fullStatespaceFor().neverClaim,jobj["neverClaim"].toBool());
//		QCOMPARE(results.fullStatespaceFor().assertionViolations,jobj["assertionViolations"].toBool());
//		QCOMPARE(results.fullStatespaceFor().acceptanceCycles,jobj["acceptanceCycles"].toBool());
//		QCOMPARE(results.fullStatespaceFor().invalidEndStates,jobj["invalidEndStates"].toBool());

//		QCOMPARE(results.fullStatespaceSpecifications().depthReached,jobj["depthReached"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().storedStates,jobj["storedStates"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().matchedStates,jobj["matchedStates"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().transitionsTaken,jobj["transitionsTaken"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().atomicSteps,jobj["atomicSteps"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().stateSize,jobj["stateSize"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().hashConflicts,jobj["hashConflicts"].toDouble(-1));
//		QCOMPARE(results.fullStatespaceSpecifications().hashSize,jobj["hashSize"].toDouble(-1));

//		QCOMPARE(results.memoryUsage().forStates,jobj["forStates"].toDouble(-1));
//		QCOMPARE(results.memoryUsage().forHashTable,jobj["forHashTable"].toDouble(-1));
//		QCOMPARE(results.memoryUsage().forSearchStack,jobj["stackFor"].toDouble(-1));
//		QCOMPARE(results.memoryUsage().inTotal,jobj["inTotal"].toDouble(-1));


//	});
//}



//void QsSpinRunTesting::test_spin_verification_run(){
//	QsHelper::safeTest([](){
//		QsProject p;
//		//QDir tmp = QDir::current();
//		QsProject::open(p,":test/files/spin/simple.json");

//		QsSpinRun spin;
//		qsSpinConfig_ptr& config = p.getConfiguration(0);
//		config->runSpin();

//		verifyResult_ptr r = spin.result();
//	});

//}



