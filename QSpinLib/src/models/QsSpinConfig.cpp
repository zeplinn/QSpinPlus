#include "qspin/models/QsSpinConfig.h"

void QsSpinConfig::readVar(QsConfigVariable &var, QString key, const QJsonObject &obj,const QsJsonErrc err){
    if(!obj[key].isObject())
        throw make_error_code(err);
    QJsonObject vobj = obj[key].toObject();
    var.read(vobj);
}
namespace {
typedef QsConfigVariable::type_t _qst;
}
QsSpinConfig::QsSpinConfig(const QString configName):
    _name(configName),
    _mode(_qst::Mode,static_cast<int>(Arg::Safty)),
    _searchBy(_qst::SearchBy,static_cast<int>(Arg::DFS)),
    _fairnes(_qst::Fairnes,static_cast<int>(Arg::StrongFairnes)),
    _searchDepth(_qst::SearchDepth,10000),
    _hashValue(_qst::HashValue),
    _memoryCompression(_qst::MemoryCompression,static_cast<int>(Arg::None))
{}

QString QsSpinConfig::name() const{return _name;}

void QsSpinConfig::setName(const QString configName){ _name = configName;}

QString QsSpinConfig::ltl() const{ return _ltl;}

void QsSpinConfig::setLtl(QString value){_ltl= value;}

QsConfigVariable &QsSpinConfig::mode() {return _mode;}

QsConfigVariable &QsSpinConfig::searchBy(){    return  _searchBy; }

QsConfigVariable &QsSpinConfig::fairnes(){    return _fairnes;}

QsConfigVariable &QsSpinConfig::searchDepth(){    return _searchDepth;}

QsConfigVariable &QsSpinConfig::hashValue(){    return _hashValue;}

QsConfigVariable &QsSpinConfig::memoryCompression(){    return _memoryCompression;}

void QsSpinConfig::read(const QJsonObject &obj){
    if(!obj["name"].isString())
        throw make_error_code(QsJsonErrc::invalidConfigNameFormat);
    _name = obj["name"].toString();
    readVar(_mode,"mode",obj,QsJsonErrc::invalidVerifyModeFormat);
    readVar(_searchBy,"searchBy",obj,QsJsonErrc::InvalidSearchByFormat);
    readVar(_fairnes,"fairnes",obj,QsJsonErrc::InvalidFairnesFormat);
    readVar(_searchDepth,"searchDepth",obj,QsJsonErrc::InvalidSearchDepthFormat);
    readVar(_hashValue,"hashValue",obj,QsJsonErrc::InvalidHashValueFormat);
    readVar(_memoryCompression,"memoryCompression",obj,QsJsonErrc::InvalidMemoryComressionFormat);

    if(!obj["ltl"].isString())
        throw make_error_code(QsJsonErrc::invalidLtlFormat);
    _ltl = obj["ltl"].toString();
}

void QsSpinConfig::write(QJsonObject &obj) const {
    obj["name"] = _name;

    QJsonObject verifyMode,searchBy,fairnes,searchDepth,hashValue,memoryCompression;
    _mode.write(verifyMode);
    _searchBy.write(searchBy);
    _fairnes.write(fairnes);
    _searchDepth.write(searchDepth);
    _hashValue.write(hashValue);
    _memoryCompression.write(memoryCompression);

    obj["mode"]=verifyMode;
    obj["searchBy"] = searchBy;
    obj["fairnes"] = fairnes;
    obj["searchDepth"] = searchDepth;
    obj["hashValue"] = hashValue;
    obj["memoryCompression"] = memoryCompression;

    obj["ltl"] = _ltl;
}

QsConfigVariable::QsConfigVariable( type_t type,int value):_useLocal(true),_value(value),_type(type){}

void QsConfigVariable::read(const QJsonObject &obj){
    QJsonValue v = obj.value("useLocal");
    if(!v.isBool())
        throw make_error_code(QsJsonErrc::InvalidUseLocalVarFormat);
    _useLocal= v.toBool(true);

    v= obj.value("value");
    if (!v.isString()){
        if(v.toInt(-99)==-99) // no isInt exist
            throw make_error_code(QsJsonErrc::InvalidValueFormat);
        _value = v.toInt(-1);
    }
    else _value = Arg::toCode(v.toString());
}

void QsConfigVariable::write(QJsonObject &obj) const{
    obj["useLocal"]=_useLocal;
    switch (_type) {
    //string based
    case Mode:
    case SearchBy:
    case Fairnes:
    case MemoryCompression:
        obj["value"] = Arg::name(static_cast<Arg::Type>(value()));
        break;
        // int based
    case SearchDepth:
    case HashValue:
        obj["value"] = _value;
        break;
    }
}

bool QsConfigVariable::useLocal() const{return _useLocal;}

void QsConfigVariable::setUseLocal(const bool value){_useLocal=value;}

int QsConfigVariable::value() const{return _value;}

void QsConfigVariable::setValue(const int value){_value=value;}
