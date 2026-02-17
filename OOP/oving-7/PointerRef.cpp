#include <iostream>
#include <print>
#include "PointerRef.h"

using namespace std;

void PointerRef::addPointer(int* ptr) {
    // BEGIN: 1a
    *ptr = *ptr + 20;
    // END: 1a
}

void PointerRef::addReference(int& ref) {
    ref = ref + 20;    
}

// BEGIN: 1b
bool PointerRef::valueComparison(int* ptr, int& ref) {
    return *ptr == ref;
}
// END: 1b

// BEGIN: 1c
bool PointerRef::addressComparison(int* ptr, int& ref) {
    return ptr == &ref;
}
// END: 1c