#pragma once
#include "Car.h"
#include <string>
#include <iostream>
#include <memory>

class Person
{
public:
	// BEGIN 3b
	Person(std::string name, std::string email, Car* car = nullptr);
	std::string getName() const;
	std::string getEmail() const;
	void setEmail(const std::string& email);
	// END 3b

	// BEGIN 3c
	bool hasAvailableSeats() const;
	// END 3c

	// BEGIN 3d
	friend std::ostream& operator<<(std::ostream& os, const Person& p);
	// END 3d

	// BEGIN 3e
	~Person();
	// END 3e

	// Vi onsker ikke å tillate kopiering av Person-objekter
	Person(const Person&) = delete;
	Person& operator=(const Person&) = delete;

private:
	// BEGIN 3a
	std::string name;
	std::string email;
	Car* car;
	// END 3a
};
