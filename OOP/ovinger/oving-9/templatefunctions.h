#pragma once
#include <random>
#include <iostream>
#include <string>
#include <vector>

// BEGIN 4a
template<typename T>
T maximum(T a, T b){
    return (a > b) ? a : b;
}
// END 4a

// BEGIN 4b
template<typename T>
void shuffle(std::vector<T>& v){
    for (size_t i = v.size() - 1; i > 0; i--){
        size_t j = static_cast<size_t>(rand()) % (i + 1);
        std::swap(v[i], v[j]);
    }
}
// END 4b

void testTemplateFunctions();
