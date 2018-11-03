#ifndef ARG_H
#define ARG_H
#include <QObject>
#include <QHash>
#include <QByteArray>

class Arg: public QObject
{
    Q_OBJECT
public:
    enum Type {
        None,
        //spin
        LTL,
        Verify, InterActive, GuidedSimulation,RandomSimulation, // spin mode. Random is only there for convience
        O1, O2, O3,O4,O5,O6,O7, //Verification optimizations
        // spin simulation

        // compile
        Safety=35, SFH,NoFair, // to use only with safety verification
        NonProgressCycle,
        BFS,BFS_DISK,BFS_DISK_LIMIT,BFS_LIMIT,
        NFair ,
        NoReduce, // no partial reduction
        Space,
        VectorSZV, // state vector size
        MemLim,     // maximum memory (mega bytes )
        //compile memory compression
        Collapse, HC0, HC1, HC2, HC3, // state vector compression modes

        // pan runtime
        TimeLimit,
        SafetyMode, ProgressMode, AccepanceMode, // runtime mode. Safetymode is only there for convience
        HashSize,
        SearchDepth,
        WeakFairness= 110,
        // helpers
//        Pan=170,
//        PanC,
//        Group,
//        Empty,
//        Unknown = -1
    };
    Q_ENUM(Type)
    explicit Arg(QObject* parent = nullptr);

    Q_INVOKABLE static QString name(Arg::Type type) noexcept;
    Q_INVOKABLE static QString val(Arg::Type type,QString extra=" ");
    static QString val(Arg::Type type,int extra){  return val(type,QString::number(extra));  }
//    Q_INVOKABLE static Arg::Type toCode(const QString& name);
private:
    // helper class for const map initilization
//    class ArgHash{
//        QHash<QString,Arg::Type> args;
//    public:
//        ArgHash();
//        Arg::Type code(const QString& name);
//    };
};







#endif // ARG_H
