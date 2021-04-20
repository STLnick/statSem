//
// Created by Nick Ray on 4/19/21.
//

#ifndef STATSEM_STATSEMSTACKITEM_HPP
#define STATSEM_STATSEMSTACKITEM_HPP

struct StatSemStackItem {
    std::string name; // The identifying string value for the identifier
    int charCol;      // Column on line token begins
    int lineNum;      // Line number which the token is on in source

    StatSemStackItem(std::string _name, int _charCol, int _lineNum) {
        name = _name;
        charCol = _charCol;
        lineNum = _lineNum;
    }
};

#endif //STATSEM_STATSEMSTACKITEM_HPP
