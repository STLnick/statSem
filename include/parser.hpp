//
// Created by Nick Ray on 3/27/21.
//

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP
#include "scanner.hpp"

node* parser(Scanner *scanner);
node* program_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* block_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* vars_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* expr_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* N_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* A_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* M_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* R_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* stats_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* mStat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* stat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* in_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* out_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* if_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* loop_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* assign_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* RO_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* label_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
node* goto_nt(Scanner *scanner, TokenRecord *&token, int &lineCount, int &charCol);
void checkAndConsumeTerminal(Scanner *scanner, TokenRecord *&token, int &lineCount, tokenID targetId, node* treeNode, int &charCol);
int isInFirstOfR(tokenID id);
int isInFirstOfStat(tokenID id);
void printErrorAndExit(std::string expected, tokenID received, int line, int column);

#endif //PARSER_PARSER_HPP
