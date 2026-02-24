#include "MeetingWindow.h"
#include <iostream>
#include <stdexcept>

MeetingWindow::MeetingWindow(TDT4102::Point position, int width, int height, const std::string& title):
	// BEGIN 5a
	AnimationWindow{position.x, position.y, width, height, title},
	// END 5a

	// BEGIN 5e
	quitBtn{{width - btnW - pad, pad}, static_cast<unsigned int>(btnW), static_cast<unsigned int>(btnH), "Quit"},
	// END 5e

	// BEGIN 6a
	personName{{pad, pad}, static_cast<unsigned int>(fieldW), static_cast<unsigned int>(fieldH), "Name"},
	personEmail{{pad, pad + fieldH + pad}, static_cast<unsigned int>(fieldW), static_cast<unsigned int>(fieldH), "Email"},
	// END 6a

	// BEGIN 6b
	personSeats{{pad, pad + 2 * (fieldH + pad)}, static_cast<unsigned int>(fieldW), static_cast<unsigned int>(fieldH), "Car seats"},
	personNewBtn{{pad, pad + 3 * (fieldH + pad)}, static_cast<unsigned int>(btnW), static_cast<unsigned int>(btnH), "Add person"},
	// END 6b

	dummyArgument{0}

{
	// Felles
	// BEGIN 5f
	add(quitBtn);
	// END 5f

	// BEGIN 5g
	quitBtn.setCallback(std::bind(&MeetingWindow::cb_quit, this));
	// END 5g

	// BEGIN 6d
	personNewBtn.setCallback(std::bind(&MeetingWindow::newPerson, this));
	// END 6d


	// Ny person
	attachPersonWidget(personName);
	attachPersonWidget(personEmail);

	attachPersonWidget(personSeats);
	attachPersonWidget(personNewBtn);
}

// Callbackfunksjoner
// BEGIN 5d
void MeetingWindow::cb_quit() {
	close();
}
// END 5d

// BEGIN 6c
void MeetingWindow::newPerson() {
	std::string name = personName.getText();
	std::string email = personEmail.getText();
	std::string seatsStr = personSeats.getText();

	if (name.empty() || email.empty()) {
		return;
	}

	Car* car = nullptr;
	if (!seatsStr.empty()) {
		try {
			int seats = std::stoi(seatsStr);
			if (seats > 0) {
				car = new Car(seats);
			}
		} catch (const std::exception&) {
			// Not a valid number, no car
		}
	}

	people.emplace_back(new Person{name, email, car});

	personName.setText("");
	personEmail.setText("");
	personSeats.setText("");
}

void MeetingWindow::printPeople() const {
	for (const auto* p : people) {
		std::cout << *p << "\n";
	}
}

MeetingWindow::~MeetingWindow() {
	for (auto* p : people) {
		delete p;
	}
}
// END 6c


void MeetingWindow::attachPersonWidget(TDT4102::Widget& pw)
{
	add(pw);
	personWidgets.emplace_back(std::ref(pw));
}
