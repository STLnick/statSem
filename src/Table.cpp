//
// Created by Nick Ray on 3/7/21.
//
#include <ctype.h>

int getTransitionFromChar(char c) {
    if (isalpha(c)) return 0; // Letter
    if (isdigit(c)) return 1; // Digit
    if (isspace(c)) return 2; // Whitespace
    switch (c) {
        case '\0': // EOF
            return 3;
        case '>':
            return 4;
        case '=':
            return 5;
        case '_':
            return 6;
        case ':':
            return 7;
        case '<':
            return 8;
        case '+':
            return 9;
        case '-':
            return 10;
        case '*':
            return 11;
        case '/':
            return 12;
        case '%':
            return 13;
        case ';':
            return 14;
        case ',':
            return 15;
        case '.':
            return 16;
        case '(':
            return 17;
        case ')':
            return 18;
        case '{':
            return 19;
        case '}':
            return 20;
        case '[':
            return 21;
        case ']':
            return 22;
        case '$':
            return 23;
    }
}