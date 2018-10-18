#ifndef IQSSERIALIZATION_H
#define IQSSERIALIZATION_H
#include <QJsonObject>
class IQsSerialization{
	public:
		virtual ~IQsSerialization(){}
		virtual void read(const QJsonObject& obj)=0;
		virtual void write(QJsonObject& obj)const=0;
};

#endif // IQSSERIALIZATION_H
