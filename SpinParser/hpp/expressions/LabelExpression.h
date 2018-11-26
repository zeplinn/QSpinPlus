#ifndef LABELEXPRESSION_H
#define LABELEXPRESSION_H
#include "hpp/statements/Statement.h"
#include "Expression.h"
#include "IdentifierExpression.h"
class LabelExpression:public Expression
{
    Expression* _label; // identifier expression
    Statement * _statement;
public:
    explicit LabelExpression(Expression* label,Statement* stmnt,linenr lineno)
        :Expression(pml_tokens::Nothing_,lineno)
    ,_label(label)
        ,_statement(stmnt)
    {
        _label->setParent(this);
    }
};
#endif // LABELEXPRESSION_H
