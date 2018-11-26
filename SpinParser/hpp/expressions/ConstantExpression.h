#ifndef CONSTANT_H
#define CONSTANT_H
#include "Expression.h"
class ConstantExpression: public Expression
{
    int _constant;
public:
    ConstantExpression(token_id tok, int constant,linenr lineno):Expression(tok,lineno)
    ,_constant(constant){}
};
#endif // CONSTANT_H
