#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>

// BEGIN 5a
template<typename Type, int Size>
// END 5a
class MyArray
{
    private:
        // BEGIN 5b
        Type elements[Size];
        // END 5b
    public:
        // BEGIN 5c
        int getSize() const {
            return Size;
        }

        Type& at(int index) {
            if (index < 0 || index >= Size) {
                throw std::out_of_range("Index " + std::to_string(index) + " out of range for MyArray of size " + std::to_string(Size));
            }
            return elements[index];
        }

        void fill(Type value) {
            for (int i = 0; i < Size; i++) {
                elements[i] = value;
            }
        }
        // END 5c
};

// BEGIN 5d
void testMyArray();
// END 5d
