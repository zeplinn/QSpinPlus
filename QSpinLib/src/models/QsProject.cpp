#include "qspin/models/QsProject.h"

qsSpinConfig_ptr QsProject::makeNewConfig() const{
	return std::make_shared<QsSpinConfig>();
}

QsProject::QsProject(const QString name):_name(name)
{

}

void QsProject::read(const QJsonObject &obj){
	_promelaFile = QUrl(obj["pml"].toString(""));
	if(QFile::exists(_promelaFile.toLocalFile()))
		throw make_error_code(QsJsonErrc::InvalidPromelaFilePath);

	if(!obj["configs"].isArray()){
		throw make_error_code(QsJsonErrc::InvalidConfigFormat);
	}
	QJsonArray jconfigs = obj["configs"].toArray();

	_configs.clear();
	QHash<QString,char> nameclash;
	for(int i=0; i < jconfigs.count();i++){
		if(!jconfigs[i].isObject())
			throw make_error_code(QsJsonErrc::InvalidConfigFormat);
		QJsonObject aobj = jconfigs[i].toObject();
		auto item = makeNewConfig();
		item->read(aobj);
		if(nameclash.contains(item->name()))
			throw make_error_code(QsJsonErrc::InvalidConfigFormat);
		_configs << item;
	}


}

void QsProject::write(QJsonObject &obj) const{
	obj["pml"]=_promelaFile.fileName();
	QJsonArray configs;
	for (int i =0; i< _configs.count();i++){
		QJsonObject elem;
		_configs[i]->write(elem);
		configs.append(elem);
	}
	obj["configs"]=configs;
}

bool QsProject::open(QsProject &project, const QString fileDest){
	QFile savedFile(fileDest);
	if (!savedFile.open(QIODevice::ReadOnly)) {
		throw QString("Couldn't open file to open.");
	}

	// read text
	QByteArray txtDoc = savedFile.readAll();
	// convert to json format
	QJsonDocument jsonDoc = QJsonDocument::fromJson(txtDoc);
	if(!jsonDoc.isObject()){
		throw make_error_code(QsJsonErrc::InvalidJsonFormat);
		return false;
	}
	project.read(jsonDoc.object());
	QFileInfo fInfo(savedFile.fileName());
	project._projectDir =fInfo.absoluteDir();
	project._name = fInfo.baseName();
	QDir::setCurrent(fInfo.absoluteDir().path());
	savedFile.close();
	return true;
}

bool QsProject::saveAs(const QsProject &pro, const QString fileDest){
	qDebug()<<"save file name"<<fileDest;
	QFile saveFile(fileDest);

	QJsonObject project;
	pro.write(project);
	QJsonDocument saveDoc(project);

	if (!saveFile.open(QIODevice::WriteOnly)) {
		throw QString("Couldn't file to save file.");
	}
	QFileInfo fInfo(saveFile);
	QDir::setCurrent(fInfo.absoluteDir().path());
	saveFile.write(saveDoc.toJson());
	saveFile.close();

	return true;
}

int QsProject::configCount() const {return _configs.count();}

qsSpinConfig_ptr &QsProject::getConfiguration(int idx){
	return  _configs[idx];
}

bool QsProject::removeConfiguration(int idx){
	if(idx>=_configs.count()) return false;
	_configs.removeAt(idx);
	return true;
}

bool QsProject::addNewConfiguration(QString name){
	QListIterator<qsSpinConfig_ptr> itr(_configs);
	qsSpinConfig_ptr tmp;
	while(itr.hasNext()){
		tmp = itr.next();
		if(tmp->name()==name) return false;
	}
	_configs << std::make_shared<QsSpinConfig>(name);
	return true;
}

QDir &QsProject::projectDir(){ return _projectDir;}

QUrl &QsProject::promelaFile(){return _promelaFile;}

QString &QsProject::name(){return _name; }
