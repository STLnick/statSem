//
// Created by Nick Ray on 4/16/21.
//
#include <cstdlib>
#include <iostream>
#include "node.hpp"
#include "statSem.hpp"
#include "statSemStack.hpp"
#include "statSemStackItem.hpp"

bool hasPassedMainToken(node *treeNode) {
    return treeNode->label == "program_nt" && treeNode->tokens[0].stringVal == "main";
}

// dup error by default --- not declared error will require 3rd arg of 1
void printErrorAndExit(std::string varName, int line, bool isDuplicateError = true) {
    if (isDuplicateError) {
        std::cout << "[ERROR]: " << varName << " already declared on line " << line << std::endl;
    } else {
        std::cout << "[ERROR]: " << varName << " not declared before being used on line " << line << std::endl;
    }

    exit(1);
}

void statSem(node *treeNode, StatSemStack &stack, int level) {
    if (treeNode->label == "block_nt") {
        std::cout << "Pre pushBlock()" << std::endl;
        stack.pushBlock();
        std::cout << "Post pushBlock()" << std::endl;
    }

    if (treeNode->label == "vars_nt") {
        int declaredLineNum = stack.find(treeNode->tokens[1].stringVal);

        if (declaredLineNum != -1) {
            // error - already declared
            printErrorAndExit(treeNode->tokens[1].stringVal, declaredLineNum);
        }

       StatSemStackItem* newItem = new StatSemStackItem(
                treeNode->tokens[1].stringVal,
                treeNode->tokens[1].charCol,
                treeNode->tokens[1].lineNum
            );

        stack.push(newItem);
    } else { // Check that all ID_tk's used have been declared
        int found = 1;
        int i;

        for (i = 0; i < treeNode->tokens.size(); i++) {
            if (treeNode->tokens[i].tokenId == ID_tk) {
                found = stack.find(treeNode->tokens[i].stringVal);
                if (found == -1) {
                    printErrorAndExit(treeNode->tokens[i].stringVal, treeNode->tokens[i].lineNum, false);
                }
            }
        }
    }

    if (treeNode->ntOne != NULL) {
        statSem(treeNode->ntOne, stack, level + 1);
    }

    std::cout << ">>> 1" << std::endl;

    // Check after first node to allow <program> to process first set of <vars>
    if (stack.getHasNotBeenSetFalse() && hasPassedMainToken(treeNode)) {
        stack.setHasNotBeenSetFalse(false);
        stack.setIsGlobal(false);
    }

    std::cout << ">>> 2" << std::endl;
    if (treeNode->ntTwo != NULL) {
        statSem(treeNode->ntTwo, stack, level + 1);
    }

    if (treeNode->ntThree != NULL) {
        statSem(treeNode->ntThree, stack, level + 1);
    }

    if (treeNode->ntFour != NULL) {
        statSem(treeNode->ntFour, stack, level + 1);
    }

    if (treeNode->label == "block_nt") {
        while (stack.getItemsSize() > 0 && stack.isNotOnBlockStop()) {
            stack.pop();
        }
        stack.pop(); // Remove BLOCK_STOP fake item
    }
}
