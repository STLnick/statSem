/*
 * Nick Ray
 * 2/15/21
 */

#ifndef SCANNER_TOKEN_RECORD_HPP
#define SCANNER_TOKEN_RECORD_HPP

#include <string>

/* Single char tokens */
// = + - / * ( ) { } [ ] % . , ; :

/* Double char tokens */
// == => := =<

// TODO: create a map to the first() of a token for error output

enum tokenID {
    ID_tk,
    NUM_tk,
    EOF_tk,
    ASSIGNOP_tk,
    SEMI_tk,
    PLUS_tk,
    MINUS_tk,
    MULT_tk,
    DIVIDE_tk,
    MOD_tk,
    DOT_tk,
    COMMA_tk,
    COLON_tk,
    LPAREN_tk,
    RPAREN_tk,
    LBRACE_tk,
    RBRACE_tk,
    LBRACKET_tk,
    RBRACKET_tk,
    EQ_tk,
    GTEQ_tk,
    LTEQ_tk,
    COLONEQ_tk,
    BEGIN_tk,
    END_tk,
    LOOP_tk,
    WHOLE_tk,
    VOID_tk,
    EXIT_tk,
    GETTER_tk,
    OUTTER_tk,
    MAIN_tk,
    IF_tk,
    THEN_tk,
    ASSIGN_tk,
    DATA_tk,
    PROC_tk,
};
const std::string tokenNames[] = {
        "Identifier",
        "Number",
        "End Of File",
        "Assignment Operator",
        "Semicolon",
        "Addition",
        "Subtraction",
        "Multiplication",
        "Division",
        "Modulus",
        "Dot",
        "Comma",
        "Colon",
        "Left Parenthesis",
        "Right Parenthesis",
        "Left Brace",
        "Right Brace",
        "Left Bracket",
        "Right Bracket",
        "Equality Operator",
        "Greater Than or Equal To Operator",
        "Less Than or Equal To Operator",
        "Colon Equals Operator",
        "Begin Keyword",
        "End Keyword",
        "Loop Keyword",
        "Whole Keyword",
        "Void Keyword",
        "Exit Keyword",
        "Getter Keyword",
        "Outter Keyword",
        "Main Keyword",
        "If Keyword",
        "Then Keyword",
        "Assign Keyword",
        "Data Keyword",
        "Proc Keyword"
};
const std::string tokenLiterals[] = {
        "Identifier",
        "Number",
        "End Of File",
        "Assignment Operator",
        ";",
        "+",
        "-",
        "*",
        "/",
        "%",
        ".",
        ",",
        ":",
        "(",
        ")",
        "{",
        "}",
        "[",
        "]",
        "==",
        "=>",
        "=<",
        ":=",
        "begin",
        "end",
        "loop",
        "whole",
        "void",
        "exit",
        "getter",
        "outter",
        "main",
        "if",
        "then",
        "assign",
        "data",
        "proc"
};
const std::string keywords[] = {
        "begin",
        "end",
        "loop",
        "whole",
        "void",
        "exit",
        "getter",
        "outter",
        "main",
        "if",
        "then",
        "assign",
        "data",
        "proc"
};

typedef struct {
    tokenID tokenId;       // The token type
    std::string stringVal; // The identifying string value for the token
    int charCol;           // Column on line token begins
    int lineNum;           // Line number which the token is on in source
} TokenRecord;

#endif /* SCANNER_TOKEN_RECORD_HPP */