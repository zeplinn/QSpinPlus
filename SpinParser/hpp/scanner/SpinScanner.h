#ifndef SPINSCANNER_H
#define SPINSCANNER_H
#include <QObject>
#include <ctype.h>
#include <QVector>
#include <QHash>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include "hpp/scanner/SpinConstants.h"
#include "hpp/scanner/SpinTerminals.h"
using std::map;
using std::string;
#define KEYWORD_BUFFER 128
using std::vector;
union mod_t{
        int num;
        QByteArray* word;
        mod_t(QByteArray* word):word(word){}
        mod_t(int num):num(num){}
};
struct pml_token{
        token_id id;
        mod_t mod;
        unsigned short lineno;
        pml_token():id(END_OF_PML_FILE_),mod(0),lineno(65333){}
        pml_token(token_id id,unsigned short lineno):id(id),mod(0),lineno(lineno){}
        pml_token(token_id id,QByteArray* word,unsigned short lineno):id(id),mod(word),lineno(lineno){
        }
        pml_token(token_id id,int num,unsigned short lineno):id(id),mod(num),lineno(lineno){

        }
        int number(){return mod.num;}
        QByteArray& word()const{return *mod.word;}


};
typedef unsigned short linenr;
class SpinScanner
{

    private:
        QHash<QByteArray,token_id> key;
        QHash<QByteArray,QByteArray> words;
        char word[KEYWORD_BUFFER] ={'\0'};
        char* initial;
        char* scan_text;
        linenr lineno;
        string input_string;
        char * last_symbol;
    public:

        SpinScanner(QString text);
        pml_token getNext();
       // bool isEndOfFile();
private:
        char inline symbol(){ return *scan_text;}
        //char* see(){ return scan_text;}
        char* next();
        bool isNext(char c);
        bool isKeyword(const string& word);
        token_id keyword(QByteArray word);
        pml_token set(token_id id);
        pml_token set(token_id id,int num);
        pml_token set(token_id id, QByteArray *word);
        void whitespace();
};
#endif // SPINSCANNER_H
