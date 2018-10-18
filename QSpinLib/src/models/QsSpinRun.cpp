#include "qspin/models/QsSpinRun.h"


//QsSpinRun::QsSpinRun(QsSpinConfig &config,const QDir projectDir, const QString projectname)
//{
//    QString promelaFile = projectDir.absoluteFilePath(projectname);
//    buildDir = QDir(projectDir.absolutePath()+"bin/"+config.name());
//    if(!buildDir.exists())
//        buildDir.mkdir(buildDir.absolutePath());

//    //move file
//    QFile file(promelaFile);
//    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
//        throw QString("promelafile do not exist");
//    QTextStream ts(&file);
//    QFile dest(buildDir.absoluteFilePath("spin.pml"));

//    dest.write(ts.readAll().toLocal8Bit());
//    file.close();
//    dest.close();

//    // create ltlFile if acceptance
//    if(config.mode().value()== Arg::Accepance){
//        QFile ltlfile(buildDir.absoluteFilePath("ltl.txt"));
//        if(!ltlfile.open(QIODevice::WriteOnly))
//            throw QString("faild to create ltl file");

//        QString replace = config.ltl().toLocal8Bit().constData();
//        replace = replace.replace("\n"," ");
//        ltlfile.write(replace.toLocal8Bit());
//        ltlfile.close();
//    }
//    // generate build/runtime options;
//    spinOptions =  QStringList()<<"-a"<<"\"spin.pml\"";
//    gccOptions = defaultGccArgs(config);
//    gccOptions << Arg::val(Arg::DNFair,"2") << "pan.c" << "-o" << "pan";

//    // set runtime options
//#ifdef Q_OS_WIN
//    panOptions << "wsl";
//    panOptions << "spin";
//#endif
//    switch (config.mode().value()) {
//    case Arg::Accepance:
//        panOptions << Arg::val(Arg::Accepance);
//        break;
//    case Arg::Liveness:
//        panOptions << Arg::val(Arg::Liveness);
//        break;
//    case Arg::Safty: break;
//    default: throw QString("unkown verifymode");
//    };

//    if(config.searchDepth().value()>0)
//        panOptions <<Arg::val(Arg::SearchDepth
//                              ,QString::number(config.searchDepth().value()));
//    if(config.hashValue().value()>0)
//        panOptions <<Arg::val(Arg::HashSize
//                              ,QString::number(config.hashValue().value()));
//}

//void QsSpinRun::buildPan(const QString &path, QsSpinConfig &config){

//    QProcess p;
//    // build pan c file
//#ifdef Q_OS_WIN
//    p.start("powershell",spinOptions);
//#else
//    p.start("spin",spinOptions)
//        #endif
//            p.waitForFinished(-1);

//    if(p.isOpen())
//        p.close();

//    //build pan executable
//    //    QStringList args = defaultArgs(config);
//    //    args << Arg::val(Arg::DNFair,"2") << "pan.c" << "-o" << "pan";
//    p.start("powershell",gccOptions);
//    p.waitForFinished(-1);
//    if(p.isOpen())
//        p.close();


//    //QSharedPointer<QProcess> p(new QProcess());
//}

//verifyResult_ptr &QsSpinRun::run(){
//	QsSpinConfig config;
//	QProcess p;
//	//    QStringList args;
//	//#ifdef Q_OS_WIN
//	//    args << "wsl";
//	//    args << "spin";
//	//#endif
//	//    switch (config.verifyMode().value()) {
//	//    case Arg::Accepance:
//	//        args << Arg::val(Arg::Accepance);
//	//        break;
//	//    case Arg::Liveness:
//	//        args << Arg::val(Arg::Liveness);
//	//        break;
//	//    case Arg::Safty: break;
//	//    default: throw QString("unkown verifymode");
//	//    }
//#ifdef Q_OS_WIN
//	p.start("powershell",spinOptions);
//#else
//	p.start("spin",args);
//#endif
//	p.waitForFinished(-1);
//	if(p.isOpen())
//		p.close();
//}

void QsSpinRun::setArguments( QsSpinConfig &config, const QString &filename)
{
	spinOptions.clear();
	gccOptions.clear();
	panOptions.clear();
	// prefix arguments;
#ifdef Q_OS_WIN
	// wsl = generel windows command for any added linux subsystem
	//, directly in the path of where the process is opend
	// it removes the need of pathing difference between linux/ windows
	// as relative path only can be used proberly now
	spinOptions << "wsl" << "spin";
	gccOptions << "wsl" << "gcc";
	panOptions << "wsl" << "./pan";
#endif

	switch (config.mode().value()) {
	case Arg::Accepance:
		spinOptions << getLtlArguments(config);
		spinOptions << Arg::val(Arg::Verify) << filename;
		break;
	case Arg::Safty:
	case Arg::Liveness:
		spinOptions << Arg::val(Arg::Verify) << filename;
		break;
	case Arg::Simulation:
	case Arg::InterActive:
		qFatal(" simulation/interactive spin set arguments is missing implmentation");
		break;
	}

	// gcc options for verify only so far;
	switch (config.mode().value()) {
	case Arg::Safty:
	case Arg::Accepance:
	case Arg::Liveness:
		gccOptions << defaultGccArgs(config);
		break;
	case Arg::Simulation:
	case Arg::InterActive:
		qFatal("simulation/ interactive gcc arguments not yet implemted");
	}

	// set pan options

	switch (config.mode().value()) {
	case Arg::Safty:
		break;
	case Arg::Liveness:
		panOptions << Arg::val(Arg::Liveness);
		if(config.fairnes().value() == Arg::WeakFairness)
			panOptions << Arg::val(Arg::WeakFairness);
		break;
	case Arg::Accepance:
		panOptions << Arg::val(Arg::Accepance);
		if(config.fairnes().value()==Arg::WeakFairness)
			panOptions << Arg::val(Arg::WeakFairness);
	}

	if(config.searchDepth().value()>0)
		panOptions << Arg::val(Arg::SearchDepth,QString::number(config.searchDepth().value()));
	if(config.hashValue().value()>0)
		panOptions << Arg::val(Arg::HashSize,QString::number(config.hashValue().value()));

}

QStringList QsSpinRun::defaultGccArgs( QsSpinConfig &config){
	QStringList args;

#ifdef Q_OS_WIN
	args << "wsl";
	args << "gcc";
#endif

	switch (config.memoryCompression().value()) {
	case Arg::DCollapse:
		args << Arg::val(Arg::DCollapse); break;
	case Arg::DH4:
		args << Arg::val(Arg::DCollapse); break;
	default: break;
	}


	switch (config.mode().value()) {
	case Arg::Safty:
		args << Arg::val(Arg::DSafty);
		break;
	case Arg::Liveness:
		args << Arg::val(Arg::DNP);
		break;
	case Arg::Accepance:
		break;
	}

	if(config.searchBy().value() == Arg::BFS)
		args << Arg::val(Arg::BFS);
	return args;
}

QStringList QsSpinRun::getLtlArguments(QsSpinConfig &config){
	QString ltlName = config.name().replace(" ","_");
	QFile f("bin/"+ltlName+"/"+ltlName+".ltl");
	QFileInfo fInfo(f);
	if(!fInfo.dir().exists())
		fInfo.dir().mkdir(fInfo.dir().path());
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){

		throw QString("failed saving ltl file");
	}
	// no comment support in file so far
	f.write(config.ltl().replace("\n"," ").toLocal8Bit());// only first line of file will be scanned by spin
	f.close();
	// save ltl to file
	return QStringList()<< Arg::val(Arg::LTL)<<ltlName+".ltl";
}
