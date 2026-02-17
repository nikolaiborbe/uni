#pragma once
#include <string>
#pragma once

class Atoi {
public:
    static const char* parseInt(const char* ptr, int* outIntVal);
private:
    static int isDigit(char c);
    static int characterToDigit(char c);
};





