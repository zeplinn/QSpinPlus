#ifndef MODULE_H
#define MODULE_H
#include "hpp/modules/IModule.h"
#include "hpp/SpinAst.h"
class Module : public SpinAst, public IModule{
    using SpinAst::SpinAst;

};

#endif // MODULE_H
