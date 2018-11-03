#include "qspin/models/Arg.h"


Arg::Arg(QObject *parent):QObject (parent){

}

QString Arg::name(Arg::Type type) noexcept
{
    switch (type)
    {
    // spin
    case LTL: return "Temporal logic";
    case Verify: return "Verification";
    case GuidedSimulation: return "Guided simulation";
    case RandomSimulation: return "Random simulation";
    case InterActive: return "Interactive simulation";
    case O1: return "Disable data-flow optimizations";
    case O2: return "Disable dead variable elimination";
    case O3: return "Disable satement merging";
    case O4: return "Enable Rendouz optimization";
    case O5: return "Disable case caching";
    case O6: return "Old interpretation tags";
    case O7: return "Old semicolon rules";
        // spin simulation
        // compile
    case Safety: return "Safety less memory" ;
    case SFH: return "Safety more memory";
    case NonProgressCycle: return "Non Progress Cycle detection";
    case NoFair : return "Disable weak fairness";
    case BFS: return "Breadth first Search (BFS)";
    case BFS_DISK: return "BFS disk";
    case BFS_DISK_LIMIT: return "BFS disk limit";
    case BFS_LIMIT: return "BFS limit";
    case NFair: return  "Allocate weak fairness";
    case NoReduce: return "No partial reduction";
    case Space: return "Optimize space";
    case VectorSZV: return "State vector size";
    case MemLim: return "Max memory use (mb)";
        // compile memory
    case HC0: return "DHC0";
    case HC1: return "DHC1";
    case HC2: return "DHC2";
    case HC3: return "DHC3";
    case Collapse: return"Collapse";
        // pan runtime
    case TimeLimit: return "Time limit";
    case SafetyMode: return "Safty mode";
    case ProgressMode: return "Liveness mode";
    case AccepanceMode: return "Acceptance mode";
    case HashSize: return "Hash size";
    case SearchDepth: return "Search depth";
    case WeakFairness: return "Weak fairness";
        //type
        //to be named
        //    case StrongFairnes : return "Strong";
        //	case DFS : return "DFS";
//    case Out: return "Output";
        //helpers
        //    case Pan:return "Pan";
        //    case PanC: return "Pan";
        //	case Group: return "Group";
        //	case Empty: return "Empty";
    case None: return  "";
    //default: qFatal("Argument have not been given a name yet");
    }
    return "";
}

QString Arg::val(Arg::Type type, QString extra)
{
    switch (type) {
    // spin
    case LTL: return "-F";
    case Verify:    return "-a";
    case InterActive:    return "-a";
    case GuidedSimulation:    return "-t";
    case RandomSimulation:    return "";

        // compile
    case Safety: return "-DSAFETY";
    case SFH: return "-DSFH";
    case NoFair: return "-DNOFAIR";
    case NonProgressCycle: return "-DNP";
    case BFS: return "-DBFS";
    case BFS_DISK: return "-DBFS_DISK";
    case BFS_DISK_LIMIT: return QString("-DBFS_DISK_LIMIT=%1").arg(extra);
    case BFS_LIMIT: return QString("-DBFS_DISK=%1").arg(extra);
    case NFair: return QString("-DNFAIR=%1").arg(extra);// maybe dynamic values later
    case NoReduce: return "-DNOREDUCE";
    case VectorSZV: return QString("-DVECTORSZV=%1").arg(extra);
    case MemLim: return  QString("-DMEMLIM=%1").arg(extra);
    // compile memory compression
    case Space: return "-DSPACE";
    case Collapse: return "-DCOLLAPSE";
    case HC0: return "-DHC0";
    case HC1: return "-DHC1";
    case HC2: return "-DHC2";
    case HC3: return "-DHC3";
    // pan runtime
    case TimeLimit: return QString("-Q%1").arg(extra);
    case SafetyMode: return "";// only added for convience
    case ProgressMode: return "-l";
    case AccepanceMode: return "-a";
    case WeakFairness: return "-f";
    case SearchDepth: return QString("-w%1").arg(extra);
    case HashSize: return QString("-m%1").arg(extra);
//    case Out: return  QString("-o %1").arg(extra);
    //case Pan:return "pan";
    //case PanC: return "pan.c";
    case None: return  "";
    //case Empty: return "";
    default: qFatal("no such argument to compile");
    }
    return "";
}

//Arg::Type Arg::toCode(const QString &name){
//    static ArgHash lookup;
//    return lookup.code(name);
//}
// currently only holds what is needed for serilization puposes
// more to add later
//Arg::ArgHash::ArgHash(){
//    args[Arg::name(Arg::SaftyMode)]         = Arg::SaftyMode;
//    args[Arg::name(Arg::ProgressMode)]      = Arg::ProgressMode;
//    args[Arg::name(Arg::AccepanceMode)]     = Arg::AccepanceMode;
//    args[Arg::name(Arg::InterActive)]   = Arg::InterActive;
//    args[Arg::name(Arg::Simulation)]    = Arg::Simulation;

//    args[Arg::name(Arg::DFS)]           = Arg::DFS;
//    args[Arg::name(Arg::BFS)]           = Arg::BFS;

//    args[Arg::name(Arg::Collapse)]     = Arg::Collapse;
//    args[Arg::name(Arg::DH4)]           = Arg::DH4;
//    args[Arg::name(Arg::WeakFairness)]  = Arg::WeakFairness;
//    args[Arg::name(Arg::StrongFairnes)] = Arg::StrongFairnes;
//    args[Arg::name(Arg::None)]          = Arg::None;
//}

//Arg::Type Arg::ArgHash::code(const QString& name){
//    if(!args.contains(name))
//        return Arg::Unknown;
//    return  args[name];
//}
