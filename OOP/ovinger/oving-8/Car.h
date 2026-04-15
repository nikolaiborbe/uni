#pragma once

// BEGIN: 2a
class Car {
public:
    Car(int freeSeats);
    bool hasFreeSeats() const;
    void reserveFreeSeat();
private:
    int freeSeats;
};
// END: 2a
