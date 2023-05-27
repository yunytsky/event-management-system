#pragma once
#include "Attendee.h"
#include <vector>
//================================================================

//Event manager class declaration
class EventManager
{
private:
	std::vector<Attendee*> allAttendees;
	std::vector<Event*> allEvents;

public:
	EventManager();
	~EventManager();

	std::vector<Attendee*> getAllAttendees();
	std::vector<Event*> getAllEvents();

	void showAllAttendees();
	void showOneAttendee(unsigned int id);
	void showEvents(std::string);
	void showAllAttendeesInvited(Event* event);

	bool addAttendee(Attendee*);
	bool addEvent(Event*);
	bool deleteEvent(Event*);
	bool assignEvent(Event*, Attendee*);
};

extern EventManager eventManager;
