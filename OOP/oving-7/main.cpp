#include <iostream>
#include "Dummy.h"
#include "CCipher.h"
#include "PointerRef.h"
#include "Atoi.h"

int main() {
    // Task 3: Dummy test
    dummyTest();

    // Task 4f: Decode with ROT 7, 11, 13, 17, 19
    DeCipher cipher("csv/cipher.csv");

    int rotKeys[] = {7, 11, 13, 17, 19};
    for (int rot : rotKeys) {
        cipher.decodeCipher(rot);
        std::cout << "ROT " << rot << ": " << cipher.getDecodedMessage() << std::endl;
        std::cout << "---" << std::endl;
    }

    return 0;
}
