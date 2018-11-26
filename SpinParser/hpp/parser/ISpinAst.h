#ifndef ISPINAST_H
#define ISPINAST_H
#include "hpp/scanner/SpinScanner.h"
class ISpinAst{

public:
    virtual ~ISpinAst(){}

    virtual linenr line()const=0;
};

#endif // ISPINAST_H
