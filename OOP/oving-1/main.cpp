// Øving 1
// Oversettelse fra Python til C++
#include "std_lib_facilities.h"

int maxOfTwo(int a, int b)   {
    // BEGIN: 2a
    if (a > b) {
        cout << "A is greater than B" << endl;
        return a;
    } else {
        cout << "B is greater than or equal to A" << endl;
        return b;
    }
    // END: 2a
}

int fibonacci(int n) {
    // BEGIN: 2c

    int a {};
    int b = 1;
    cout << "Fibonacci numbers:" << endl;
    for (size_t x = 1; x < n + 1; x++) {
        cout << x << " " << b << endl;
        auto temp = b;
        b += a;
        a = temp;
    }
    cout << "----" << endl;

    return b;

    // END: 2c
}

int squareNumberSum(int n) {
    // BEGIN: 2d

    size_t totalSum {};
    for (size_t i = 1; i < n + 1; i++) {
        totalSum += i * i;
        cout << i * i << endl;
    }
    cout << totalSum << endl;

    return totalSum;
 
    // END: 2d  
}

void triangleNumbersBelow(int n) {
    // BEGIN: 2e

    int acc = 1;
    int num = 2;
    cout << "Triangle numbers below " << n << ":" << endl;
    while (acc < n) {
        cout << acc << endl;
        acc += num;
        num += 1;
    }
    cout << "" << endl;

    // END: 2e
}

bool isPrime(int n) {
    // BEGIN: 2f
    
    for (size_t j = 2; j < n; j++) {
        if (n % j == 0) {
            return false;
        }
    }
    return true;
    
    // END: 2f
}

void naivePrimeNumberSearch(int n) {
    // BEGIN: 2g

    for (size_t number = 2; number < n; number++) {
        if (isPrime(number))
            cout << number << " is a prime" << endl;
    }

    // END: 2g 
}

void inputAndPrintNameAndAge() {
    // BEGIN: 2h

    string name;
    int age;

    cout << "Skriv inn et navn: ";
    cin >> name;

    cout << "Skriv inn alderen til " << name << ": ";
    cin >> age;

    cout << name << " er " << age << " år gammel." << endl;;

    // END: 2h
}

int main() {
    // BEGIN: 2b

    cout << "Oppgave a)" << endl;
    cout << maxOfTwo(5,6) << endl;

    cout << "Oppgave c)" << endl;
    cout << fibonacci(5) << endl;

    cout << "Oppgave d)" << endl;
    cout << squareNumberSum(5) << endl;

    cout << "Oppgave e)" << endl;
    triangleNumbersBelow(10);

    cout << "Oppgave f) og g)" << endl;
    naivePrimeNumberSearch(14);

    inputAndPrintNameAndAge();
    // END: 2b
	return 0;
}
