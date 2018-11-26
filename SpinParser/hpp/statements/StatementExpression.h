#ifndef STATEMENTEXPRESSION_H
#define STATEMENTEXPRESSION_H
#include "hpp/statements/Statement.h"
#include "hpp/expressions/IExpression.h"
#include "hpp/expressions/Expression.h"
#include "hpp/ILhs.h"
class StatementExpression: public Expression,public ILhs
{
    Expression* _lhs;
public:
    StatementExpression(Expression* lhs,linenr lineno):Expression (lhs->type(),lineno),_lhs(lhs) {}

    // IExpression interface
public:
    virtual Expression *lhs()const override
    {
        return _lhs;
    }

};
#endif // STATEMENTEXPRESSION_H
