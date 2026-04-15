#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <print>

class DeCipher
{
private:
    char* csvFileContents = nullptr;
    size_t fileContentsSizeInBytes = 0;
    size_t nextCharacterIndexToProcess = 0;

    const unsigned int maxDecodedMessageLength = 2048;
    char* decodedMessage = nullptr;
    size_t nextDecodedCharacterIndex = 0;

public:
    explicit DeCipher(const std::filesystem::path& filename);
    ~DeCipher();

    void jumpToStartOfNextLine();
    void jumpToStartOfNextOddLine();
    void getLastWordOnCurrentLine(char*& lastWord, int& lengthOfWord);
    void decodeCipher(int ROTKey);
    std::string getDecodedMessage();

    void benchmarkSpeed();

};
