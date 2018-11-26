#ifndef SPINPARSER_H
#define SPINPARSER_H
#include <QObject>
#include <QDebug>
#include <QHash>
#include <QByteArray>
// scanner ///////////////////////////////
#include "hpp/scanner/SpinConstants.h"
#include "hpp/scanner/SpinScanner.h"
#include "hpp/scanner/SpinLookAheadScanner.h"
// modules //////////////////////////////////
#include "hpp/modules/IModule.h"
#include "hpp/modules/Proctype.h"
#include "hpp/modules/GlobalVariableDeclation.h"
// statements
#include "hpp/statements/Sequence.h"
#include "hpp/statements/IStatement.h"
#include "hpp/statements/StatementExpression.h"
#include "hpp/statements/IfStatement.h"
#include "hpp/statements/DoStatement.h"
// Expressions
#include "hpp/steps/VariableDeclaration.h"
#include "hpp/expressions/IExpression.h"
#include "hpp/expressions/Expression.h"
#include "hpp/expressions/BinaryExpression.h"
#include "hpp/expressions/ConstantExpression.h"
#include "hpp/expressions/SymbolExpression.h"
#include "hpp/expressions/IdentifierExpression.h"
#include "hpp/expressions/UnaryExpression.h"
#include "hpp/expressions/ConditionalExpression.h"
#include "hpp/expressions/LabelExpression.h"
#include "hpp/expressions/RunExpression.h"
#include "hpp/Priority.h"
typedef pml_tokens tok;
class SpinParser : public QObject{
    Q_OBJECT
    SpinLookAheadScanner* _scanner;
    bool _isInError;
public:
    explicit SpinParser(QObject* parent= nullptr);

private:
    void spec();
    IModule* module();
    IModule* proctype();
    void init(){}
    void never(){}
    void trace(){}
    void utype(){}
    void mtype(){}
    QList<VariableDeclaration*> decl_lst();
    VariableDeclaration* one_decl();
    void typeName();
    void active(){}
    Priority *prioity();
    void enabler();
    void visible();
    Statement* step();
    Sequence* sequence();

    void ch_init();// not a statement
    Expression* varref();
    void send();
    void recieve();
    void poll();
    void send_args();
    QList<Expression*> arg_lst();
    void recieve_args();
    void recv_arg();

    // assign group begin

    Statement* statement();

    Expression *range();

    QList<Sequence*> options();

    // ############ expression group expansion based on operator precedance
    // http://spinroot.com/spin/Man/operators.html


    // end group Expansion ################################
    bool binaroperator();
    bool unaryOp();
    Expression* any_expr();

    // any_expr subsections

    // end any_expr subsections

    Expression* expr();


    Expression* expr_sub();
    // operator splitop

    IdentifierExpression* name();
    // assignment           =
    Expression* assign(){
        auto lhs = logicOr_any_expr();

        if(have(tok::EQUAL_)){
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs, any_expr(),t.lineno);
        }
        return lhs;
    }
    // assign group end

    // logic or             ||
    Expression* logicOr_any_expr(){
        auto lhs = logicAnd_any_expr();
        while (have(tok::COLON_COLON_)) {
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs,logicAnd_any_expr(),t.lineno);
        }
        return lhs;

    }
    //  logic and            &&
    Expression* logicAnd_any_expr(){
        auto lhs = bitwiseOr_any_expr();
        while (have(tok::AND_AND_)) {
            auto t = _scanner->token();
            lhs = new BinaryExpression(t.id,lhs,bitwiseOr_any_expr(),t.lineno);
        }
        return lhs;
    }
    // bitwise or           |
    Expression* bitwiseOr_any_expr(){
        auto lhs = exclusiveOr_any_expr();
        while (have(tok::AND_AND_)) {
            auto t = _scanner->token();
            lhs = new BinaryExpression(t.id,lhs,exclusiveOr_any_expr(),t.lineno);
        }
        return lhs;

    }
    // bitwise exclusive    ^
    Expression* exclusiveOr_any_expr(){
        auto lhs = bitwiseAnd_any_expr();
        while (have(tok::AND_AND_)) {
            auto t = _scanner->token();
            lhs = new BinaryExpression(t.id,lhs,bitwiseAnd_any_expr(),t.lineno);
        }
        return lhs;
    }
    // bitwise and          &
    Expression* bitwiseAnd_any_expr(){
        auto lhs = equality_any_expr();
        while (have(tok::AND_)) {
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs,equality_any_expr(),t.lineno);
        }
        return  lhs;
    }
    // equality             ==  !=
    Expression* equality_any_expr(){
        auto lhs = relational_any_expr();
        while (have(tok::EQUAL_EQUAL_) || have(tok::NOT_EQUAL_)) {
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs,relational_any_expr(),t.lineno);
        }
        return lhs;
    }
    // relational           <   <=  >   >=
    Expression* relational_any_expr(){
        auto lhs = shift_any_expr();
        auto t = _scanner->token();
        switch (t.id) {
        case tok::LESS_:
        case tok::LESS_EQUAL_:
        case tok::GREATER_:
        case tok::GREATER_EQUAL_:
            _scanner->next();
            lhs = new BinaryExpression(t.id,lhs,shift_any_expr(),t.lineno);
        }

        return lhs;
    }
    // shift                <<  >>
    Expression* shift_any_expr(){
        auto lhs = additive_any_expr();
        if(have(tok::LESS_LESS_) || have(tok::GREATER_GREATER_)){
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs,additive_any_expr(),t.lineno);

        }
        return lhs;
    }
    // additive             +   -
    Expression* additive_any_expr(){
        auto lhs = multiplactive_any_expr();
        while (have(PLUS_) || have(MINUS_)) {
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs,multiplactive_any_expr(),t.lineno);
        }
        return lhs;
    }
    // multiplicative       *   /   %
    Expression* multiplactive_any_expr(){
        auto lhs = unary_any_expr();
        while (have(STAR_) || have(SLASH_) || have(PERCENT_)) {
            auto t = _scanner->previous();
            lhs = new BinaryExpression(t.id,lhs,unary_any_expr(),t.lineno);
        }
        return lhs;
    }
    // unary expr           !   ~   ++  --
    Expression* unary_any_expr(){
        if(haveUnary(_scanner->token().id)){
            auto t = _scanner->previous();
            auto exp = any_expr();
            return  new UnaryExpression(t.id,exp,t.lineno);
        }
        else return primary_any_expr();
    }
    // commands_anyExpr
    Expression* commands_any_expr(){
        auto type = _scanner->token();
        switch (type.id) {

        case tok::LEN_:
        {
            mustBe(tok::LPAREN_);
            auto xpr = varref();
            mustBe(tok::RPAREN_);
            return xpr;
        }
        case tok::TIMEOUT_:
        case tok::NP_:
            _scanner->next();
            return new SymbolExpression(type.id,type.lineno);
        case tok::ENABLED_:
        {

            _scanner->next();
            mustBe(tok::LPAREN_);
            auto cmd  = new UnaryExpression(type.id,any_expr(),type.lineno);
            return cmd;
        }
        case tok::PC_VALUE_:
        {
            _scanner->next();
            mustBe(tok::LPAREN_);
            auto cmd = new UnaryExpression(type.id,any_expr(),type.lineno);
            mustBe(tok::RPAREN_);
            return cmd;
        }
        case tok::RUN_:
        {
            _scanner->next();
            auto id = name();
            mustBe(tok::LPAREN_);
            auto args = arg_lst();
            mustBe(tok::RPAREN_);
            Priority* p= nullptr;
            if(see(tok::PRIORITY_)){
            p = prioity();
            }
            return  new RunExpression(type.id,id,args,p,type.lineno);
        }

        case tok::GET_PRIORITY_:
        case tok::SET_PRIORITY_:
        {
            _scanner->next();
            mustBe(LPAREN_);
            auto xpr = expr();
            mustBe(RPAREN_);
            return new UnaryExpression(type.id,xpr,type.lineno);

        }
        default: break;
        }
        if(haveConst(type.id)){
            return new ConstantExpression(type.id,type.number(),type.lineno);
        }

        // identifiers
        return  primary_any_expr();
    }


    //primary
    Expression* primary_any_expr(){
        auto t = _scanner->token();
        if(have(tok::RPAREN_)){
            auto condition = logicOr_any_expr();
            if(have(tok::COLON_)){
                auto lhs = logicOr_any_expr();
                mustBe(tok::COLON_);
                condition = new ConditionalExpression(
                            condition,lhs,logicOr_any_expr(),t.lineno
                            );
                mustBe(tok::RPAREN_);
                return  condition;
            }
            mustBe(tok::RPAREN_);
            return condition;
        }

        else if(see(tok::IDENTIFIER_)){
            auto ref = varref();
            if(have(tok::COLON_)){
                auto stmnt = statement();
                return new LabelExpression(ref,stmnt,t.lineno);
            }

            // require varref to be an array reference
            else if (have(tok::AT_)) {
                auto t2 = _scanner->previous();
                auto ref_r = name();
                return  new BinaryExpression(t2.id,ref,ref_r,t.lineno); // remoteReferenceExpression
            }
            auto t2 = _scanner->token();
            switch (t2.id) {
            case tok::NOT_:
            case tok::NOT_NOT_:
                send();
                return nullptr;
            case tok::QM_:
            case tok::QM_QM_:
            case tok::QM_LESS_:
            case tok::QM_QM_LESS_:
                recieve();
            }

            return ref;
        }
        else if(haveConst(t.id)){
            return new ConstantExpression(t.id,t.number(),t.lineno);
        }
    }
    ConstantExpression* constant(){
        auto t = _scanner->token();
        switch (t.id) {
        case pml_tokens::FALSE_:
        case pml_tokens::TRUE_:
        case pml_tokens::INT_LITERAL_:
        case tok::SKIP_:
            _scanner->next();
            return new ConstantExpression(t.id,t.number(),t.lineno);
        default: parseError("Invalied ConstantExpression",t);
        }
        return  nullptr; // will never be reached
    }
    bool haveUnary(token_id sought){
        switch (sought) {
        case tok::NOT_:
        case tok::TILDE_:
        case tok::PLUS_PLUS_:
        case tok::MINUS_MINUS_:
            _scanner->next();
            return true;
        default: return  false;
        }
    }
    // helpers
    bool see(token_id sought);
    bool have(token_id sought);
    // add error handling recovery later
    void mustBe(token_id sought);
    bool seeType(token_id sought);
    bool haveConst(token_id sought);
    bool haveChanPoll(token_id sought);
    void parseError(QString msg, pml_token object);

};

#endif // SPINPARSER_H
