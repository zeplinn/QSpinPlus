#ifndef CONDITIONALEXPRESSION_H
#define CONDITIONALEXPRESSION_H
#include "Expression.h"
#include "BinaryExpression.h"
class ConditionalExpression: public BinaryExpression
{
    Expression* _condition;
public:
    ConditionalExpression(Expression* condition, Expression* true_expr, Expression* false_expr,linenr lineno)
        :BinaryExpression (pml_tokens::Nothing_,true_expr,false_expr,lineno)
    , _condition(condition){
        condition->setParent(this);
    }
};
#endif // CONDITIONALEXPRESSION_H
