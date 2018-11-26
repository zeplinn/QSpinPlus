#ifndef SYMBOLEXPRESSION_H
#define SYMBOLEXPRESSION_H
#include "Expression.h"

class SymbolExpression:public Expression
{
public:
    SymbolExpression(token_id tok,linenr lineno):Expression(tok,lineno) {}
};
#endif // SYMBOLEXPRESSION_H
