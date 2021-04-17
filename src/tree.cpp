//
// Created by Nick Ray on 4/8/21.
//

#include <iostream>
#include <fstream>
#include "node.hpp"

node* initNode(std::string str, node* treeNode) {
    treeNode = new node;
    treeNode->label = str;
    treeNode->ntOne = treeNode->ntTwo = treeNode->ntThree = treeNode->ntFour = NULL;

    return treeNode;
}

void printPreorder(node* treeNode, int level = 0) {
    if (treeNode == NULL) return;

    // Print tokens by node label
    std::cout << "\e[1m" << std::string(level * 2, ' ') + treeNode->label + ": " << "\e[0m";
    for(int i = 0; i < treeNode->tokens.size(); i++) {
        std::cout << treeNode->tokens[i] << " ";
    }
    std::cout << std::endl;

    if (treeNode->ntOne != NULL) {
        printPreorder(treeNode->ntOne, level + 1);
    }

    if (treeNode->ntTwo != NULL) {
        printPreorder(treeNode->ntTwo, level + 1);
    }

    if (treeNode->ntThree != NULL) {
        printPreorder(treeNode->ntThree, level + 1);
    }

    if (treeNode->ntFour != NULL) {
        printPreorder(treeNode->ntFour, level + 1);
    }

}
