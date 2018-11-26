#ifndef PROCTYPE_H
#define PROCTYPE_H
#include "hpp/modules/Module.h"
#include "hpp/statements/Sequence.h"
#include <QObject>
class Proctype : public Module{

    bool _isActive;
    int _instances;
    Sequence* _sequence;
public:
    explicit Proctype(bool isActive,int instances, Sequence* sequence,linenr lineno): Module(lineno)
    ,_isActive(isActive),_instances(instances),_sequence(sequence){
        sequence->setParent(this);
    }
};

#endif // PROCTYPE_H
