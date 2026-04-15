#include "cannonball.h"
#include "cannonball_viz.h"
#include "utilities.h"

// BEGIN: 2a
double acclY() {
	return -gravity;
}
// END: 2a

// BEGIN: 2b
double velY(double initVelocityY, double time) {
	return initVelocityY + acclY() * time;
}
// END: 2b

// BEGIN: 2c
double posX(double initPositionX, double initVelocityX, double time) {
	return initPositionX + initVelocityX * time;
}

double posY(double initPositionY, double initVelocityY, double time) {
	return initPositionY + initVelocityY * time + acclY() * time * time / 2.0;
}
// END: 2c

// BEGIN: 2d
void printTime(double time) {
	int totalSeconds = static_cast<int>(time);
	int hours = totalSeconds / 3600;
	int minutes = (totalSeconds % 3600) / 60;
	int seconds = totalSeconds % 60;
	cout << hours << " timer, " << minutes << " minutter og " << seconds << " sekunder" << endl;
}
// END: 2d

// BEGIN: 2e
double flightTime(double initVelocityY) {
	return (-2.0 * initVelocityY) / acclY();
}
// END: 2e

// BEGIN: 3b
bool testDeviation(double compareOperand, double toOperand, double maxError, string name) {
	if (abs(compareOperand - toOperand) <= maxError) {
		cout << name << " is valid." << endl;
		return true;
	} else {
		cout << name << " is not valid, expected " << toOperand << ", got " << compareOperand << "." << endl;
		return false;
	}
}
// END: 3b

// BEGIN: 4a
double getUserInputTheta() {
	double theta;
	cout << "Skriv inn vinkel i grader: ";
	cin >> theta;
	return theta;
}

double getUserInputInitVelocity() {
	double velocity;
	cout << "Skriv inn startfart: ";
	cin >> velocity;
	return velocity;
}

double degToRad(double deg) {
	return deg * pi / 180.0;
}

double getVelocityX(double theta, double initVelocity) {
	return initVelocity * cos(degToRad(theta));
}

double getVelocityY(double theta, double initVelocity) {
	return initVelocity * sin(degToRad(theta));
}

vector<double> getVelocityVector(double theta, double initVelocity) {
	vector<double> v;
	v.push_back(getVelocityX(theta, initVelocity));
	v.push_back(getVelocityY(theta, initVelocity));
	return v;
}
// END: 4a

// BEGIN: 4b
double getDistanceTraveled(double velocityX, double velocityY) {
	double time = flightTime(velocityY);
	return posX(0.0, velocityX, time);
}
// END: 4b

// BEGIN: 4c
double targetPractice(double distanceToTarget, double velocityX, double velocityY) {
	double distance = getDistanceTraveled(velocityX, velocityY);
	return distanceToTarget - distance;
}
// END: 4c


// BEGIN: 5b
void playTargetPractice() {
	int targetDistance = randomWithLimits(100, 1000);
	cout << "Malet er " << targetDistance << " meter unna." << endl;

	for (int i = 0; i < 10; i++) {
		cout << "\nForsok " << (i + 1) << " av 10:" << endl;
		double theta = getUserInputTheta();
		double initVelocity = getUserInputInitVelocity();

		double velX = getVelocityX(theta, initVelocity);
		double velYVal = getVelocityY(theta, initVelocity);

		double deviation = targetPractice(targetDistance, velX, velYVal);
		double time = flightTime(velYVal);

		cout << "Kulen brukte ";
		printTime(time);

		if (abs(deviation) < 5.0) {
			cout << "Gratulerer! Du traff malet!" << endl;
			return;
		} else if (deviation > 0) {
			cout << "Skuddet var " << abs(deviation) << " meter for kort." << endl;
		} else {
			cout << "Skuddet var " << abs(deviation) << " meter for langt." << endl;
		}
	}
	cout << "Beklager, du brukte alle forsokene dine. Bedre lykke neste gang!" << endl;
}
// END: 5b
