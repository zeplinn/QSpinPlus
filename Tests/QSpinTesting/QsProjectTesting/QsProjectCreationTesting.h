#ifndef QSPROJECTCREATIONTESTING_H
#define QSPROJECTCREATIONTESTING_H

#include <QObject>
#include <QDir>
#include <QtTest>

#include "qspin/viewModels/QSpinMain.h"
#include "TestSuite.h"
#include "qspin/models/QsProject.h"
#include "qspin/viewModels/EventAggregator.h"

class QsProjectCreationTesting : public TestSuite
{
		Q_OBJECT
	public:
		using TestSuite::TestSuite;

	signals:

	private slots:
		void test_createNewProject();
};

#endif // QSPROJECTCREATIONTESTING_H
