//
// Created by Nick Ray on 2/21/21.
//
#include <istream>
#include <string>
#include <time.h>
#include <vector>

void readSrcIntoString(std::istream &srcFile, std::string &src) {
    src.assign((std::istreambuf_iterator<char>(srcFile)),
               (std::istreambuf_iterator<char>()));
    src += '\0'; // Manually add null terminator for easier parsing of EOF token
}

std::string getRandomSuccessMessage() {
    srand (time(NULL));
    int randomInt = rand() % 6;
    switch (randomInt) {
        case 0:
            return "File successfully parsed! Booyah!!";
        case 1:
            return "Much wow! Such parse!";
        case 2:
            return "Ya did good kid...";
        case 3:
            return "Welp... works on this machine at least!";
        case 4:
            return "Success! This program execution is now PARSED tense! LOL";
        default:
            return "Default Success Message. Yay.";
    };
}