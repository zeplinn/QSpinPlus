#ifndef RUNEXPRESSION_H
#define RUNEXPRESSION_H
#include "Expression.h"
#include "IdentifierExpression.h"
#include "hpp/SpinAst.h"
#include "hpp/Priority.h"
class RunExpression:public Expression
{
    Priority* _priority;
    IdentifierExpression* _name;
    QList<Expression*> _arg_list;
public:
    explicit RunExpression(token_id tok,IdentifierExpression* name,
                           QList<Expression*> arg_list, Priority* priority, linenr lineno)
        : Expression(tok,lineno)
        ,_priority(priority)
        ,_name(name)
        ,_arg_list(arg_list)
    {
        _priority->setParent(this);
        for(auto arg: _arg_list)
            arg->setParent(this);
    }
};
#endif // RUNEXPRESSION_H
