//
// Created by Nick Ray on 4/8/21.
//

#ifndef PARSER_TREE_HPP
#define PARSER_TREE_HPP

#include "node.hpp"

node* initNode(std::string str, node* node);
void printPreorder(node* treeNode, int level = 0);

#endif //PARSER_TREE_HPP
