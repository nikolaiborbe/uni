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
    return b*b - 4*a*c;
    // END: 3a
}

void printRealRoots(double a, double b, double c) {
    // BEGIN: 3b
    double in_sqrt = discriminant(a,b,c);
    if (in_sqrt < 0) return;

    if (in_sqrt > 0)
    {
        double x_1, x_2;

        x_1 = (-b + sqrt(in_sqrt)) / (2*a);
        x_2 = (-b - sqrt(in_sqrt)) / (2*a);

        cout << "x_1: " << x_1 << ", " << "x_2: " << x_2 << endl;
    }

    if (in_sqrt = 0)
    {
        double x;

        x = (-b) / (2*a);

        cout << "x: " << x << endl;
    }

    // END: 3b
}

void solveQuadraticEquations() {
    // BEGIN: 3c
    double a, b, c;

    cout << "Hvilke konstanter har du?";
    cin >> a;
    cin >> b;
    cin >> c;

    printRealRoots(a,b,c);

    // END: 3c
}

void pythagoras() {
    // BEGIN: 4a
    using u16 = uint16_t;
    constexpr u16 WINDOW_WIDTH = 1024;
    constexpr u16 WINDOW_HEIGHT = 768;
    constexpr string TITLE = "Pythagoras";
    constexpr Point CENTER = Point{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    AnimationWindow win(150,150, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

    // jeg bruker u, v, w, for hhv. rødt, blått, grønt kvadrat i opg.tesksten.
    // og indeks some hvilket punkt (mot kl. starter øverst venstre).

    // vi vet at punkt u_4=v_2, osv.

    // tegning trekant
    Point t1 = {CENTER.x - 150, CENTER.y + 50};
    Point t2 = {CENTER.x + 0, CENTER.y + 50};
    Point t3 = {CENTER.x - 150, CENTER.y - 200};
    win.draw_triangle(t1, t2, t3, Color::black);
    
    // tegning kvadrater
    u16 A = t2.x - t1.x;
    u16 B = t1.y - t3.y;
    u16 hypotnuse = sqrt(A*A + B*B);

    // u (rødt) kvadrat
    Point u1 = t1;
    Point u2 {t1.x, t1.y + (t2.x - t1.x)};
    Point u3 {t2.x, t1.y + (t2.x - t1.x)};
    Point u4 = t2;
    win.draw_quad(u1, u2, u3, u4, Color::red);
    
    // v (blått) kvadrat
    Point v1 = t3;
    Point v2 = t2;
    Point v3 {t2.x + B, t2.y - A};
    Point v4 {t3.x + B, t3.y - A};
    win.draw_quad(v1, v2, v3, v4, Color::blue);

    Point w1 {t3.x - B, t3.y};
    Point w2 = {t1.x - B, t1.y};
    Point w3 = t1;
    Point w4 = t3;
    win.draw_quad(w1, w2, w3, w4, Color::green);

    win.wait_for_close();
    // END: 4a
}

vector<int> calculateBalance(int amount, int rate, int years) {
    // BEGIN: 5a

    double current_balance{};
    vector<int> log;
    for (int i{}; i <= years; i++) {
        current_balance = amount * pow(1 + static_cast<double>(rate)/100, i);

        log.push_back(static_cast<int>(round(current_balance)));

    }

    return log;
    // END: 5a
}

void printBalance(vector<int> balanceVec) {
    // BEGIN: 5b

    int year{};
    cout << setw(15) << "År" << setw(15) << "Saldo" << endl;
    for (auto& balance : balanceVec) {
        cout << setw(15) << year << setw(15) << balance << endl;
        year++;
    };
    // END: 5b
}


int main() {
    // Oppgave 1a
    int x;

    while(true)
    {
        cout << "\n0) Avslutt" << endl 
        << "1) Løs en kvadratisk likning" << endl << "2) Regn ut renter" << endl;
        cin >> x;

        switch (x) {
            case 0:
                return 0;
            case 1:
                solveQuadraticEquations();
                break;
            case 2:
                int a,b,c;
                cout << "Hvor mye, hvilken rate, og hvor mange år: ";
                cin >> a >> b >> c;
                printBalance(calculateBalance(a,b,c));
                break;
        }

    }
    // Her kan du teste funksjonene dine ved hjelp av menysystem som beskrevet. 
    // NB: Denne delen av koden blir IKKE automatisk rettet.
    return 0;
}
