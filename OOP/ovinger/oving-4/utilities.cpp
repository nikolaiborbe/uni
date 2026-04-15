#include "utilities.h"

int incrementByValueNumTimes(int startValue, int increment, int numTimes)
{
	for (int i = 0; i < numTimes; i++)
		startValue += increment;

	return startValue;
}

// BEGIN: 1d
void incrementByValueNumTimesRef(int& startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
}
// END: 1d

// BEGIN: 1e
void swapNumbers(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
// END: 1e

// BEGIN: 2b
void printStudent(const Student& student) {
    cout << "Name: " << student.name << "\n";
    cout << "Study Program: " << student.studyProgram << "\n";
    cout << "Age: " << student.age << "\n";
}
// END: 2b

// BEGIN: 2c
bool isInProgram(const Student& student, const string& program) {
    return student.studyProgram == program;
}
// END: 2c


// BEGIN: 3a
string randomizeString(int length, char lowerBound, char upperBound) {
    string result = "";
    for (int i = 0; i < length; i++) {
        char randomChar = lowerBound + rand() % (upperBound - lowerBound + 1);
        result += randomChar;
    }
    return result;
}
// END: 3a

// BEGIN: 3c
string readInputToString(int length, char lowerBound, char upperBound) {
    string input;
    bool valid = false;

    while (!valid) {
        cout << "Enter " << length << " characters (" << lowerBound << "-" << upperBound << "): ";
        cin >> input;

        if (static_cast<int>(input.length()) != length) {
            cout << "Invalid length. Please try again.\n";
            continue;
        }

        valid = true;
        for (int i = 0; i < length; i++) {
            char c = toupper(input[i]);
            if (c < toupper(lowerBound) || c > toupper(upperBound)) {
                valid = false;
                cout << "Invalid character. Please try again.\n";
                break;
            }
        }
    }

    // Convert to uppercase
    for (int i = 0; i < static_cast<int>(input.length()); i++) {
        input[i] = toupper(input[i]);
    }

    return input;
}
// END: 3c

// BEGIN: 3d
int countChar(const string& str, char c) {
    int count = 0;
    for (char ch : str) {
        if (ch == c) {
            count++;
        }
    }
    return count;
}
// END: 3d
