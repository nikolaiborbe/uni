#include "std_lib_facilities.h"
#include "cannonball.h"

int main()
{
	const double maxError = 0.0001;

	// 3c: Test funksjoner
	cout << "--- Testing velY ---" << endl;
	testDeviation(velY(25.0, 2.5), 0.475, maxError, "velY(25.0, 2.5)");
	testDeviation(velY(25.0, 5.0), -24.05, maxError, "velY(25.0, 5.0)");

	cout << "--- Testing posX ---" << endl;
	testDeviation(posX(0.0, 50.0, 2.5), 125.0, maxError, "posX(0.0, 50.0, 2.5)");
	testDeviation(posX(0.0, 50.0, 5.0), 250.0, maxError, "posX(0.0, 50.0, 5.0)");

	cout << "--- Testing posY ---" << endl;
	testDeviation(posY(0.0, 25.0, 2.5), 31.84375, maxError, "posY(0.0, 25.0, 2.5)");
	testDeviation(posY(0.0, 25.0, 5.0), 2.375, maxError, "posY(0.0, 25.0, 5.0)");

	// 4d: Test getVelocityVector
	cout << "--- Testing getVelocityVector ---" << endl;
	vector<double> v = getVelocityVector(27.5, 15.64);
	testDeviation(v[0], 13.8728, 0.001, "getVelocityX(27.5, 15.64)");
	testDeviation(v[1], 7.22175, 0.001, "getVelocityY(27.5, 15.64)");

	cout << "--- Testing getDistanceTraveled ---" << endl;
	testDeviation(getDistanceTraveled(v[0], v[1]), 20.4253, 0.001, "getDistanceTraveled(13.87, 7.22)");

	// 5b: Start spillet
	playTargetPractice();

	return 0;
}