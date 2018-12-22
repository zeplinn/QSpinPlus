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

    case CustomSpinString: return  "Spin commands";
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
    case HC: return "Collapse state vector size";
    case Collapse: return"Collapse";

    case CustomGccString: return  "Gcc commands";

        // pan runtime
    case TimeLimit: return "Time limit";
    case SafetyMode: return "Safety mode";
    case ProgressMode: return "Progress mode";
    case AccepanceMode: return "Acceptance mode";
    case HashSize: return "Hash size";
    case SearchDepth: return "Search depth";
    case WeakFairness: return "Weak fairness";
    case CustomPanString: return  "Pan commands";

    case None: return  "";
    }
    return "";
}

QString Arg::val(Arg::Type type, QString extra)
{
    switch (type) {
    // spin
    case LTL: return "-F";
    case O1: return "-o1";
    case O2: return "-o2";
    case O3: return "-o3";
    case O4: return "-o4";
    case O5: return "-o5";
    case O6: return "-o6";
    case O7: return "-o7";
    case Verify:    return "-a";
    case InterActive:    return "-a";
    case GuidedSimulation:    return "-t";
    case RandomSimulation:    return "";

    case CustomSpinString: return  extra;

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
    case HC: return QString("-DHC%1").arg(extra);

    case CustomGccString: return  extra;

        // pan runtime
    case TimeLimit: return QString("-Q%1").arg(extra);
    case SafetyMode: return "";// only added for convience
    case ProgressMode: return "-l";
    case AccepanceMode: return "-a";
    case WeakFairness: return "-f";
    case SearchDepth: return QString("-m%1").arg(extra);
    case HashSize: return QString("-w%1").arg(extra);

    case CustomPanString: return  extra;

    case None: return  "";
    default: qFatal("Arg: no such argument to compile");
    }
    return "";
}

Arg::Category Arg::getCategory(Arg::Type command){
    if(isSpinArgument(command)) return  Spin;
    if(isCompileArgument(command)) return Gcc;
    if(isPanArgument(command)) return  Pan;
    throw QString("command do not belong to any category: %1").arg(name(command));
}

bool Arg::isSpinArgument(Arg::Type arg){
    return arg>= static_cast<Type>(Spin) && arg< static_cast<Type>(Gcc);
}

bool Arg::isCompileArgument(Arg::Type arg){
    return arg>= static_cast<Type>(Gcc) && arg< static_cast<Type>(TimeLimit);
}

bool Arg::isPanArgument(Arg::Type arg){
    return arg>= static_cast<Type>(Pan);
}
