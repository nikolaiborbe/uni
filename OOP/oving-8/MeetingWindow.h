#pragma once

#include "AnimationWindow.h"
#include "Meeting.h"
#include "Person.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"

#include <string>
#include <vector>
#include <functional>


// Meeting GUI
class MeetingWindow : public TDT4102::AnimationWindow
{
	public:
	// BEGIN 5c
	static constexpr int pad = 10;
	static constexpr int btnW = 100;
	static constexpr int btnH = 30;
	static constexpr int fieldW = 200;
	static constexpr int fieldH = 30;
	// END 5c

	MeetingWindow(TDT4102::Point position, int width, int height, const std::string& title);

	// Avslutt knapp
	// BEGIN 5e
	TDT4102::Button quitBtn;
	// END 5e

	// Callback-funksjoner
	// BEGIN 5d
	void cb_quit();
	// END 5d


	// Person
	// BEGIN 6a
	TDT4102::TextInput personName;
	TDT4102::TextInput personEmail;
	// END 6a

	// BEGIN 6b
	TDT4102::TextInput personSeats;
	TDT4102::Button personNewBtn;
	// END 6b


	// Personer
	// BEGIN 6c
	std::vector<Person*> people;
	void newPerson();
	void printPeople() const;
	// END 6c

	int dummyArgument;

	// Hjelpefunksjoner og variabler
	void attachPersonWidget(TDT4102::Widget& pw);
	std::vector<std::reference_wrapper<TDT4102::Widget>> personWidgets;

	~MeetingWindow();
};
