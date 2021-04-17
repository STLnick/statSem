#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <string>
#include "ScannerStruct.hpp"
#include "Table.hpp"
#include "token.hpp"
#include "TokenRecord.hpp"

Scanner *initScanner(std::string &src) {
    Scanner *scanner = (Scanner *) malloc(sizeof(Scanner));

    scanner->src = &src;
    scanner->i = 0;
    scanner->c = scanner->src->at(scanner->i); // Explicitly set the first character

    return scanner;
}

void advanceScanner(Scanner *scanner, int &charCol) {
    scanner->i += 1;
    charCol += 1;
    if (scanner->i != scanner->src->length())
        scanner->c = scanner->src->at(scanner->i);
}

int isKeyword(std::string str) {
    for (int i = 0; i < 14; i++) {
        if (str == keywords[i]) {
            return 1;
        }
    }
    return 0;
}

TokenRecord *getKeywordToken(std::string str, int lineCnt, int charCol) {
    if (str == "begin")  return initToken(str, BEGIN_tk, lineCnt, charCol);
    if (str == "end")    return initToken(str, END_tk, lineCnt, charCol);
    if (str == "loop")   return initToken(str, LOOP_tk, lineCnt, charCol);
    if (str == "whole")  return initToken(str, WHOLE_tk, lineCnt, charCol);
    if (str == "void")   return initToken(str, VOID_tk, lineCnt, charCol);
    if (str == "exit")   return initToken(str, EXIT_tk, lineCnt, charCol);
    if (str == "getter") return initToken(str, GETTER_tk, lineCnt, charCol);
    if (str == "outter") return initToken(str, OUTTER_tk, lineCnt, charCol);
    if (str == "main")   return initToken(str, MAIN_tk, lineCnt, charCol);
    if (str == "if")     return initToken(str, IF_tk, lineCnt, charCol);
    if (str == "then")   return initToken(str, THEN_tk, lineCnt, charCol);
    if (str == "assign") return initToken(str, ASSIGN_tk, lineCnt, charCol);
    if (str == "data")   return initToken(str, DATA_tk, lineCnt, charCol);
    if (str == "proc")   return initToken(str, PROC_tk, lineCnt, charCol);

    exit(1); // Error
}

TokenRecord *getTypedToken(State state, std::string str, int lineCnt, int charCol) {
    switch (state) {
        case ASSIGNOP:
            return initToken(str, ASSIGNOP_tk, lineCnt, charCol);
        case GTEQ:
            return initToken(str, GTEQ_tk, lineCnt, charCol);
        case EQ:
            return initToken(str, EQ_tk, lineCnt, charCol);
        case COLONEQ:
            return initToken(str, COLONEQ_tk, lineCnt, charCol);
        case LTEQ:
            return initToken(str, LTEQ_tk, lineCnt, charCol);
        case ID:
            if (isKeyword(str)) {
                return getKeywordToken(str, lineCnt, charCol);
            }
            return initToken(str, ID_tk, lineCnt, charCol);
        case NUM:
            return initToken(str, NUM_tk, lineCnt, charCol);
        case EOF_:
            return initToken(str, EOF_tk, lineCnt, charCol);
        case SEMI:
            return initToken(str, SEMI_tk, lineCnt, charCol);
        case PLUS:
            return initToken(str, PLUS_tk, lineCnt, charCol);
        case MINUS:
            return initToken(str, MINUS_tk, lineCnt, charCol);
        case MULT:
            return initToken(str, MULT_tk, lineCnt, charCol);
        case DIVIDE:
            return initToken(str, DIVIDE_tk, lineCnt, charCol);
        case MOD:
            return initToken(str, MOD_tk, lineCnt, charCol);
        case DOT:
            return initToken(str, DOT_tk, lineCnt, charCol);
        case COMMA:
            return initToken(str, COMMA_tk, lineCnt, charCol);
        case COLON:
            return initToken(str, COLON_tk, lineCnt, charCol);
        case LPAREN:
            return initToken(str, LPAREN_tk, lineCnt, charCol);
        case RPAREN:
            return initToken(str, RPAREN_tk, lineCnt, charCol);
        case LBRACE:
            return initToken(str, LBRACE_tk, lineCnt, charCol);
        case RBRACE:
            return initToken(str, RBRACE_tk, lineCnt, charCol);
        case LBRACKET:
            return initToken(str, LBRACKET_tk, lineCnt, charCol);
        case RBRACKET:
            return initToken(str, RBRACKET_tk, lineCnt, charCol);
        case INITIAL:
        case CMT_ST_A:
        case CMT_ST_B:
        case CMT_END_A:
        case CMT_END_B:
        case FINAL:
        case ERROR:
        default: 
            exit(1);
    }
}

TokenRecord *getNextToken(Scanner *scanner, int &lineCnt, int &charCol) {
    State nextState;
    State state = INITIAL;
    State tempState;
    std::string str;
    int transition;

    while (state != FINAL) {
        transition = getTransitionFromChar(scanner->c);
        nextState = Table[state][transition];
        if(scanner->c == '\n' && state == INITIAL) {
            lineCnt++;
            charCol = 1;
            resetStartCol();
        }

        // Handle errors
        if (nextState == ERROR) {
            std::cout << "SCANNER ERROR: Unexpected character `" << scanner->c << "` (" << (int) scanner->c << ")"
                      << std::endl;
            exit(1);
        }

        if (nextState == FINAL) {
            return getTypedToken(state, str, lineCnt, charCol);
        } else if (nextState == EOF_) {
            return initToken("\0", EOF_tk, lineCnt, charCol);
        } else if (nextState == CMT_ST_A) {
            tempState = state; // save the current state when comment started
            state = nextState;
            advanceScanner(scanner, charCol);
        } else if (nextState == CMT_ST_B || nextState == CMT_END_A || nextState == CMT_END_B) {
            state = nextState == CMT_END_B ? tempState : nextState;
            advanceScanner(scanner, charCol);
        } else {
            state = nextState;
            if (!isspace(scanner->c)) {
                str += scanner->c;
            }
            advanceScanner(scanner, charCol);
        }
    }

    exit(1); // Error
}
