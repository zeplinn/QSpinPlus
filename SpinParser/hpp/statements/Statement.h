#ifndef STATEMENT_H
#define STATEMENT_H
#include "hpp/statements/IStatement.h"
#include "hpp/SpinAst.h"
class Statement: public SpinAst
{
    using SpinAst::SpinAst;

    // IStatement interface
public:
    virtual bool canExecute() const
    {
        return  false;
    }
    virtual Statement *getNext()
    {
        return  nullptr;
    }
};
#endif // STATEMENT_H
