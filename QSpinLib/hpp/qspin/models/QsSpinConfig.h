#ifndef QSSPINCONFIG_H
#define QSSPINCONFIG_H
#include "qspin/models/IQsSerialization.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <memory>
#include <qspin/qsErrors.h>
#include <QDebug>
#include "qspin/models/Arg.h"
#include <QUuid>
class QsConfigVariable: public IQsSerialization{
	bool _useLocal;
	int _value;
	// arguments Arg::safty
public:
enum type_t{
	Mode,
	SearchBy,
	Fairnes,
	SearchDepth,
	HashValue,
	MemoryCompression
};
	explicit QsConfigVariable(type_t type , int value =0);
	void read(const QJsonObject& obj) override;
	void write(QJsonObject& obj)const override;
	bool useLocal()const;
	void setUseLocal(const bool value);

	int value()const;
	void setValue(const int value);
private:
	type_t _type;
};

class QsSpinConfig: public IQsSerialization{
	QString _name;
	QsConfigVariable _mode;
	QsConfigVariable _searchBy;
	QsConfigVariable _fairnes;
	QsConfigVariable _searchDepth;
	QsConfigVariable _hashValue;
	QsConfigVariable _memoryCompression;
	QString _ltl;
	// potenial inline function
	static void readVar(QsConfigVariable& var, QString key, const QJsonObject& obj, const QsJsonErrc err);
public:
	enum params{
		SaftyVerification,
		AcceptanceVerification,
		LivenesVerification
	};
	explicit QsSpinConfig(const QString configName="Unnamed");
	QString name()const;
	void setName(const QString configName);

	QString ltl()const;
	void setLtl(QString value);
	QsConfigVariable& mode();
	QsConfigVariable& searchBy();
	QsConfigVariable& fairnes();
	QsConfigVariable& searchDepth();
	QsConfigVariable& hashValue();
	QsConfigVariable& memoryCompression();

	void read(const QJsonObject& obj) override;

	void write(QJsonObject& obj)const override;

	void runSpin(){

	}



};
typedef  std::shared_ptr<QsSpinConfig> qsSpinConfig_ptr;
#endif // QSSPINCONFIG_H
