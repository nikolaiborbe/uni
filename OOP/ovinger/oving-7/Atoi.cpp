#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <print>
#include "Atoi.h"

using namespace std;

int Atoi::isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int Atoi::characterToDigit(char c){
    // Forutsetter at c er et siffer ('0'...'9')
    return (c - '0'); 
}

const char* Atoi::parseInt(const char* ptr, int* outIntVal) {
    // BEGIN: 2a
    int sign;
    int num;

    if (*ptr == '-') {
        sign = -1;
        ++ptr;
    } else {
        sign = 1;
    }

    num = 0;

    while (isDigit(*ptr)) {
        num = num * 10 + characterToDigit(*ptr);
        ++ptr;
    }

    *outIntVal = sign * num;

    return ptr;
    // END: 2a
}
