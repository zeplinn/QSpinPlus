#include "hpp/scanner/SpinScanner.h"
namespace  {
bool inline isIdentifier_start(char c){ return isalpha(c) || c == '_';	}
bool inline isIdentifier(char c){ return isIdentifier_start(c) || isdigit(c); }
}
SpinScanner::SpinScanner(QString text): lineno(1)
{
    // inefficent string concatanation. Consider QTextStream for later refinement,
    // or differnt way of terminating at end of file.
    input_string = text.toStdString().substr(0,text.length());
    scan_text = &input_string[0];
    last_symbol = &input_string[text.size()-1];

    key["active"]       = ACTIVE_       ;
    key["assert"]       = ASSERT_       ;
    key["atomic"]       = ATOMIC_       ;
    key["bit"]          = BIT_          ;
    key["break"]        = BREAK_        ;
    key["byte"]         = BYTE_         ;
    key["c_code"]       = C_CODE_       ;
    key["c_expr"]       = C_EXPR_       ;
    key["c_decl"]       = C_DECL_       ;
    key["c_track"]      = C_TRACK_      ;
    key["c_state"]      = C_STATE_      ;
    key["do"]           = DO_           ;
    key["d_step"]       = D_STEP_       ;
    key["else"]         = ELSE_         ;
    key["empty"]        = EMPTY_        ;
    key["enabled"]      = ENABLED_      ;
    key["false"]        = FALSE_        ;
    key["fi"]           = FI_           ;
    key["for"]          = FOR_          ;
    key["full"]         = FULL_         ;
    key["get_priority"] = GET_PRIORITY_ ;
    key["goto"]         = GOTO_         ;
    key["if"]           = IF_           ;
    key["in"]           = IN_           ;
    key["init"]         = INIT_         ;
    key["int"]          = INT_          ;
    key["hidden"]       = HIDDEN_       ;
    key["len"]          = LEN_          ;
    key["mtype"]        = MTYPE_        ;
    key["nempty"]       = NEMPTY        ;
    key["nfull"]        = NFULL         ;
    key["np_"]          = NP_           ;
    key["never"]        = NEVER_        ;
    key["od"]           = OD_           ;
    key["of"]           = OF_           ;
    key["pc_value"]     = PC_VALUE_     ;
    key["priority"]     = PRIORITY_     ;
    key["proctype"]     = PROCTYPE_     ;
    key["run"]          = RUN_          ;
    key["select"]       = D_STEP_       ;
    key["set_priority"] = SET_PRIORITY_ ;
    key["short"]        = SHORT_        ;
    key["show"]         = SHOW_         ;
    key["skip"]         = SKIP_         ;
    key["timeout"]      = TIMEOUT_      ;
    key["trace"]        = TRACE_        ;
    key["true"]         = TRUE_         ;
    key["typedef"]      = TYPEDEF_      ;
    key["unless"]       = UNLESS_       ;
    key["xr"]           = XR_           ;
    key["xs"]           = XS_           ;

}

pml_token SpinScanner::getNext(){

    whitespace();
    if(scan_text > last_symbol){
        return set(END_OF_PML_FILE_);
    }
    switch (*scan_text) {
    case '(':                   return set(LPAREN_);
    case ')':                   return set(RPAREN_);
    case '{':                   return set(LBRACE_);
    case '}':                   return set(RBRACE_);
    case '[':                   return set(LBRACK_);
    case ']':                   return set(RBRACK_);
    case '^':                   return set(CIRCUMFLEX_);
    case '~':                   return set(TILDE_);
    case ',':                   return set(COMMA_);
    case ';':                   return set(SEMI_);
    case '+':
        if(isNext('+'))         return set(PLUS_PLUS_);
        else                    return set(PLUS_);
    case '-':
        if      (isNext('-'))	return set(MINUS_MINUS_);
        else if (isNext('>'))	return set(R_ARROW_);
        else					return set(MINUS_);
    case '*':                   return set(STAR_);
    case '/':                   return set(SLASH_);
    case '=':
        if(isNext('='))         return set(EQUAL_EQUAL_);
        else                    return set(EQUAL_);
    case ':':
        if(isNext(':'))         return set(COLON_COLON_);
        else                    return set(COLON_);
    case '<':
        if(isNext('='))         return set(LESS_EQUAL_);
        else if(isNext('<'))    return set(LESS_LESS_);
        else                    return set(LESS_);
    case '>':
        if(isNext('='))         return set(GREATER_EQUAL_);
        else if (isNext('>'))   return set(GREATER_GREATER_);
        else                    return set(GREATER_);
    case '&':
        if(isNext('&'))         return set(AND_AND_);
        else                    return set(AND_);
    case '|':
        if(isNext('|'))         return set(OR_OR_);
        else                    return set(OR_);
    case '?':
        if      (isNext('?'))
            if  (isNext('<')) return set(QM_QM_LESS_);
            else              return set(QM_QM_);
        else                    return set(QM_);
    case '@':                   return set(AT_);
    case '!':
        if      (isNext('!'))   return set(NOT_NOT_);
        else if (isNext('='))   return set(NOT_EQUAL_);
        else                    return set(NOT_);
    case '.':
        if(isNext('.'))         return set(DOT_DOT_);
        else                    return set(DOT_);
    default:
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        char* start = scan_text;
        while(isdigit(*next())){} return set(INT_LITERAL_,atoi(start));
    }
        if (!isIdentifier_start(symbol())){
            QString s = QString("Invalid scanning symbol: %1, at line:")
                    .arg(scan_text[0]).arg(lineno);
            qFatal(s.toLocal8Bit());
        }
        //throw QString("Invalid scanning symbol: %1\n").arg(scan_text[0]);

        char* first = scan_text;
        int length = 0;
        while (isIdentifier(symbol())) {
            length++;
            next();
        }
        QByteArray* str = new QByteArray(first,length);
        if (key.contains(*str)){
            scan_text--;
            return set(key[*str]);
        }
        else
            return set(IDENTIFIER_,str);
    }

}

char *SpinScanner::next(){return ++scan_text;}

bool SpinScanner::isNext(char c){
    if(scan_text>=last_symbol && !(scan_text[1]==c)) return false;
    next();
    return true;
}

token_id SpinScanner::keyword(QByteArray word){return key[word];}

// helper functions

pml_token SpinScanner::set(token_id id)
{
    next();
    return  pml_token(id,lineno);
}

pml_token SpinScanner::set(token_id id, int num)
{
    return pml_token(id,num,lineno);
}

pml_token SpinScanner::set(token_id id, QByteArray* word)
{
    return pml_token(id,word,lineno);
}


void SpinScanner::whitespace()
{
    while(scan_text<=last_symbol){

        switch (*scan_text) {
        case '/':
            if(isNext('/'))
                while(scan_text<= last_symbol && (*scan_text) != '\n')
                    next();
            else if (isNext('*')) {
                next();
                while ((*next())!='*' && ! isNext('/')) {
                    if((*scan_text)=='\n')
                        lineno++;
                }
            }
            else return;
        case '\n':
            lineno++;
        case '\t':
        case '\r':
        case ' ':
            next();
            break;
        default:
            return;
        }
    }

}
