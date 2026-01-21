//handout oving 2

#include "std_lib_facilities.h"
#include "AnimationWindow.h"


void inputAndPrintInteger() {
    // BEGIN: 1b
    int a {};

    cout << "Skriv inn et tall: ";
    cin >> a;
    cout << "Du skrev: " << a << endl;

    // END: 1b
}

int inputInteger() {
    // BEGIN: 1c
    int a{};

    cout << "Skriv inn et tall: ";
    cin >> a;

    return a;
    // END: 1c  
}

void printSumOfInputIntegers() {
    // BEGIN: 1d
    int a = inputInteger();
    int b = inputInteger();

    cout << "\nSummer av tallene: " << a + b << endl;

    // END: 1d
}

bool isOdd(int n) {
    // BEGIN: 1f
    if (n % 2 == 0)
        return false;
    else
        return true;
    // END: 1f
}

void inputIntegersAndPrintSum() {
    // BEGIN: 2a
    int num_iter {};
    cout << "Hvor mange nummere ønsker du å summere?";
    cin >> num_iter;

    int current_sum{};
    int current_val{};
    for (int i{}; i < num_iter; i++) {
        cin >> current_val;
        current_sum += current_val;
    }

    cout << current_sum << endl;
    // END: 2a
}

void inputIntegersAndPrintSumUntilStopped() {
    // BEGIN: 2b
    int current_sum{};
    int current_number{};
    while (true) {
        cin >> current_number;
        current_sum += current_number;

        if (current_number == 0) break;
    }
    cout << current_sum;

    // END: 2b
}

double inputDouble() {
    // BEGIN: 2d
    double a{};
    cin >> a;
    return a;
    // END: 2d
}

void convertNOKtoEUR() {
    // BEGIN: 2e
    double user_input{};
    while (true) {
        cout << "Skriv inn et tall: ";
        user_input = inputDouble();
        if (user_input > 0) break;
    }

    string eur_str = format("{:.2f}", user_input / 10.5);
    cout << "Den konverterte beløpet er: " << eur_str << "€" << endl;

    // END: 2e
}

void printMultiplicationTable() {
    // BEGIN: 2g
    int h{}, w{};

    cout << "Enter height: ";
    cin >> h;
    cout << "Enter width: ";
    cin >> w;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cout << setw(10) << j*i;
        }
        cout << endl;
    }

    // END: 2g
}

double discriminant(double a, double b, double c) {
    // BEGIN: 3a
    return 0;
    // END: 3a
}

void printRealRoots(double a, double b, double c) {
    // BEGIN: 3b

    // END: 3b
}

void solveQuadraticEquations() {
    // BEGIN: 3c

    // END: 3c
}

void pythagoras() {
    // BEGIN: 4a
    // Alle deloppgaver i 4 skal løses her
    // END: 4a
}

vector<int> calculateBalance(int amount, int rate, int years) {
    // BEGIN: 5a
    return {};
    // END: 5a
}

void printBalance(vector<int> balanceVec) {
    // BEGIN: 5b

    // END: 5b
}

void temp() {
    printMultiplicationTable();
}

int main() {
    // Oppgave 1a
    int x;

    while(true)
    {
        cout << "\n0) Avslutt" << endl << "1) Annen funksjon" << endl;
        cin >> x;

        switch (x) {
            case 0:
                return 0;
            case 1:
                temp();
                break;
        }

    }
    // Her kan du teste funksjonene dine ved hjelp av menysystem som beskrevet. 
    // NB: Denne delen av koden blir IKKE automatisk rettet.
    return 0;
}
