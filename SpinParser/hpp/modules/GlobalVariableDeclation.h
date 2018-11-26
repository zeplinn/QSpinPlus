#ifndef GLOBALVARIABLEDECLATION_H
#define GLOBALVARIABLEDECLATION_H
#include "hpp/modules/Module.h"
#include "hpp/steps/VariableDeclaration.h"
class GlobalVariableDeclarations: public Module
{
    QList<VariableDeclaration*> _varibles;
public:
    GlobalVariableDeclarations(QList<VariableDeclaration*> variables,linenr lineno):Module(lineno)
    ,_varibles(variables){
        for(auto decl : variables)
            decl->setParent(this);
    }
};
#endif // GLOBALVARIABLEDECLATION_H
