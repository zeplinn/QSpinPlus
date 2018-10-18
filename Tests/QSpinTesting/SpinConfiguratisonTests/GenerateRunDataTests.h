#ifndef GENERATERUNDATATESTS_H
#define GENERATERUNDATATESTS_H

#include <QObject>
#include "TestSuite.h"
#include "qspin/models/QsSpinConfig.h"
#include "qspin/models/Arg.h"
#include <QUuid>
class GenerateRunDataTests : public TestSuite
{
		Q_OBJECT
	public:
		using TestSuite::TestSuite;

	signals:

	private slots:
		void test_generateVerificationOutput(){
			QsSpinConfig config;
			config.mode().setValue(Arg::Safty);

			//QUuid key = config.generateOutput();

		}
};

#endif // GENERATERUNDATATESTS_H
