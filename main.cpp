#include <iostream>
#include <string>
#include <sstream>

void getString(std::string& str) {
    std::cout << "what sentence" << std::endl;
    getline(std::cin, str);
}

void reverseWords(std::string& str) {
    str = 
    for (int i = 0; str.size(); i++) {
        std::cout << i << std::endl;
    }
}

int main() {
    std::string str;
    getString(str);
    reverseWords(str);
    std::cout << str << std::endl;

    return 0;

}

