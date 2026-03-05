#include "measurePerformance.h"
#include "Stopwatch.h"
#include <memory>
#include <array>
#include <iostream>


// BEGIN 1a
double measurePerformanceUnique(){
    constexpr int iterations = 1000000;
    Stopwatch sw;
    sw.start();
    for (int i = 0; i < iterations; i++){
        std::unique_ptr<int> p = std::make_unique<int>(42);
    }
    return sw.stop() / iterations;
}

double measurePerformanceShared(){
    constexpr int iterations = 1000000;
    Stopwatch sw;
    sw.start();
    for (int i = 0; i < iterations; i++){
        std::shared_ptr<int> p = std::make_shared<int>(42);
    }
    return sw.stop() / iterations;
}

double measurePerformanceStack(){
    constexpr int iterations = 100000;
    constexpr int size = 10000;
    Stopwatch sw;
    sw.start();
    for (int i = 0; i < iterations; i++){
        std::array<int, size> arr1;
        arr1[0] = i;
    }
    return sw.stop() / iterations;
}

double measurePerformanceHeap(){
    constexpr int iterations = 100000;
    constexpr int size = 10000;
    Stopwatch sw;
    sw.start();
    for (int i = 0; i < iterations; i++){
        std::array<int, size>* arr2 = new std::array<int, size>;
        (*arr2)[0] = i;
        delete arr2;
    }
    return sw.stop() / iterations;
}
// END 1a
