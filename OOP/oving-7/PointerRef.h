#pragma once

class PointerRef {
public:
    static void addPointer(int* ptr);
    static void addReference(int& ref);

    // BEGIN: 1b
    static bool valueComparison(int* ptr, int& ref);
    // END: 1b

    // BEGIN: 1c
    static bool addressComparison(int* ptr, int& ref);
    // END: 1c
};
