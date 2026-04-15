#include "Person.h"

// BEGIN 3b
Person::Person(std::string name, std::string email, Car* car)
	: name{name}, email{email}, car{car} {}

std::string Person::getName() const {
	return name;
}

std::string Person::getEmail() const {
	return email;
}

void Person::setEmail(const std::string& email) {
	this->email = email;
}
// END 3b

// BEGIN 3c
bool Person::hasAvailableSeats() const {
	return car != nullptr && car->hasFreeSeats();
}
// END 3c

// BEGIN 3d
std::ostream& operator<<(std::ostream& os, const Person& p) {
	os << p.name << " (" << p.email << ")";
	if (p.car != nullptr) {
		os << " has a car";
		if (p.car->hasFreeSeats()) {
			os << " with free seats";
		}
	}
	return os;
}
// END 3d

// BEGIN 3e
Person::~Person() {
	delete car;
}
// END 3e
