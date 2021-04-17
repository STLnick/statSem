//
// Created by Nick Ray on 3/7/21.
//
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

void init(int argc, char **argv, std::string &fileNameToRead) {
    std::string buffer;
    // Read in input if needed and set the filename to be read depending on arguments
    /*  ./frontEnd or ./frontEnd < filename  */
    if (argc == 1) {
        std::ofstream tempFile;
        // Open temp file to hold user input or redirected file input
        try {
            tempFile.open("output.fs");
        }
        catch (int e) {
            std::cerr << "Failed to open the temp file for writing!" << std::endl;
            exit(1);
        }

        std::cout
                << "Preparing to read in input (if using keyboard type "
                   "'ctrl + d' on *nix systems and 'ctrl + z' for Windows to finish)"
                << std::endl;

        // While there is input from user/file write it to new file
        try {
            while (std::cin >> buffer) {
                tempFile << buffer << std::endl;
            }
        } catch (int e) {
            std::cerr << "Error while reading from buffer and writing to file!" << std::endl;
        }

        tempFile.close();

        fileNameToRead = "output";
        /*  ./frontEnd filename  */
    } else if (argc == 2) {
        fileNameToRead = argv[1];
        int dotIndex = fileNameToRead.find('.');

        // IF this filename has a '.' -> make sure the extension is fs and just store filename no extension
        if (dotIndex != -1) {
            std::string fileExt = fileNameToRead.substr(dotIndex);

            if (fileExt.compare(".fs") != 0) {
                std::cerr << "Incorrect file type provided - must use file extension '.fs'" << std::endl;
                exit(1);
            }

            fileNameToRead.erase(dotIndex, std::string::npos);
        }
    } else {
        std::cout << "Incorrect invocation of program! Try again or execute './P0 -h' to view the help info"
                  << std::endl;
        exit(1);
    }
}
