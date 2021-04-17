#include <iostream>
#include <string>
#include "TokenRecord.hpp"

void printToken(TokenRecord *token) {
    std::cout << "[" << tokenNames[token->tokenId] << "] '" << token->stringVal
    << "' on line " << token->lineNum
    << " at column " << token->charCol << std::endl;
}

static int startCol = 1;

TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum, int charCol) {
    TokenRecord *newToken = new TokenRecord();
    newToken->stringVal = name;
    newToken->tokenId = tokenId;
    newToken->lineNum = lineNum;
    newToken->charCol = startCol;

    startCol = charCol;
    return newToken;
}

void resetStartCol() {
    startCol = 1;
}
