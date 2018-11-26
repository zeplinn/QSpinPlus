#ifndef PRIORITY_H
#define PRIORITY_H
#include "hpp/SpinAst.h"
#include "hpp/expressions/ConstantExpression.h"
class Priority: public SpinAst
{
    ConstantExpression* _constant;
public:
    Priority(ConstantExpression* constant, linenr lineno)
        :SpinAst(lineno)
    ,_constant(constant){}
};
#endif // PRIORITY_H
