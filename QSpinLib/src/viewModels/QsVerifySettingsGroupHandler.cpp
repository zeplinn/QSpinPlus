#include "qspin/viewModels/QsVerifySettingsGroupHandler.h"

VerificationConfiguration *QsVerifySettingsGroupHandler::item() const{return !_item.isNull() ? _item.data() :_default_item;}

VerificationConfiguration *QsVerifySettingsGroupHandler::reference() const{return _ref;}

void QsVerifySettingsGroupHandler::setReference(VerificationConfiguration *value){

        auto old_ref= _ref;
        _ref = value;
        emit referenceChanged();
        setItem(value);
        if(ltlEditorHandler()!=nullptr){
            if(!old_ref.isNull()){
                old_ref->ltl()->setDocument(ltlEditorHandler()->text());
            }
            if(!_ref.isNull()){
                auto ltl = _ref->ltl();
                auto cmd = ltl->command();
                QString str = ltl->document();
                ltlEditorHandler()->setText(str);

            }
        }
}

QsCodeEditorHandler *QsVerifySettingsGroupHandler::ltlEditorHandler() const{ return _ltlEditorHandler; }

void QsVerifySettingsGroupHandler::setLtlEditorHandler(QsCodeEditorHandler *value){
    if(_ltlEditorHandler != value){
        _ltlEditorHandler = value;
        emit ltlEditorHandlerChanged();
    }
}

bool QsVerifySettingsGroupHandler::isEditable() const{ return _isEditable; }

void QsVerifySettingsGroupHandler::setIsEditable(bool value){
    if(_isEditable != value){
        _isEditable = value;
        emit isEditableChanged();
    }
}

QsVerifySettingsGroupHandler::QsVerifySettingsGroupHandler(QObject *parent, EventAggregator *msg)
    :QObjectBase (parent,msg)
    ,_default_item(new VerificationConfiguration(this,msg))
    ,_item(nullptr)
    ,_ref(nullptr)
    ,_ltlEditorHandler(nullptr)
    ,_isEditable(false)
{

}

void QsVerifySettingsGroupHandler::setItem(VerificationConfiguration *value){
    _item = value;
    emit itemChanged();
    if(_item !=nullptr) setIsEditable(true);
    else setIsEditable(false);

}

QString QsVerifySettingsGroupHandler::isValidLtlName(QString name){
    QFile f(name+".ltl");
    if(f.exists()){
        return qs().readTextFile(f.fileName());
    }
    qs().writeTextFile("",f.fileName());
    return "true";
}
