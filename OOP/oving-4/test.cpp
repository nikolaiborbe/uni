#include "test.h"

void testCallByValue()
{
	int v0 = 5;
	int increment = 2;
	int iterations = 10;
	int result = incrementByValueNumTimes(v0, increment, iterations);
	cout << "v0: " << v0 << " increment: " << increment
		 << " iterations: " << iterations << " result: " << result << '\n';
}

void testCallByReference()
{
	// BEGIN: 1d
	int v0 = 5;
	int increment = 2;
	int iterations = 10;
	incrementByValueNumTimesRef(v0, increment, iterations);
	cout << "v0: " << v0 << " increment: " << increment
		 << " iterations: " << iterations << '\n';
	// END: 1d

}


void testString(){
	// 3b OG 3e gjøres inne i her
	// BEGIN: 3e
	// 3b: Create grades string with 8 random characters A-F
	string grades = randomizeString(8, 'A', 'F');
	cout << "Grades: " << grades << '\n';

	// 3e: Count each grade and calculate average
	vector<int> gradeCount;
	for (char c = 'A'; c <= 'F'; c++) {
		gradeCount.push_back(countChar(grades, c));
	}

	// Print grade counts
	cout << "Grade counts:\n";
	for (int i = 0; i < 6; i++) {
		cout << static_cast<char>('A' + i) << ": " << gradeCount[i] << '\n';
	}

	// Calculate average (A=6, B=5, C=4, D=3, E=2, F=1)
	double sum = 0;
	int totalGrades = 0;
	for (int i = 0; i < 6; i++) {
		sum += gradeCount[i] * (6 - i);  // A=6, B=5, etc.
		totalGrades += gradeCount[i];
	}

	if (totalGrades > 0) {
		double average = sum / totalGrades;
		cout << "Average grade: " << average << '\n';
	}
	// END: 3e
}