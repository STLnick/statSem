//
// Created by Nick Ray on 4/16/21.
//

#ifndef STATSEM_STATSEM_HPP
#define STATSEM_STATSEM_HPP

#include "node.hpp"
#include "statSemStack.hpp"

void setIsGlobalFalse();
void statSem(node *treeNode, StatSemStack stack, int level);

#endif //STATSEM_STATSEM_HPP
