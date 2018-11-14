#ifndef PRINTTOCONSOLE_H
#define PRINTTOCONSOLE_H
#include <QObject>
class PrintToConsole{
		QString _msg;

	public:
		explicit PrintToConsole(QString message):_msg(message){}
		QString message()const{return _msg;}
};

#endif // PRINTTOCONSOLE_H
