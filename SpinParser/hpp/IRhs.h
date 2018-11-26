#ifndef IRHS_H
#define IRHS_H
#include "hpp/expressions/Expression.h"
class IRhs{
public:
    virtual ~IRhs(){}
    virtual Expression* rhs()const=0;
};

#endif // IRHS_H
