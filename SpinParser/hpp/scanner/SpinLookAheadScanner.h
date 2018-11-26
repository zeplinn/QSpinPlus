#ifndef SPINLOOKAHEADSCANNER_H
#define SPINLOOKAHEADSCANNER_H
#include <QObject>
#include "hpp/scanner/SpinScanner.h"
class SpinLookAheadScanner : public QObject
{
    Q_OBJECT
SpinScanner * _scanner;
pml_token _previousToken, _currentToken;
public:
    SpinLookAheadScanner(QString text,QObject* parent= nullptr):QObject (parent)
    ,_scanner(new SpinScanner(text)){}

    void next(){
        _previousToken = _currentToken;
        _currentToken = _scanner->getNext();
    }

    pml_token token(){ return _currentToken; }
    pml_token previous(){ return _previousToken;}
    bool atEnd(){
        return _currentToken.id != pml_tokens::END_OF_PML_FILE_;
    }
};
#endif // SPINLOOKAHEADSCANNER_H
