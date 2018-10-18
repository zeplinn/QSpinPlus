#ifndef ARG_H
#define ARG_H
#include <QObject>
#include <QHash>
#include <QByteArray>

class Arg
{
public:
    enum Type {
        //no extra argument chices
        Safty, Liveness, Accepance,
        Verify, InterActive, Simulation,
// memory compression
        DCollapse=10, DH4,

        WeakFairness= 30,StrongFairnes,
        DNP, DSafty,
        DFS, BFS, Out,
        LTL,
        // extra argument choice
        DNFair =50,	HashSize, SearchDepth,

        // helpers
        Pan=100,
        PanC,
        Group,
        Empty,
        None,
        Unknown = -1
    };
    explicit Arg();

    static QString name(Arg::Type type) noexcept;
    static QString val(Arg::Type type,QString extra=" ");
    static Arg::Type toCode(const QString& name);
private:
    // helper class for const map initilization
    class ArgHash{
        QHash<QString,Arg::Type> args;
    public:
        ArgHash();
        Arg::Type code(const QString& name);
    };
};







#endif // ARG_H
