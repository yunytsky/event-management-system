#pragma once
#include "Event.h"
#include <iostream>
#include <vector>
#include <string>
//================================================================

//Class declaration
class Attendee
{
private:
	std::string firstName, lastName, email, password, phoneNumber;
	unsigned int _id;
	std::vector<Event*> attendeeEvents;
public:
	std::string getFirstName();
	std::string getLastName();
	std::string getEmail();
	std::string getPassword();
	unsigned int getId();
	std::string getPhoneNumber();
	std::vector<Event*> getAttendeeEvents();

	void setId(unsigned int);
	void setEvents(std::vector<Event*>);

	Attendee(std::string, std::string, std::string, std::string, std::string);
	~Attendee();

	void addEvent(Event*);
	void removeAttendeeEvent(Event*);
	void showAttendeeEvents(std::string);

	friend std::ostream& operator<<(std::ostream&, const Attendee&);
	bool operator==(const Attendee&);

};

//Attendee's menu functions
void callUserMenu(Attendee&);
void navigateAttendee(Attendee&);
void callShowEventsAttendeeMenu(Attendee&);


