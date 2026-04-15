#pragma once

#include "Person.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

// BEGIN 4a
enum class Campus { trh, aal, gjo };
// END 4a

// BEGIN 4b
std::ostream& operator<<(std::ostream& os, const Campus& c);
// END 4b


const std::unordered_map<Campus, std::string> campusToString {
	{ Campus::trh, "Trondheim" },
	{ Campus::aal, "Aalesund" },
	{ Campus::gjo, "Gjovik"}
};

const std::unordered_map<std::string, Campus> stringToCampus {
	{ "Trondheim", Campus::trh },
	{ "Aalesund", Campus::aal },
	{ "Gjovik", Campus::gjo }
};

class Meeting
{
private:
	// BEGIN 4c
	int day;
	int startTime;
	int endTime;
	Campus location;
	std::string subject;
	const Person* leader;
	std::vector<Person*> participants;
	// END 4c
public:
	// BEGIN 4d
	int getDay() const { return day; }
	int getStartTime() const { return startTime; }
	int getEndTime() const { return endTime; }
	Campus getLocation() const { return location; }
	std::string getSubject() const { return subject; }
	const Person* getLeader() const { return leader; }
	// END 4d

	// BEGIN 4e
	void addParticipant(Person* p);
	// END 4e

	Meeting(int day, int startTime, int endTime, Campus location, const std::string& subject, Person* leader);

	// BEGIN 4h
	std::vector<std::string> getParticipantList() const;
	// END 4h

	// BEGIN 4i
	std::vector<Person*> findPotentialCoDriving(Meeting& other) const;
	// END 4i

	// Vi ønsker ikke å tillate kopiering av Meeting-objekter
	Meeting(const Meeting&) = delete;
	Meeting& operator=(const Meeting&) = delete;
};

// BEGIN 4j
std::ostream& operator<<(std::ostream& os, const Meeting& m);
// END 4j
