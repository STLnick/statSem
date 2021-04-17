//
// Created by Nick Ray on 2/21/21.
//
#include <istream>
#include <string>

void readSrcIntoString(std::istream &srcFile, std::string &src) {
    src.assign((std::istreambuf_iterator<char>(srcFile)),
               (std::istreambuf_iterator<char>()));
    src += '\0'; // Manually add null terminator for easier parsing of EOF token
}