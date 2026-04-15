
#include "std_lib_facilities.h"
#include "test.h"
#include "mastermind.h"
#include "masterVisual.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));  // Seed random number generator

	// Test menu
	int choice = 0;
	while (choice != 7) {
		cout << "\n=== Test Menu ===\n";
		cout << "1. Test Call By Value\n";
		cout << "2. Test Call By Reference\n";
		cout << "3. Test String Functions\n";
		cout << "4. Test Student Struct\n";
		cout << "5. Play Mastermind (Console)\n";
		cout << "6. Play Mastermind (Graphics)\n";
		cout << "7. Exit\n";
		cout << "Choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				testCallByValue();
				break;
			case 2:
				testCallByReference();
				break;
			case 3:
				testString();
				break;
			case 4: {
				// Test Student struct (2d)
				Student student1;
				student1.name = "Ola Nordmann";
				student1.studyProgram = "MTDT";
				student1.age = 21;

				printStudent(student1);
				cout << "Is in MTDT: " << (isInProgram(student1, "MTDT") ? "Yes" : "No") << "\n";
				cout << "Is in MTEK: " << (isInProgram(student1, "MTEK") ? "Yes" : "No") << "\n";
				break;
			}
			case 5:
				playMastermind();
				break;
			case 6:
				playMastermindVisual();
				break;
			case 7:
				cout << "Goodbye!\n";
				break;
			default:
				cout << "Invalid choice.\n";
		}
	}

	return 0;
}
