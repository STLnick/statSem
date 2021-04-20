//
// Created by Nick Ray on 4/16/21.
//
#include <iostream>
#include "node.hpp"
#include "statSem.hpp"
#include "statSemStack.hpp"
#include "statSemStackItem.hpp"

bool hasPassedMainToken(node *treeNode) {
    return treeNode->label == "program_nt" && treeNode->tokens[1].stringVal == "main";
}

void printErrorAndExit(std::string varName, int line) {
    std::cout << varName << " already declared on line " << line << std::endl;
    exit(1);
}

void statSem(node *treeNode, StatSemStack stack, int level) {
    int varCount = 0;

    if (treeNode->label == "vars_nt") {
        int declaredLineNum = stack.find(treeNode->tokens[1].stringVal);

        if (declaredLineNum != -1) {
            // error - already declared
            printErrorAndExit(treeNode->tokens[1].stringVal, declaredLineNum);
        }

        StatSemStackItem newItem = StatSemStackItem(
                treeNode->tokens[1].stringVal,
                treeNode->tokens[1].charCol,
                treeNode->tokens[1].lineNum
            );

        stack.push(newItem);
        varCount++;

        // ? Debugging
        std::cout << treeNode->tokens[1].stringVal
                    << " " << treeNode->tokens[2].stringVal
                    << " " << treeNode->tokens[3].stringVal << std::endl << std::endl;
    }

    if (treeNode->ntOne != NULL) {
        statSem(treeNode->ntOne, stack, level + 1);
    }

    if (stack.getHasNotBeenSetFalse() && hasPassedMainToken(treeNode)) {
        stack.setHasNotBeenSetFalse(false);
        stack.setIsGlobal(false);
    }

    if (treeNode->ntTwo != NULL) {
        statSem(treeNode->ntTwo, stack, level + 1);
    }

    if (treeNode->ntThree != NULL) {
        statSem(treeNode->ntThree, stack, level + 1);
    }

    if (treeNode->ntFour != NULL) {
        statSem(treeNode->ntFour, stack, level + 1);
    }

    // pop for varCount times
    std::cout << "varCount: " << varCount << std::endl;
    int i;
    for (i = 0; i < varCount; i++) {
        stack.pop();
    }
}