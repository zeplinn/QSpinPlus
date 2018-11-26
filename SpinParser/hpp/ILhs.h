#ifndef ILHS_H
#define ILHS_H
#include "hpp/expressions/Expression.h"
class ILhs{
public:
    virtual ~ILhs(){}
    virtual Expression* lhs()const=0;
};

#endif // ILHS_H
