#include "FileUtils.h"

void writeUserInputToFile(const std::string &path)
{
    // BEGIN: 1a
    std::ofstream outputStream{path};
    std::cout << "Write some words, they will be output in the file \"" << path << "\", every word on separate lines. quit exits" << std::endl;
    std::string word;
    while (std::cin >> word) {
        if (word == "quit") {
            break;
        }
        outputStream << word << std::endl;
    }
    // END: 1a
}

void addLineNumbers(const std::string &filename)
{
    // BEGIN: 1b
    std::ifstream inputStream{filename};
    if (!inputStream) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }
    std::string outputFilename = filename + ".linum";
    std::ofstream outputStream{outputFilename};
    std::string line;
    int lineNumber = 1;
    while (std::getline(inputStream, line)) {
        outputStream << lineNumber << ": " << line << std::endl;
        lineNumber++;
    }
    // END: 1b
}