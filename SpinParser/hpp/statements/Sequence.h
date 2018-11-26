#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <QObject>
#include "hpp/statements/Statement.h"

class Sequence: public Statement{

    QList<Statement*> _statements;
    using Statement::Statement;
public:

    void append (Statement* statement){
        _statements << statement;
        statement->setParent(this);
    }
};

#endif // SEQUENCE_H
