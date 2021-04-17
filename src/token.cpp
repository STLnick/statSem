#include <iostream>
#include <string>
#include "TokenRecord.hpp"

void printToken(TokenRecord *token) {
    std::cout << "[" << tokenNames[token->tokenId] << "] '" << token->stringVal
    << "' on line " << token->lineNum
    << " at column " << token->charCol << std::endl;
}

TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum, int charCol) {
    static int startCol = 1;

    if (name == "RESET_START_COL") {
        startCol = 1;
        return NULL;
    }

    TokenRecord *newToken = new TokenRecord();
    newToken->stringVal = name;
    newToken->tokenId = tokenId;
    newToken->lineNum = lineNum;
    newToken->charCol = startCol;

    startCol = charCol;
    return newToken;
}

void resetStartCol() {
    TokenRecord *throwaway = initToken("RESET_START_COL", ID_tk, 0, 1);
}
