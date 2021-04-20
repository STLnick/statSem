//
// Created by Nick Ray on 4/8/21.
//

#ifndef PARSER_NODE_HPP
#define PARSER_NODE_HPP

#include <vector>
#include "TokenRecord.hpp"

struct node {
    std::string label;
    std::vector<TokenRecord> tokens;
    node* ntOne;
    node* ntTwo;
    node* ntThree;
    node* ntFour;
};

#endif //PARSER_NODE_HPP
