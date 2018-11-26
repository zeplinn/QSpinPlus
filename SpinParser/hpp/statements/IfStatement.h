#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H
#include "Statement.h"
#include "Sequence.h"
class IfStatement: public Statement
{
    QList<Sequence*> _branches;

public:
    explicit IfStatement(QList<Sequence*> branches, linenr lineno)
        : Statement(lineno)
    ,_branches(branches)
    {
        for(auto b : _branches){
            b->setParent(this);
        }
    }
protected:
    QList<Sequence*>& branches(){return _branches;}
};

#endif // IFSTATEMENT_H
