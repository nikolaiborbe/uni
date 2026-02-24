#pragma once
#include <iostream>
#include <memory>
#include <string>

class Book {
public:
    Book(const std::string& title, int pages)
        : title(title), pages(pages) {
        std::cout << "Book \"" 
        << title << "\" created.\n";
    }
    ~Book() {
        std::cout << "Book \"" 
        << title << "\" destroyed.\n";
    }
    void read() {
        std::cout << "Reading \"" 
        << title << "\" with " 
        << pages << " pages.\n";
    }
private:
    std::string title;
    int pages;
};
