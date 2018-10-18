#include "QsProjectCreationTesting.h"

static QsProjectCreationTesting PROJECT_CREATION_TESTING;

void QsProjectCreationTesting::test_createNewProject(){
	safeTest([](){
		EventAggregator msg_service;
		QSpinMain app(nullptr,&msg_service);
		QDir d = QDir::current();
		QString projectName ="Create new project";
		qsProject_ptr project = app.createNewProject(projectName,d.path());
		d = QDir(d.path()+"/"+projectName);
		QVERIFY2(!project,"Project is null");
		QVERIFY2(d.exists(),"ProjectDir exists");
		if(d.exists())
			d.rmdir(d.path());

	});
}
