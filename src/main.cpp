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

    // Setup / validate file to read from using keyboard input, input redirection or command line argument
    init(argc, argv, fileNameToRead);

    // Setup a file stream to assign src in scanner
    fileNameToRead += ".fs";

    std::ifstream srcFile(fileNameToRead.c_str());

    std::string srcString;
    readSrcIntoString(srcFile, srcString);

    // Initialize the Scanner
    Scanner *scanner = initScanner(srcString);

    /* ------------------------------------ */
    // Test Parser
    /* ------------------------------------ */

    node *root = NULL;
    root = parser(scanner);
    printPreorder(root);

    std::cout << "\n\nFile parsed successfully! Booyah!\n\n";

    /* ------------------------------------ */
    // Free memory
    /* ------------------------------------ */
    free(scanner);
    srcFile.close();

    return 0;
}
