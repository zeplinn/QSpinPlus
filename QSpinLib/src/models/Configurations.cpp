#include "qspin/models/Configurations.h"

VerificationConfiguration *Configurations::currentItem() const{ return _currentItem; }

int Configurations::currentIndex() const{ return _currentIndex; }

void Configurations::setCurrentIndex(int value){
    if(_currentIndex != value){
        _currentIndex = value;
        if(value>=0)    _currentItem = _configurations[value];
        else            _currentItem = nullptr;
        emit currentIndexChanged();
        emit currentItemChanged();
    }
}

//Configurations::Configurations(QObject *parent):QObject(parent){}


void Configurations::append(VerificationConfiguration *item){
    if(item != nullptr){
        _configurations<< item;
        item->setParent(this);

    }
}

void Configurations::removeAt(int index){
    if(index < 0 || index >= _configurations.count() ) return;

    auto at =_configurations.takeAt(index);
    at->deleteLater();
}

int Configurations::itemAt(VerificationConfiguration *item) const{
    return _configurations.indexOf(item);
}




void Configurations::read(QXmlStreamReader &xml){
    if(xml.name()== "Configurations"){
        while (xml.readNextStartElement()) {
            if(xml.name() == typeid(VerificationConfiguration).name()){

                auto vc = new VerificationConfiguration();
                vc->read(xml);
                append(vc);
            }
            else{
                // notify of illegal object
            }
        }
    }
}

void Configurations::write(QXmlStreamWriter &xml){
    xml.writeStartElement("Configurations");
    for( auto vc : _configurations)
        vc->write(xml);
    xml.writeEndElement();
}
