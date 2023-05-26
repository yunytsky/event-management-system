#pragma once
#include "Attendee.h"
#include <vector>

class EventManager
{
private:
	std::vector<Attendee> allAttendees;
	std::vector<Event> allEvents;

public:
	EventManager();
	std::vector<Attendee> getAllAttendees();
	std::vector<Event> getAllEvents();
	void showAllAttendees();
	void showAllEvents();
	bool addAttendee(Attendee&);
	bool addEvent(Event&);
	bool deleteEvent(Event&);
	bool assignEvent(Event&, Attendee&);
};

extern EventManager eventManager;
