#include "utilities.h"
#include "std_lib_facilities.h"
#include <random>

// BEGIN: 5a
int randomWithLimits(int lowerLimit, int upperLimit) {
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> distribution(lowerLimit, upperLimit);
	return distribution(generator);
}
// END: 5a