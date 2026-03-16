#include "Stopwatch.h"
#include "optimizeVector.h"
#include <vector>
#include <iostream>


// BEGIN 2a
void testVector(){
    std::vector<int> v;
    for (int i = 0; i < 20; i++){
        v.push_back(i);
        std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
    }
}
// END 2a


void optimizeVector(){
    // BEGIN 2d
    {
        Stopwatch sw;
        std::vector<int> v;
        sw.start();
        for (int i = 0; i < 1000000; i++){
            v.push_back(i);
        }
        std::cout << "Oppgave 2d: " << sw.stop() << std::endl;
    }
    // END 2d

    // BEGIN 2e
    {
        Stopwatch sw;
        std::vector<int> v;
        v.resize(1000000);
        sw.start();
        for (size_t i = 0; i < 1000000; i++){
            v[i] = static_cast<int>(i);
        }
        std::cout << "Oppgave 2e: " << sw.stop() << std::endl;
    }
    // END 2e
}
