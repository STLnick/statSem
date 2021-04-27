/*
 * Nick Ray
 * 2/15/21
 * scanner
 */
#include <cstdlib>
#include <fstream>
#include <istream>
#include <iostream>
#include "init.hpp"
#include "node.hpp"
#include "parseCommandLineOpts.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "statSem.hpp"
#include "statSemStack.hpp"
#include "TokenRecord.hpp"
#include "token.hpp"
#include "tree.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    std::string fileNameToRead;

    // Parse Command Line Options
    switch (parseCommandLineOpts(argc, argv)) {
        case -1:
            std::cout << "Invalid Usage - Terminating" << std::endl;
            return -1;
        case 1: // Help flag was used, gracefully exit
            return 0;
    }

    // Validate file to read from
    init(argc, argv, fileNameToRead);

    // Read file source into string
    fileNameToRead += ".fs";
    std::ifstream srcFile(fileNameToRead.c_str());
    std::string srcString;
    readSrcIntoString(srcFile, srcString);

    /* ------------------------------------ */
    // Scanner + Parser
    /* ------------------------------------ */
    Scanner *scanner = initScanner(srcString);
    //node *root = NULL;
    node *root = parser(scanner);
    printPreorder(root);

    /* ------------------------------------ */
    // Static Semantics
    /* ------------------------------------ */
    StatSemStack stack;
    statSem(root, stack, 0);

    /* ------------------------------------ */
    // Awesome Success Message
    /* ------------------------------------ */
    std::cout << std::endl << getRandomSuccessMessage() << std::endl << std::endl;

    // Free memory
    free(scanner);
    srcFile.close();

    return 0;
}
