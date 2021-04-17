#ifndef SCANNER_TOKEN_HPP
#define SCANNER_TOKEN_HPP

#include "TokenRecord.hpp"

TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum, int charCol);

void printToken(TokenRecord *token);
void resetStartCol();

#endif // !SCANNER_TOKEN_HPP
