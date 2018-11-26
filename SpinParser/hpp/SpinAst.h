#ifndef SPINAST_H
#define SPINAST_H
#include <QObject>
#include "hpp/parser/ISpinAst.h"
class SpinAst : public QObject, public ISpinAst
{
    Q_OBJECT
    linenr _lineno;
public:
    explicit SpinAst(linenr lineno):QObject(nullptr),_lineno(lineno) {}


    // ISpinAst interface
public:
    virtual linenr line() const override
    {
        return _lineno;
    }
public:
    size_t hashCode()const{

        return  typeid (this).hash_code();}
};
#endif // SPINAST_H
