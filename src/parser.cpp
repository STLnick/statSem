//
// Created by Nick Ray on 3/27/21.
//
#include <cstdlib>
#include <iostream>
#include "node.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "tree.hpp"
#include "TokenRecord.hpp"

node* parser(Scanner *scanner) {
    int charCol = 1;
    int lineCount = 1;
    node *root = NULL;
    root = initNode("parser", root);

    TokenRecord *token = getNextToken(scanner, lineCount, charCol);

    root->tokens.push_back("<program>");
    root->ntOne = program_nt(scanner, token, lineCount, charCol); // Grandpappy non-terminal processing

    if (token->tokenId != EOF_tk) {
        printErrorAndExit("End of File", token->tokenId, token->lineNum, token->charCol);
    }

    return root;
}

/*  <program> -> <vars> main <block>  */
/*  first( <program> ) : { data, main }  */
node* program_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("program_nt", treeNode);

    treeNode->tokens.push_back("<vars>");
    treeNode->ntOne = vars_nt(scanner, token, lineCount, charCol);

    checkAndConsumeTerminal(scanner, token, lineCount, MAIN_tk, treeNode, charCol);

    treeNode->tokens.push_back("<block>");
    treeNode->ntTwo = block_nt(scanner, token, lineCount, charCol);

    return treeNode; // explicit return
}

/*  <block> -> begin <vars> <stats> end  */
/*  first( <block> ) : { begin }  */
node* block_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("block_nt", treeNode);

    if (token->tokenId == BEGIN_tk) { // [Predict] begin <vars> <stats> end
        treeNode->tokens.push_back(token->stringVal);
        token = getNextToken(scanner, lineCount, charCol); // consume BEGIN_tk

        treeNode->tokens.push_back("<vars>");
        treeNode->ntOne = vars_nt(scanner, token, lineCount, charCol);

        treeNode->tokens.push_back("<stats>");
        treeNode->ntTwo = stats_nt(scanner, token, lineCount, charCol);

        checkAndConsumeTerminal(scanner, token, lineCount, END_tk, treeNode, charCol);

        return treeNode; // explicit return
    } else {
        printErrorAndExit("begin", token->tokenId, token->lineNum, token->charCol);
    }
}

/*  <vars> -> ε | data Identifier := Integer ; <vars>  */
/*  first( <vars> ) : { data }  */
node* vars_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("vars_nt", treeNode);

    if (token->tokenId == DATA_tk) { // [Predict] data Identifier := Integer ; <vars>
        treeNode->tokens.push_back(token->stringVal);
        token = getNextToken(scanner, lineCount, charCol); // consume DATA_tk token

        checkAndConsumeTerminal(scanner, token, lineCount, ID_tk, treeNode, charCol);

        checkAndConsumeTerminal(scanner, token, lineCount, COLONEQ_tk, treeNode, charCol);

        checkAndConsumeTerminal(scanner, token, lineCount, NUM_tk, treeNode, charCol);

        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);

        treeNode->tokens.push_back("<vars>");
        treeNode->ntOne = vars_nt(scanner, token, lineCount, charCol); // vars_nt()

        return treeNode; // explicit return
    } else { // [Predict] ε
        return NULL;
    }
}

/*  <expr> -> <N> - <expr> | <N>  */
/*  first( <expr> ) : { first(N) }  */
// process <N> - then check for '-' to choose production
node* expr_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("expr_nt", treeNode);

    treeNode->tokens.push_back("<N>");
    treeNode->ntOne = N_nt(scanner, token, lineCount, charCol);

    if (token->tokenId == MINUS_tk) { // [Predict] <N> - <expr>
        checkAndConsumeTerminal(scanner, token, lineCount, MINUS_tk, treeNode, charCol);
        treeNode->tokens.push_back("<expr>");
        treeNode->ntTwo = expr_nt(scanner, token, lineCount, charCol);
    }

    return treeNode; // explicit return
}

/*  <N> -> <A> / <N> | <A> * <N> | <A>  */
/*  first( <N> ) : { first(A) }  */
node* N_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("N_nt", treeNode);

    treeNode->tokens.push_back("<A>");
    treeNode->ntOne = A_nt(scanner, token, lineCount, charCol);

    if (token->tokenId == DIVIDE_tk) { // [Predict] <A> / <N>
        checkAndConsumeTerminal(scanner, token, lineCount, DIVIDE_tk, treeNode, charCol);
        treeNode->tokens.push_back("<N>");
        treeNode->ntTwo = N_nt(scanner, token, lineCount, charCol);
    } else if (token->tokenId == MULT_tk) { // [Predict] <A> * <N>
        checkAndConsumeTerminal(scanner, token, lineCount, MULT_tk, treeNode, charCol);
        treeNode->tokens.push_back("<N>");
        treeNode->ntTwo = N_nt(scanner, token, lineCount, charCol);
    }

    return treeNode; // explicit return
}

/*  <A> -> <M> + <A> | <M>  */
/*  first( <A> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
node* A_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("A_nt", treeNode);

    treeNode->tokens.push_back("<M>");
    treeNode->ntOne = M_nt(scanner, token, lineCount, charCol);

    if (token->tokenId == PLUS_tk) { // [Predict] <M> + <A>
        checkAndConsumeTerminal(scanner, token, lineCount, PLUS_tk, treeNode, charCol);
        treeNode->tokens.push_back("<A>");
        treeNode->ntTwo = A_nt(scanner, token, lineCount, charCol);
    }

    return treeNode; // explicit return
}

/*  <M> -> * <M> | <R>  */
/*  first( <M> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
node* M_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("M_nt", treeNode);

    if (token->tokenId == MULT_tk) { // [Predict] * <M>
        checkAndConsumeTerminal(scanner, token, lineCount, MULT_tk, treeNode, charCol);
        treeNode->tokens.push_back("<M>");
        treeNode->ntOne = M_nt(scanner, token, lineCount, charCol);
    } else if ( isInFirstOfR(token->tokenId) ) { // [Predict] <R>
        treeNode->tokens.push_back("<R>");
        treeNode->ntOne = R_nt(scanner, token, lineCount, charCol);
    } else {
        printErrorAndExit("* / Left Parenthesis / Identifier / Integer", token->tokenId, token->lineNum, token->charCol);
    }

    return treeNode; // explicit return
}

/*  <R> -> ( <expr> ) | Identifier | Integer  */
/*  first( <R> ) : { '( <expr> )': '(', 'Identifier': Identifier, 'Integer': Integer/Number }  */
node* R_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("R_nt", treeNode);

    if (token->tokenId == LPAREN_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, LPAREN_tk, treeNode, charCol);
        treeNode->tokens.push_back("<expr>");
        treeNode->ntOne = expr_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, RPAREN_tk, treeNode, charCol);
    } else if (token->tokenId == ID_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, ID_tk, treeNode, charCol);
    } else if (token->tokenId == NUM_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, NUM_tk, treeNode, charCol);
    } else {
        printErrorAndExit("Left Parenthesis / Identifier / Integer", token->tokenId, token->lineNum, token->charCol);
    }

    return treeNode; // explicit return
}

/*  <stats> -> <stat> <mStat>  */
/*  first( <stats> ) : { '<stat> <mStat>': [getter, outter, begin, if, loop, assign, proc, void] }  */
node* stats_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("stats_nt", treeNode);

    treeNode->tokens.push_back("<stat>");
    treeNode->ntOne = stat_nt(scanner, token, lineCount, charCol);
    treeNode->tokens.push_back("<mStat>");
    treeNode->ntTwo =  mStat_nt(scanner, token, lineCount, charCol);

    return treeNode; // explicit return
}

/*  <mStat> -> ε | <stat> <mStat>  */
/*  first( <mStat> ) : { '<stat> <mStat>': [getter, outter, begin, if, loop, assign, proc, void] }  */
node* mStat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("mStat_nt", treeNode);

    if ( isInFirstOfStat(token->tokenId) ) { // [Predict] <stat> <mStat>
        treeNode->tokens.push_back("<stat>");
        treeNode->ntOne = stat_nt(scanner, token, lineCount, charCol);
        treeNode->tokens.push_back("<mStat>");
        treeNode->ntTwo = mStat_nt(scanner, token, lineCount, charCol);
        return treeNode; // explicit return
    } else { // [Predict] ε
        return NULL; // explicit return
    }
}

/*  <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; |  */
/*  first( <stat> ) : { '<in>': getter, '<out>': outter, '<block>': begin, '<if>': if,
 *                      '<loop>': loop, '<assign>': assign, '<goto>': proc, '<label>': void }  */
node* stat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("stat_nt", treeNode);

    if (token->tokenId == GETTER_tk) {
        treeNode->tokens.push_back("<in>");
        treeNode->ntOne = in_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else if (token->tokenId == OUTTER_tk) {
        treeNode->tokens.push_back("<out>");
        treeNode->ntOne = out_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else if (token->tokenId == BEGIN_tk) {
        treeNode->tokens.push_back("<block>");
        treeNode->ntOne = block_nt(scanner, token, lineCount, charCol);
    } else if (token->tokenId == IF_tk) {
        treeNode->tokens.push_back("<if>");
        treeNode->ntOne = if_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else if (token->tokenId == LOOP_tk) {
        treeNode->tokens.push_back("<loop>");
        treeNode->ntOne = loop_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else if (token->tokenId == ASSIGN_tk) {
        treeNode->tokens.push_back("<assign>");
        treeNode->ntOne = assign_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else if (token->tokenId == PROC_tk) {
        treeNode->tokens.push_back("<goto>");
        treeNode->ntOne = goto_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else if (token->tokenId == VOID_tk) {
        treeNode->tokens.push_back("<label>");
        treeNode->ntOne = label_nt(scanner, token, lineCount, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk, treeNode, charCol);
    } else {
        printErrorAndExit("getter/outter/begin/if/loop/assign/proc/void", token->tokenId, token->lineNum, token->charCol);
    }

    return treeNode; // explicit return
}

/*  <in> -> getter Identifier  */
/*  first( <in> ) : { getter }  */
node* in_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("in_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, GETTER_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk, treeNode, charCol);
    return treeNode; // explicit return
}

/*  <out> -> outter <expr>  */
/*  first( <out> ) : { outter }  */
node* out_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("out_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, OUTTER_tk, treeNode, charCol);
    treeNode->tokens.push_back("<expr>");
    treeNode->ntOne = expr_nt(scanner, token, lineCount, charCol);
    return treeNode; // explicit return
}

/*  <if> -> if [ <expr> <RO> <expr> ] then <stat> */
/*  first( <if> ) : { if }  */
node* if_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("if_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, IF_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, LBRACKET_tk, treeNode, charCol);

    treeNode->tokens.push_back("<expr>");
    treeNode->ntOne = expr_nt(scanner, token, lineCount, charCol);
    treeNode->tokens.push_back("<R0>");
    treeNode->ntTwo = RO_nt(scanner, token, lineCount, charCol);
    treeNode->tokens.push_back("<expr>");
    treeNode->ntThree = expr_nt(scanner, token, lineCount, charCol);

    checkAndConsumeTerminal(scanner, token, lineCount, RBRACKET_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, THEN_tk, treeNode, charCol);

    treeNode->tokens.push_back("<stat>");
    treeNode->ntFour = stat_nt(scanner, token, lineCount, charCol);

    return treeNode; // explicit return
}

/*  <loop> -> loop [ <expr> <RO> <expr> ] then <stat>  */
/*  first( <loop> ) : { loop }  */
node* loop_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("loop_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, LOOP_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, LBRACKET_tk, treeNode, charCol);

    treeNode->tokens.push_back("<expr>");
    treeNode->ntOne = expr_nt(scanner, token, lineCount, charCol);
    treeNode->tokens.push_back("<R0>");
    treeNode->ntTwo = RO_nt(scanner, token, lineCount, charCol);
    treeNode->tokens.push_back("<expr>");
    treeNode->ntThree = expr_nt(scanner, token, lineCount, charCol);

    checkAndConsumeTerminal(scanner, token, lineCount, RBRACKET_tk, treeNode, charCol);

    treeNode->tokens.push_back("<stat>");
    treeNode->ntFour = stat_nt(scanner, token, lineCount, charCol);

    return treeNode; // explicit return
}

/*  <assign> -> assign Identifier := <expr>  */
/*  first( <assign> ) : { assign }  */
node* assign_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("assign_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, ASSIGN_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, COLONEQ_tk, treeNode, charCol);
    treeNode->tokens.push_back("<expr>");
    treeNode->ntOne = expr_nt(scanner, token, lineCount, charCol);
    return treeNode; // explicit return
}

/*  <RO> -> => | =< | == | [ == ] (three tokens) | %  */
/*  first( <R0> ) : { =, %, [ }  */
node* RO_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("R0_nt", treeNode);

    if (token->tokenId == GTEQ_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, GTEQ_tk, treeNode, charCol);
    } else if (token->tokenId == LTEQ_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, LTEQ_tk, treeNode, charCol);
    } else if (token->tokenId == EQ_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, EQ_tk, treeNode, charCol);
    } else if (token->tokenId == LBRACKET_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, LBRACKET_tk, treeNode, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, EQ_tk, treeNode, charCol);
        checkAndConsumeTerminal(scanner, token, lineCount, RBRACKET_tk, treeNode, charCol);
    } else if (token->tokenId == MOD_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, MOD_tk, treeNode, charCol);
    } else {
        printErrorAndExit("=> / =< / == / [ == ] / %", token->tokenId, token->lineNum, token->charCol);
    }

    return treeNode; // explicit return
}

/*  <label> -> void Identifier  */
/*  first( <label> ) : { void }  */
node* label_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("label_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, VOID_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk, treeNode, charCol);

    return treeNode; // explicit return
}

/*  <goto> -> proc Identifier  */
/*  first( <goto> ) : { proc }  */
node* goto_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol) {
    node* treeNode = NULL;
    treeNode = initNode("goto_nt", treeNode);

    checkAndConsumeTerminal(scanner, token, lineCount, PROC_tk, treeNode, charCol);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk, treeNode, charCol);

    return treeNode; // explicit return
}

void checkAndConsumeTerminal(Scanner *scanner, TokenRecord *&token, int &lineCount, tokenID targetId, node* treeNode, int &charCol) {
    if (token->tokenId == targetId) {
        treeNode->tokens.push_back(token->stringVal);
        token = getNextToken(scanner, lineCount, charCol);
    } else {
        printErrorAndExit(tokenNames[targetId], token->tokenId, token->lineNum, token->charCol);
    }
}

int isInFirstOfR(tokenID id) {
    const tokenID rFirsts[] = {
            LPAREN_tk,
            ID_tk,
            NUM_tk
    };
    int len = sizeof(rFirsts) / sizeof(rFirsts[0]);
    int i;

    for(i = 0; i < len; i++) {
        if (rFirsts[i] == id) return 1;
    }

    return 0;
}

int isInFirstOfStat(tokenID id) {
    const tokenID statFirsts[] = {
            GETTER_tk,
            OUTTER_tk,
            BEGIN_tk,
            IF_tk,
            LOOP_tk,
            ASSIGN_tk,
            PROC_tk,
            VOID_tk
    };
    int len = sizeof(statFirsts) / sizeof(statFirsts[0]);
    int i;

    for(i = 0; i < len; i++) {
        if (statFirsts[i] == id) return 1;
    }

    return 0;
}

void printErrorAndExit(std::string expected, tokenID received, int line, int column) {
    std::cout   << "ERROR: Expected '" << expected << "' on line " << line
                << " at column " << column
                << " but received '" << tokenLiterals[received] << "' instead." << std::endl;
    exit(1);
}
