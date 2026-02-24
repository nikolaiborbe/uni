#include "Person.h"
#include "Meeting.h"
#include "MeetingWindow.h"
#include <iostream>

int main()
{
	MeetingWindow mw{{100, 100}, 500, 400, "Meetings"};
	mw.wait_for_close();
	mw.printPeople();

	return 0;
}
