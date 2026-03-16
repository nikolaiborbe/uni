#include "templatefunctions.h"

void testTemplateFunctions(){
    int a = 1;
    int b = 2;
    int c = maximum<int>(a, b);
    std::cout << "max(1, 2) = " << c << std::endl;

    double d = 2.4;
    double e = 3.2;
    double f = maximum<double>(d, e);
    std::cout << "max(2.4, 3.2) = " << f << std::endl;

    std::vector<int> vi{1, 2, 3, 4, 5, 6, 7};
    shuffle(vi);
    std::cout << "Shuffled int vector: ";
    for (int x : vi) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<std::string> vs{"one", "two", "three", "four"};
    shuffle(vs);
    std::cout << "Shuffled string vector: ";
    for (const auto& s : vs) std::cout << s << " ";
    std::cout << std::endl;
}
