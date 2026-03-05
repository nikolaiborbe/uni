#include "MyArray.h"

// BEGIN 5d
void testMyArray(){
    MyArray<int, 5> intArr;
    intArr.fill(0);
    for (int i = 0; i < intArr.getSize(); i++){
        intArr.at(i) = i * 10;
    }
    std::cout << "Int array: ";
    for (int i = 0; i < intArr.getSize(); i++){
        std::cout << intArr.at(i) << " ";
    }
    std::cout << std::endl;

    MyArray<double, 3> doubleArr;
    doubleArr.fill(3.14);
    std::cout << "Double array: ";
    for (int i = 0; i < doubleArr.getSize(); i++){
        std::cout << doubleArr.at(i) << " ";
    }
    std::cout << std::endl;

    try {
        intArr.at(10);
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
// END 5d
