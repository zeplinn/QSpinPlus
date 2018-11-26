#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "IExpression.h"
#include "hpp/statements/Statement.h"
#include "hpp/scanner/SpinConstants.h"
class Expression: public Statement{
    token_id _tok;
    // IExpression interface
public:
    explicit Expression(token_id tok,linenr lineno):Statement(lineno)
    {}
    token_id type()const{return  _tok;}

};

#endif // EXPRESSION_H
