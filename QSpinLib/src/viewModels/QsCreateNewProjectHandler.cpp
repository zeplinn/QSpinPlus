//#include "qspin/viewModels/QsCreateNewProjectHandler.h"

//void QsCreateNewProjectHandler::updateCanAccept(){ emit canAcceptChanged(); }

//QString QsCreateNewProjectHandler::name() const{ return _name; }

//void QsCreateNewProjectHandler::setName(QString value){
//    if(isValidName(value)){
//        _name = value;
//        emit nameChanged();
//        emit isValidNameChanged();
//        updateCanAccept();
//    }
//}

//QString QsCreateNewProjectHandler::promelaPath() const{ return _promelaPath; }

//QString QsCreateNewProjectHandler::destination() const{ return _destination; }

//bool QsCreateNewProjectHandler::isValidName() const{ return isValidName(_name); }

//bool QsCreateNewProjectHandler::useExistingPml() const{ return _useExistingPml; }

//void QsCreateNewProjectHandler::setUseExistingPml(bool value){
//    if(_useExistingPml != value){
//        _useExistingPml = value;
//        emit useExistingPmlChanged();
//        updateCanAccept();
//    }
//}

//bool QsCreateNewProjectHandler::canAccept() const{
//    return isValidFolder()
//            && isValidName()
//            && (useExistingPml() ? isValidPromelaFile() : true);
//}

//bool QsCreateNewProjectHandler::isValidPromelaFile() const{
//    return QFileInfo::exists(_promelaPath) && !promelaPath().isEmpty();
//}

//bool QsCreateNewProjectHandler::isValidFolder() const{
//    return QDir(_destination).exists() && ! destination().isEmpty();
//                                                     }

//void QsCreateNewProjectHandler::setPromelaPath(QUrl value){
//    if(_promelaPath != value.toLocalFile()){
//        _promelaPath = value.toLocalFile();
//        emit promelaPathChanged();
//        emit isValidPromelaFileChanged();
//        updateCanAccept();
//    }
//}

//void QsCreateNewProjectHandler::setDestination(QString value){
//    _destination = value;

//        updateCanAccept();

//}

//bool QsCreateNewProjectHandler::isValidName(QString name){
//    return qs().isValidFileName(name);
//}

//QsCreateNewProjectHandler::QsCreateNewProjectHandler(QObject *parent, EventAggregator *msg):QObjectBase(parent,msg) {}

//QsCreateNewProjectHandler::~QsCreateNewProjectHandler() {}
