//
// Created by Nick Ray on 3/7/21.
//

#ifndef SCANNER_STATE_HPP
#define SCANNER_STATE_HPP

enum State {
    INITIAL = 0,
    ASSIGNOP,
    GTEQ,
    EQ,
    COLONEQ,
    LTEQ,
    ID,
    NUM,
    EOF_,
    SEMI,
    PLUS,
    MINUS,
    MULT,
    DIVIDE,
    MOD,
    DOT,
    COMMA,
    COLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    CMT_ST_A,
    CMT_ST_B,
    CMT_END_A,
    CMT_END_B,
    FINAL = 49,
    ERROR = 50
};

#endif //SCANNER_STATE_HPP
