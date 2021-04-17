//
// Created by Nick Ray on 2/21/21.
//

#ifndef SCANNER_SCANNER_HPP
#define SCANNER_SCANNER_HPP

#include "ScannerStruct.hpp"
#include "TokenRecord.hpp"

void advanceScanner(Scanner *scanner, int &charCol);

Scanner *initScanner(std::string &src);

TokenRecord *getNextToken(Scanner *scanner, int &lineCnt, int &charCol);

#endif //SCANNER_SCANNER_HPP
