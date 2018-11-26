#ifndef IDENTIFIEREXPRESSION_H
#define IDENTIFIEREXPRESSION_H
#include "Expression.h"
class IdentifierExpression:public Expression
{
    QString _id;
public:
    explicit IdentifierExpression(token_id tok,QString id,linenr lineno)
        :Expression(tok,lineno)
    ,_id(id){}
    QString identifier()const {return _id;}

};
#endif // IDENTIFIEREXPRESSION_H
