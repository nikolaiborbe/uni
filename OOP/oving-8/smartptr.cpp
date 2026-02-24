#include "smartptr.h"

void smartptrTest () {
    std::shared_ptr<Book> b1(new Book("1984", 328));
    std::shared_ptr<Book> b2(b1);

    std::unique_ptr<Book> b3(new Book("Brave New World", 288));
    std::unique_ptr<Book> b4(std::move(b3));

    std::shared_ptr<Book> b5(new Book("Fahrenheit 451", 194));
    std::shared_ptr<Book> b6(b5);

    b1->read();
    b2->read();
    // b3 is now nullptr after move, so we skip it
    b4->read();
    b5->read();
    b6->read();
}
