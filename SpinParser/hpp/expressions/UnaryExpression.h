#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H
#include "Expression.h"
#include "hpp/ILhs.h"
class UnaryExpression: public Expression, public ILhs{


    Expression* _lhs;
public:
    explicit UnaryExpression(token_id tok,Expression* lhs,linenr lineno)
        :Expression(tok,lineno)
    ,_lhs(lhs)
    {
        _lhs->setParent(this);
    }
    virtual Expression *lhs() const override
    {
        return _lhs;
    }
};

#endif // UNARYEXPRESSION_H
