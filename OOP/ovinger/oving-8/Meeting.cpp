#include "Meeting.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cmath>

// BEGIN 4b
std::ostream& operator<<(std::ostream& os, const Campus& c) {
	os << campusToString.at(c);
	return os;
}
// END 4b

// BEGIN 4e
void Meeting::addParticipant(Person* p) {
	participants.push_back(p);
}
// END 4e

// BEGIN 4f
Meeting::Meeting(int day, int startTime, int endTime, Campus location, const std::string& subject, Person* leader)
	: day{day}, startTime{startTime}, endTime{endTime}, location{location}, subject{subject}, leader{leader} {
	addParticipant(leader);
}
// END 4f

// BEGIN 4h
std::vector<std::string> Meeting::getParticipantList() const {
	std::vector<std::string> names;
	for (const auto* p : participants) {
		names.push_back(p->getName());
	}
	return names;
}
// END 4h

// BEGIN 4i
std::vector<Person*> Meeting::findPotentialCoDriving(Meeting& other) const {
	std::vector<Person*> result;
	for (auto* p : other.participants) {
		if (p->hasAvailableSeats()
			&& other.location == location
			&& other.day == day
			&& std::abs(other.startTime - startTime) < 100
			&& std::abs(other.endTime - endTime) < 100) {
			result.push_back(p);
		}
	}
	return result;
}
// END 4i

// BEGIN 4j
std::ostream& operator<<(std::ostream& os, const Meeting& m) {
	os << "Meeting: " << m.getSubject() << "\n";
	os << "Location: " << m.getLocation() << "\n";
	os << "Time: " << m.getStartTime() << " - " << m.getEndTime() << ", Day: " << m.getDay() << "\n";
	os << "Leader: " << m.getLeader()->getName() << "\n";
	os << "Participants:\n";
	for (const auto& name : m.getParticipantList()) {
		os << "  - " << name << "\n";
	}
	return os;
}
// END 4j
