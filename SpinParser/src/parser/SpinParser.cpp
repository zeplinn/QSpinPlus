
/*!
  \class SpinParser
typename: BIT | BOOL | BYTE | SHORT | INT | MTYPE | CHAN | uname    // user defined type names (see utype)



priority: PRIORITY const                                            // simulation priority

enabler : PROVIDED '(' expr ')'                                     // execution constraint

send    : varref '!' send_args                                      // normal fifo send
    | varref '!' '!' send_args                                      // sorted send

receive : varref '?' recv_args                                      // normal receive
    | varref '?' '?' recv_args                                      // random receive
    | varref '?' '<' recv_args '>'                                  // poll with side-effect
    | varref '?' '?' '<' recv_args '>'                              // ditto

poll    : varref '?' '[' recv_args ']'                              // poll without side-effect
    | varref '?' '?' '[' recv_args ']'                              // ditto

send_args: arg_lst | any_expr '(' arg_lst ')'

arg_lst  : any_expr [ ',' any_expr ] *

recv_args: recv_arg [ ',' recv_arg ] *  |  recv_arg '(' recv_args ')'

recv_arg : varref | EVAL '(' varref ')' | [ '-' ] const

assign  : varref '=' any_expr                                       // standard assignment
    | varref '+' '+'                                                // increment
    | varref '-' '-'                                                // decrement

range	: varref ':' expr '..' expr
    | varref IN varref

options : ':' ':' sequence [ ':' ':' sequence ] *

andor	: '&' '&' | '|' '|'

binarop	: '+' | '-' | '*' | '/' | '%' | '&' | '^' | '|'
    | '>' | '<' | '>' '=' | '<' '=' | '=' '=' | '!' '='
    | '<' '<' | '>' '>' | andor

unarop	: '~' | '-' | '!'

expr	: any_expr
    | '(' expr ')'
    | expr andor expr
    | chanpoll '(' varref ')'                                       // may not be negated

chanpoll: FULL | EMPTY | NFULL | NEMPTY

string	: '"' [ any_ascii_char ] * '"'

uname	: name

name	: alpha [ alpha | number ] *

const	: TRUE | FALSE | SKIP | number [ number ] *

alpha	: 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j'
    | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't'
    | 'u' | 'v' | 'w' | 'x' | 'y' | 'z'
    | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J'
    | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T'
    | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z'
    | '_'

number	: '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
*/


#include "hpp/parser/SpinParser.h"
SpinParser::SpinParser(QObject *parent):QObject(parent){

}
/*!
 * \brief SpinParser::spec
 *   spec	: module [ module ] *
 * \return ISpinAst*
*/
void SpinParser::spec(){
    QList<IModule*> modules;
    while (_scanner->token().id!= tok::END_OF_PML_FILE_) {
        modules << module();

    }
}
/*!
 * \brief SpinParser::module
 * module	: proctype      // proctype declaration
 *  | init              // init process
 *  | never             // never claim
 *  | trace             // event trace
 *  | utype             // user defined types
 *  | mtype             // mtype declaration
 *  | decl_lst          // global vars, chans
 * \return IModule*
 *
 * // includes
 *
 * init	: INIT [ priority ] '{' sequence '}'
 *
 * never	: NEVER	'{' sequence '}'
 *
 * trace	: TRACE '{' sequence '}'
 *
 * utype	: TYPEDEF name '{' decl_lst '}'
 *
 * mtype	: MTYPE [ '=' ] '{' name [ ',' name ] * '}'
 */
IModule *SpinParser::module(){
    if(see(tok::ACTIVE_) || see(tok::PROCTYPE_)){
            return  proctype();
        }
        else if (have(tok::TYPEDEF_)) {
            auto t = _scanner->previous();
            mustBe(tok::IDENTIFIER_);
            auto name = _scanner->previous();
            mustBe(tok::LBRACE_);
            auto members = decl_lst();
            mustBe(tok::RBRACE_);
            // create typedef object
        }
        else if(have(tok::NEVER_)){

        }
        else if (have(tok::TRACE_)){

        }
        else if(see(tok::INIT_)){

        }
        else if (have(tok::MTYPE_)) {

        }
        else  {
            auto l = _scanner->token().id;
            return new GlobalVariableDeclarations( decl_lst(),l);
        }
    return nullptr;
}


/*!
 * \brief SpinParser::proctype
 * proctype: [ active ] PROCTYPE name '(' [ decl_lst ]')'
 *     [ priority ] [ enabler ] '{' sequence '}'
 *
 *  includes
 *  active  : ACTIVE [ '[' const ']' ]                  // instantiation
 * \return IModule*
 */

IModule *SpinParser::proctype(){
    bool isActive = false;
    int instances=1;
    if(have(tok::ACTIVE_)){
        if(have(tok::LBRACK_)){
            if(haveConst(_scanner->token().id)){
                instances = _scanner->previous().number();
                mustBe(tok::RBRACK_);
            }
            else parseError("No constant found",_scanner->token());
        }

    }
    mustBe(tok::PROCTYPE_);
    linenr line = _scanner->previous().lineno;
    mustBe(tok::IDENTIFIER_);
    QString id = _scanner->previous().word();
    mustBe(tok::LPAREN_);
    // add possibillity for taking arguments later int a, int b ....
    mustBe(tok::RPAREN_);
    mustBe(tok::LBRACE_);
    auto seq = sequence();
    mustBe(tok::RBRACE_);
    return new Proctype(isActive,instances,seq,line);
}

 // unused

 // unused

  // unused

 // unused

 // unused

/*!
 * \brief SpinParser::decl_lst
 * decl_lst: one_decl [ ';' one_decl ] *
 * \return QList<IVariableDeclaration*>
 */
QList<VariableDeclaration *> SpinParser::decl_lst(){
    QList<VariableDeclaration*> varDecl;
    do{
        varDecl << one_decl();
    }while(have(tok::SEMI_) || have(tok::R_ARROW_));

    return varDecl;


}

/*!
 * \brief SpinParser::one_decl
 * one_decl: [ visible ] typename  ivar [',' ivar ] *
 *
 * // includes
 * ivar    : name [ '[' const ']' ] [ '=' any_expr | '=' ch_init ]
 * \return IVariableDeclaration*
 */
VariableDeclaration *SpinParser::one_decl(){
    int visibility=0;
    if(have(tok::HIDDEN_) || have(tok::SHOW_)){
        visibility = static_cast<int>(_scanner->previous().id);
    }
    if(!seeType(IDENTIFIER_)){
        _scanner->next();
        pml_token t = _scanner->previous();
        mustBe(tok::IDENTIFIER_);
        QString id = _scanner->previous().word();
        if(have(tok::LBRACK_))
        {
            parseError("Array declaration not yet implemented",_scanner->previous());

        }

        if(have(tok::EQUAL_)){

            //ch_init
            if(see(tok::LBRACK_)){
                parseError("Channel declaration assignment not yet implemented: ",_scanner->token());
            }else{

                auto expr = any_expr();
                return new VariableDeclaration(visibility,id,expr,t.id);

            }

        }
    }
    else{
        parseError("invalid varible declaration",_scanner->token());
    }
    return nullptr;
}

/*!
 * \brief SpinParser::typeName
 *
 */
void SpinParser::typeName(){}



Priority* SpinParser::prioity(){
    mustBe(tok::PRIORITY_);
    auto t = _scanner->previous();
    auto c = constant();
    return  new Priority(c,t.lineno);
}

void SpinParser::enabler(){}

void SpinParser::visible(){}

/*!
 * \brief SpinParser::step
 *
 * \return IStatement*
 */
Statement *SpinParser::step(){
    if(have(tok::XS_) || have(tok::XR_)){// not yet implemented

    }
    Statement* stmnt = statement();
    if(have(tok::UNLESS_)){
        parseError("statement unless statement not yet implemented",_scanner->previous());
    }
    else return stmnt;
}

/*!
 * \brief SpinParser::sequence
 * sequence: step [ ';' step ] *
 * \return Sequence*
 */
Sequence *SpinParser::sequence(){
    Sequence* seq = new Sequence(_scanner->token().lineno);
    do{
        seq->append(step());
    }while(have(tok::SEMI_) || have(tok::R_ARROW_));
    return seq;
}

/*!
 * \brief SpinParser::ch_init
 * ch_init : '[' const ']' OF '{' typename [ ',' typename ] * '}'
 */
void SpinParser::ch_init(){}

/*!
 * \brief SpinParser::varref
 * varref	: name [ '[' any_expr ']' ] [ '.' varref ]
 * \return IExpression*
 */
Expression *SpinParser::varref(){
    if(have(tok::IDENTIFIER_)){
        auto id = _scanner->previous();
        if(have(tok::LBRACK_)){
            parseError("Array variable reference not yet implemented",_scanner->previous());
            auto idx = any_expr();
            Q_UNUSED(idx)
            mustBe(tok::RBRACK_);
        }
        if(have(tok::DOT_)){
            parseError("grouped object reference not yet implemented",_scanner->previous());
            auto chain = varref();
            Q_UNUSED(chain);
        }
        return nullptr; // return variable reference
    }

}

void SpinParser::send(){}

void SpinParser::recieve(){}

void SpinParser::poll(){}

void SpinParser::send_args(){}

QList<Expression *> SpinParser::arg_lst(){
    QList<Expression*> args;
    do{
        args << any_expr();
    }while (have(tok::COMMA_));
    return args;
}

void SpinParser::recieve_args(){}

void SpinParser::recv_arg(){}



Statement *SpinParser::statement(){
    auto t = _scanner->token();
    switch (_scanner->token().id) {
    case tok::IF_:
    {
        _scanner->next();
        mustBe(COLON_COLON_);
        auto opts = options();
        mustBe(FI_);
        return new IfStatement(opts,t.lineno);
    }
    case tok::DO_:
    {
        mustBe(DO_);
        mustBe(COLON_COLON_);
        auto opts = options();

        mustBe(OD_);
        return new DoStatement(opts,t.lineno);
    }
    case tok::FOR_:
    {
        mustBe(FOR_);
        mustBe(LPAREN_);
        auto r = range();
        mustBe(RPAREN_);
        mustBe(LBRACE_);
        auto seq = sequence();
        mustBe(RBRACE_);
        return new ConstantExpression(t.id,0,t.lineno); // OBS: object should be changed
    }
    case tok::ATOMIC_:
    {
        mustBe(ATOMIC_);
        mustBe(LBRACE_);
        auto seq = sequence();
        mustBe(RBRACE_);
        return new ConstantExpression(t.id,0,t.lineno); // object should be changed
    }
    case tok::D_STEP_:
    {

        mustBe(D_STEP_);
        mustBe(LBRACE_);
        auto seq = sequence();
        mustBe(RBRACE_);
        return  new ConstantExpression(t.id,0,t.lineno); // OBS: object must be changed
    }
    case tok::SELECT_:
    {
        mustBe(SELECT_);
        mustBe(LPAREN_);
        auto sel = range();
        return  new ConstantExpression(t.id,0,t.lineno); // OBS: object must be changed
    }
    case tok::LBRACE_:
    {
        mustBe(tok::LBRACE_);
        auto seq = sequence();
        mustBe(tok::RBRACE_);
        return seq;
    }

    case tok::ELSE_:
    case tok::BREAK_:
        mustBe(BREAK_);
        return new SymbolExpression(t.id,t.lineno);
    case tok::GOTO_:
    {
        mustBe(GOTO_);
        auto n = name();
        return new UnaryExpression(t.id,n,t.lineno);
    }
        // case labeled statement mix with varref calls
    case tok::ASSERT_:
    {
        mustBe(tok::ASSERT_);
        expr();
        break;
    }

    case tok::C_CODE_:
    case tok::C_EXPR_:
    case C_DECL_:
    case C_TRACK_:
    case C_STATE_:
    {
        _scanner->next();
        mustBe(LBRACE_);
        int braceCount =1;
        do{
            if(have(LBRACE_)){
             braceCount++;
            }
            else if (have(RBRACE_)) {
                braceCount--;
            }
            else _scanner->next();

        }while (braceCount>0) ;
        // will not focus on supporting c code
        return new SymbolExpression(t.id,t.lineno);
}
    default:
        _scanner->next();

    }
    return new StatementExpression( expr(),t.lineno);
}

Expression* SpinParser::range(){
    // loop construct
    auto id = varref(); // ref
    if(have(tok::COLON_)){
        auto from =expr();// from
        mustBe(tok::DOT_DOT_);
        auto to =expr(); // to
        return new ConstantExpression(id->type(),0,id->line()); // OBS: must be changed
    }
    else{
        mustBe(tok::IN_);
        auto in = varref(); // list
        return new ConstantExpression(id->type(),0,id->line());
    }
}

QList<Sequence *> SpinParser::options(){
    QList<Sequence*> opts;
    while(have(tok::COLON_COLON_)){
        opts << sequence();
    }
    return opts;
}

bool SpinParser::binaroperator(){
    switch (_scanner->token().id) {
    case tok::PLUS_:
    case tok::MINUS_:
    case tok::STAR_:
    case tok::SLASH_:
    case tok::PERCENT_:
    case tok::AND_:
    case tok::OR_:
    case tok::CIRCUMFLEX_: // ^
    case tok::NOT_:
    case tok::GREATER_:
    case tok::GREATER_EQUAL_:
    case tok::LESS_:
    case tok::LESS_EQUAL_:
    case tok::EQUAL_EQUAL_:
    case tok::NOT_EQUAL_:
    case tok::LESS_LESS_:
    case tok::GREATER_GREATER_:
    case tok::AND_AND_:
    case tok::OR_OR_:
        _scanner->next();
        return  true;
    default: return  false;
    }
}

bool SpinParser::unaryOp(){
    switch (_scanner->token().id) {
    case tok::NOT_:
    case tok::MINUS_:
    case tok::TILDE_: // ~
        _scanner->next();
        return true;
    default: return false;
    }
}

// any expr helpers;

/*!
 * \brief SpinParser::any_expr
 * any_expr: '(' any_expr ')'
    | any_expr binarop any_expr
    | unarop any_expr
    | '(' any_expr '-' '>' any_expr ':' any_expr ')'
    | LEN '(' varref ')'                                            // nr of messages in chan
    | poll
    | varref
    | const
    | TIMEOUT
    | NP_                                                           // non-progress system state
    | ENABLED '(' any_expr ')'                                      // refers to a pid
    | PC_VALUE '(' any_expr ')'                                     / refers to a pid
    | name '[' any_expr ']' '@' name                                // refers to a pid
    | RUN name '(' [ arg_lst ] ')' [ priority ]
    | get_priority( expr )                                          // expr refers to a pid
    | set_priority( expr , expr )                                   // first expr refers to a pid
 * \return IExpression*
 */
Expression *SpinParser::any_expr(){
    return logicOr_any_expr();
}




/*!
 * \brief expr
 *  expr: expr_sub && expr
 *      | expr_sub
 * expr have been split up into expr and expr_sub
 * due to being a topdown parser
 * \return Expression*
 */
Expression *SpinParser::expr(){
    auto lhs = expr_sub();
    while (have(tok::AND_AND_)) {
        auto t = _scanner->previous();
        lhs = new BinaryExpression(t.id,lhs,expr(),t.lineno);
    }
    return lhs;

}

/*!
 * \brief expr_sub
 * expr_sub: '(' expr ')'
 *          | chanpoll '(' varref ')'
 *          | any_expr
 * \return Expression*
 */
Expression *SpinParser::expr_sub(){
    if(have(tok::LPAREN_)){
        auto e = expr();
        mustBe(tok::RPAREN_);
        return e;
    }
    else if(haveChanPoll(_scanner->token().id)){
        auto t = _scanner->previous();
        mustBe(tok::LPAREN_);
        auto ref = varref();
        mustBe(tok::RPAREN_);
        return  new UnaryExpression(t.id,ref,t.lineno);
    }
    return any_expr();
}

IdentifierExpression *SpinParser::name(){
    mustBe(tok::IDENTIFIER_);
    auto t = _scanner->previous();
    return new IdentifierExpression(t.id,t.word(),t.lineno);
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
///  Helper methoeds
bool SpinParser::see(token_id sought){
    return _scanner->token().id == sought;
}



bool SpinParser::have(token_id sought){
    if(see(sought)){
        _scanner->next();
        return  true;
    }
    else return false;
}

void SpinParser::mustBe(token_id sought){
    if(see(sought)){
        _scanner->next();

    }
    else{
        _isInError = true;
        // prompt messeages
    }
}

bool SpinParser::seeType(token_id sought){
    switch (sought) {
    case pml_tokens::BIT_:
    case pml_tokens::BYTE_:
    case pml_tokens::SHORT_:
    case pml_tokens::INT_:
        return true;
    default: return  false;
    }
}

bool SpinParser::haveConst(token_id sought){
    switch (sought) {
    case pml_tokens::FALSE_:
    case pml_tokens::TRUE_:
    case pml_tokens::INT_LITERAL_:
        _scanner->next();
        return true;
    default: return false;
    }
}

bool SpinParser::haveChanPoll(token_id sought){
    switch (sought) {
    case tok::FULL_:
    case tok::EMPTY_:
    case tok::NFULL:
    case tok::NEMPTY:
        _scanner->next();
        return  true;
    default: return false;
    }
}

void SpinParser::parseError(QString msg, pml_token object){
    Q_UNUSED(msg)

    qDebug()<< msg << "line nr:" << object.lineno;
    throw QString("parser failed");
}
