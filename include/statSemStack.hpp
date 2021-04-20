//
// Created by Nick Ray on 4/17/21.
//

#ifndef STATSEM_STATSEMSTACK_HPP
#define STATSEM_STATSEMSTACK_HPP

#include "statSemStackItem.hpp"

class StatSemStack {
private:
    std::vector<StatSemStackItem*> items;
    bool hasNotBeenSetFalse;
    bool isGlobal;
public:
    StatSemStack();
    bool getHasNotBeenSetFalse();
    void setHasNotBeenSetFalse(bool val);
    void setIsGlobal(bool val);
    void push(StatSemStackItem &item);
    void pop();
    int find(std::string bufferName);
};

#endif //STATSEM_STATSEMSTACK_HPP
