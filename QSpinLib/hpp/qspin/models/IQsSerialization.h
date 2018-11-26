#ifndef IQSSERIALIZATION_H
#define IQSSERIALIZATION_H
#include <QJsonObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMetaType>
#include <QObject>
// obselete and is to be removed
class IQsSerialization{
public:
    virtual ~IQsSerialization(){}
    virtual void read(const QJsonObject& obj)=0;
    virtual void write(QJsonObject& obj)const=0;
};
class IQJsonSerialization{
public:
    virtual ~IQJsonSerialization(){}
    virtual void read(const QJsonObject& obj)=0;
    virtual void write(QJsonObject& obj)const=0;
    virtual bool isValidJsonObject(QJsonObject& obj)=0;
};
class IQXmlSerialization{
public:
    virtual ~IQXmlSerialization(){}
    virtual void read(QXmlStreamReader& xml)=0;
    virtual void write(QXmlStreamWriter& xml)=0;
};
Q_DECLARE_INTERFACE(IQJsonSerialization,"qsp.IQJsonSerialization/1.0")

#endif // IQSSERIALIZATION_H
