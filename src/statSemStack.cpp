//
// Created by Nick Ray on 4/17/21.
//

#include <iostream>
#include <vector>
#include "statSem.hpp"
#include "statSemStack.hpp"

StatSemStack::StatSemStack() {
        hasNotBeenSetFalse = true;
        isGlobal = true;
    }

bool StatSemStack::getHasNotBeenSetFalse() {
    return hasNotBeenSetFalse;
}

void StatSemStack::setHasNotBeenSetFalse(bool val) {
    hasNotBeenSetFalse = val;
}

void StatSemStack::setIsGlobal(bool val) {
    isGlobal = val;
}

void StatSemStack::push(StatSemStackItem &item) {
    items.push_back(&item);
}

void StatSemStack::pop() {
    items.pop_back();
}

int StatSemStack::find(std::string bufferName) {
    std::vector<StatSemStackItem*>::iterator iter = items.begin();

    for (; iter != items.end(); ++iter) {
        if (bufferName == (*iter)->name) {
            return (*iter)->lineNum;
        }
    }

    return -1;
}