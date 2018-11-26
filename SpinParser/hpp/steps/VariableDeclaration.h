#ifndef DECLLST_H
#define DECLLST_H
#include <QObject>
#include <QHash>
#include "hpp/statements/Statement.h"
#include "hpp/expressions/Expression.h"
class IVariable{
public:
    virtual ~IVariable(){}
    virtual QString identifier()const=0;
};

class VariableDeclaration: public Statement, public IVariable{
    int _visibility=0;
    QString _name;
    Expression* _rhs=nullptr;
public:
    explicit VariableDeclaration(int visibility,QString name,Expression* rhs,linenr lineno):Statement(lineno)
      ,_visibility(visibility),_name(name), _rhs(rhs){}

    // IVariable interface
public:
    virtual QString identifier() const override
    {
        return _name;
    }
};

#endif // DECLLST_H
