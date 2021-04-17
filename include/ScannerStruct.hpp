//
// Created by Nick Ray on 2/21/21.
//

#ifndef SCANNER_SCANNER_STRUCT_HPP
#define SCANNER_SCANNER_STRUCT_HPP

#include <string>

typedef struct {
    std::string *src; // String created from source code
    char c;           // Current character
    unsigned int i;   // Current index
} Scanner;

#endif //SCANNER_SCANNER_STRUCT_HPP
