#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H
#include "IExpression.h"
#include "IBinaryExpression.h"
#include "Expression.h"
#include "UnaryExpression.h"
#include "hpp/scanner/SpinConstants.h"
#include "hpp/IRhs.h"

class BinaryExpression: public UnaryExpression, public IRhs{


    // IBinaryExpression interface
    Expression* _rhs;
public:
    explicit BinaryExpression(token_id tok,Expression* lhs, Expression* rhs,linenr lineno):UnaryExpression(tok,lhs,lineno)
      ,_rhs(rhs){
        _rhs->setParent(this);
    }
    virtual Expression *rhs() const override
    {
        return _rhs;
    }
};

#endif // BINARYEXPRESSION_H
