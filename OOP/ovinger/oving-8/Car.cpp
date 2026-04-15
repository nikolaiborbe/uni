#include "Car.h"

#include <cassert>

// BEGIN 2b
Car::Car(int freeSeats) : freeSeats{freeSeats} {}
// END 2b

// BEGIN 2c
bool Car::hasFreeSeats() const {
    return freeSeats > 0;
}

void Car::reserveFreeSeat() {
    assert(freeSeats > 0);
    --freeSeats;
}
// END 2c
