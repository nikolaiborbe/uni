#include "CCipher.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>

DeCipher::DeCipher(const std::filesystem::path& filename) {
    std::ifstream fileStream{filename, std::ios::binary}; // std::ios::binary for å unngå rare newline-konverteringer på Windows
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
    }

    decodedMessage = new char[maxDecodedMessageLength];

    // Leser inn hele CSV-filen i én stor buffer.
    // Denne "dump hele fila i minnet"-metoden er ofte mye raskere
    // enn å lese ord for ord / linje for linje med strømmer.
    // (Ikke pensum, men nyttig å se at det finnes.)
    fileContentsSizeInBytes = std::filesystem::file_size(filename);
    csvFileContents = new char[fileContentsSizeInBytes];
    fileStream.read(csvFileContents, fileContentsSizeInBytes);
}

DeCipher::~DeCipher() {
    delete[] csvFileContents;
    delete[] decodedMessage;
}


void DeCipher::jumpToStartOfNextLine() {
    // BEGIN: 4b
    while (nextCharacterIndexToProcess < fileContentsSizeInBytes && csvFileContents[nextCharacterIndexToProcess] != '\n') {
        nextCharacterIndexToProcess++;
    }
    if (nextCharacterIndexToProcess < fileContentsSizeInBytes) {
        nextCharacterIndexToProcess++; // skip past the '\n'
    }
    // END: 4b
}

void DeCipher::jumpToStartOfNextOddLine() {
    // BEGIN: 4c
    jumpToStartOfNextLine();
    jumpToStartOfNextLine();
    // END: 4c
}

void DeCipher::getLastWordOnCurrentLine(char*& lastWord, int& lengthOfWord) {
    // BEGIN: 4d
    // Find the end of the current line (or end of file)
    size_t lineEnd = nextCharacterIndexToProcess;
    while (lineEnd < fileContentsSizeInBytes && csvFileContents[lineEnd] != '\n') {
        lineEnd++;
    }

    // Go backwards from lineEnd to find the last comma
    size_t pos = lineEnd;
    // Skip newline if present
    if (pos > nextCharacterIndexToProcess && pos > 0) {
        pos--; // we're now at last char of line (or just before \n)
    }

    // Find the last comma
    size_t lastComma = nextCharacterIndexToProcess; // default to start if no comma
    for (size_t i = nextCharacterIndexToProcess; i < lineEnd; i++) {
        if (csvFileContents[i] == ',') {
            lastComma = i;
        }
    }

    // The last word starts after the last comma
    size_t wordStart = lastComma + 1;
    // But if there was no comma found (lastComma == nextCharacterIndexToProcess and char is not ','),
    // then the whole line is one word
    if (csvFileContents[lastComma] != ',') {
        wordStart = nextCharacterIndexToProcess;
    }

    lastWord = &csvFileContents[wordStart];
    lengthOfWord = static_cast<int>(lineEnd - wordStart);
    // END: 4d
}

void DeCipher::decodeCipher(int ROTKey){
    // BEGIN: 4e
    nextCharacterIndexToProcess = 0;
    nextDecodedCharacterIndex = 0;

    // We start on line 1 (odd). Process odd lines only.
    while (nextCharacterIndexToProcess < fileContentsSizeInBytes) {
        char* lastWord = nullptr;
        int lengthOfWord = 0;
        getLastWordOnCurrentLine(lastWord, lengthOfWord);

        // Check if the length of the word is even (partall)
        if (lengthOfWord % 2 == 0) {
            // Decode each character with ROTKey and add to decodedMessage
            for (int i = 0; i < lengthOfWord; i++) {
                char c = lastWord[i];
                if (c >= 'A' && c <= 'Z') {
                    c = static_cast<char>('A' + (c - 'A' + 26 - ROTKey) % 26);
                } else if (c >= 'a' && c <= 'z') {
                    c = static_cast<char>('a' + (c - 'a' + 26 - ROTKey) % 26);
                }
                decodedMessage[nextDecodedCharacterIndex++] = c;
            }
        }

        // Jump to next odd line (skip even line)
        jumpToStartOfNextOddLine();
    }
    // END: 4e
}

std::string DeCipher::getDecodedMessage() {
    // Må legge inn en nullterminator slik at std::string tolker C-stringen riktig
    decodedMessage[nextDecodedCharacterIndex] = '\0';
    return std::string(decodedMessage);
}

void DeCipher::benchmarkSpeed() {
    std::cout << "Running benchmark.." << std::endl;
    std::chrono::time_point<std::chrono::steady_clock> pointers_startTime = std::chrono::steady_clock::now();
    decodeCipher(99);
    std::chrono::time_point<std::chrono::steady_clock> pointers_endTime = std::chrono::steady_clock::now();
    double timeInSeconds = std::chrono::duration_cast<std::chrono::nanoseconds>(pointers_endTime - pointers_startTime).count() / 1000000000.0;
    std::cout << "Time taken to decode message using pointers: " << timeInSeconds << " seconds" << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> strings_startTime = std::chrono::steady_clock::now();
    std::ifstream inStream{"csv/cipher.csv"};
    std::string line;
    std::string decodedMessage;
    while(std::getline(inStream, line)) {
        std::stringstream lineStream;
        lineStream << line;

        // Henter siste ord i linja (det som kommer etter siste komma)
        std::string word;
        while(std::getline(lineStream, word, ',')) {
            // Gjør ingenting: vi vil bare at "word" skal ende opp som siste felt
        }

        if(word.size() % 2 == 0) {
            // Vi dekoder ikke her (poenget er å sammenligne hastighet, ikke resultat)
            decodedMessage += word;
        }

        // Vi vil kaste annenhver linje, så vi leser én ekstra linje her
        std::getline(inStream, line);
    }

    std::chrono::time_point<std::chrono::steady_clock> strings_endTime = std::chrono::steady_clock::now();
    timeInSeconds = std::chrono::duration_cast<std::chrono::nanoseconds>(strings_endTime - strings_startTime).count() / 1000000000.0;
    std::cout << "Time taken to decode message using strings: " << timeInSeconds << " seconds" << std::endl;

    std::cout << decodedMessage << std::endl;
}