#include "qspin/models/Arg.h"


Arg::Arg(){

}

QString Arg::name(Arg::Type type) noexcept
{
	switch (type)
	{
	// memory
    case DH4: return "DH4";
    case DCollapse: return"DCollapse";
		//type
    case Safty: return "Safty";
	case Liveness: return "Liveness";
	case Accepance: return "Acceptance";
    case Simulation: return "Simulation";
    case InterActive: return "Interactive";
	case DNP: return "DNP";
	case DSafty: return "DSafty";
		//to be named
    case WeakFairness: return "Weak";
    case StrongFairnes : return "Strong";
	case DNFair : return "DNFair";
	case DFS : return "DFS";
	case BFS: return "BFS";
    case Out: return "Output";
    case HashSize: return "HashSize";
    case SearchDepth: return "SearchDepth";
	//helpers
    case Pan:return "Pan";
    case PanC: return "Pan";
	case Group: return "Group";
	case Empty: return "Empty";
    case None: return  "None";
	default: qFatal("Argument have not been given a name yet"); return "";
	}
}

QString Arg::val(Arg::Type type, QString extra)
{
	switch (type) {
	case DCollapse: return "-DCOLLAPSE";
	case DH4: return "-DH4";
	case Safty: return "";// not yet known
	case Liveness: return "-l";
    case Verify:    return "-a";
	case Accepance: return "-a";
	case WeakFairness: return "-f";
    case LTL: return "-F";
	case DNFair: return QString("-DNFAIR=2");// maybe dynamic values later
	case DNP: return "-DNP";
	case DSafty: return "-DSAFETY";
	case BFS: return "-DBFS";
	case DFS: return "";
    case SearchDepth: return QString("-w%1").arg(extra);
    case HashSize: return QString("-m%1").arg(extra);
    case Out: return  QString("-o %1").arg(extra);
    case Pan:return "pan";
    case PanC: return "pan.c";
    case None: return  "";
	case Empty: return "";
	default: qFatal("no such argument to compile"); return "";
	}
}

Arg::Type Arg::toCode(const QString &name){
    static ArgHash lookup;
    return lookup.code(name);
}
// currently only holds what is needed for serilization puposes
// more to add later
Arg::ArgHash::ArgHash(){
    args[Arg::name(Arg::Safty)]         = Arg::Safty;
    args[Arg::name(Arg::Liveness)]      = Arg::Liveness;
    args[Arg::name(Arg::Accepance)]     = Arg::Accepance;
    args[Arg::name(Arg::InterActive)]   = Arg::InterActive;
    args[Arg::name(Arg::Simulation)]    = Arg::Simulation;

    args[Arg::name(Arg::DFS)]           = Arg::DFS;
    args[Arg::name(Arg::BFS)]           = Arg::BFS;

    args[Arg::name(Arg::DCollapse)]     = Arg::DCollapse;
    args[Arg::name(Arg::DH4)]           = Arg::DH4;
    args[Arg::name(Arg::WeakFairness)]  = Arg::WeakFairness;
    args[Arg::name(Arg::StrongFairnes)] = Arg::StrongFairnes;
    args[Arg::name(Arg::None)]          = Arg::None;
}

Arg::Type Arg::ArgHash::code(const QString& name){
    if(!args.contains(name))
        return Arg::Unknown;
    return  args[name];
}
