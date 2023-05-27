#pragma once
#include <string>
//================================================================

//Create an event (function is available only for admins)
void createEvent(std::string);

//Choose event type function
void chooseEventType();

//Auxiliary functions
unsigned int pickAnAttendee();
unsigned int pickAnEvent();

//Admin's menu functions
void callAdminMenu();
void navigateAdmin();
void deleteEventById(unsigned int);
void callShowEventsAdminMenu();
void callShowAttendeesAdminMenu();
void callInvitedAttendeesMenu();