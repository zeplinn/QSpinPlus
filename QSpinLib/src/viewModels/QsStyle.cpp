#include "qspin/viewModels/QsStyle.h"

ButtonStyle *QsStyle::button() const{return _colorScheme->button();}

SpinBoxStyle *QsStyle::spinbox() const{return _colorScheme->spinbox();}

ComboBoxStyle *QsStyle::combobox() const{return _colorScheme->combobox();}

GeneralStyle *QsStyle::general() const{return _colorScheme->general();}

PromelaEditor *QsStyle::promelaEditor() const{ return _colorScheme->promelaEditor();}



void QsStyle::registerAsQml(){
    qmlRegisterUncreatableType<QsStyle>(QsImpports::cppItems(),1,0,"QsStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<ButtonStyle>(QsImpports::cppItems(),1,0,"ButtonStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<GeneralStyle>(QsImpports::cppItems(),1,0,"GeneralStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<ComboBoxStyle>(QsImpports::cppItems(),1,0,"ComboBoxStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<SpinBoxStyle>(QsImpports::cppItems(),1,0,"SpinBoxStyle","no Instance of style object allowed");
    qmlRegisterUncreatableType<PromelaEditor>(QsImpports::cppItems(),1,0,"PromelaEditor","no Instance of style object allowed");
    //qmlRegisterUncreatableType<PromelaTextHighlighter>(QsImpports::cppItems(),1,0,"PromelaTextHighlighter","no Instance of style object allowed");

}


QsStyle*QsStyle::qmlAttachedProperties(QObject*parent){
    return new QsStyle(parent,nullptr);
}

