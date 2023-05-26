#include "Attendee.h"
#include "Menu.h"
#include "EventManager.h"
#include <iostream>

//Constructor
Attendee::Attendee(std::string firstName, std::string lastName, std::string email, std::string phoneNumber, std::string password)
	: firstName(firstName), lastName(lastName), email(email), phoneNumber(phoneNumber), password(password) {
	this->attendeeEvents = {};
}

//Destructor
Attendee::~Attendee(){}

//Getters, setters
std::string Attendee::getFirstName() {
	return firstName;
}
std::string Attendee::getLastName() {
	return lastName;
}
std::string Attendee::getEmail() {
	return email;
}
std::string Attendee::getPassword() {
	return password;
}
std::string Attendee::getPhoneNumber() {
	return phoneNumber;
}
unsigned int Attendee::getId() {
    return _id;
};
std::vector<Event> Attendee::getAttendeeEvents() {
    return attendeeEvents;
}

void Attendee::setId(unsigned int id) {
    _id = id;
}
void Attendee::setEvents(std::vector<Event>& events) {
    attendeeEvents = events;
}

//Assign event to an attendee
void Attendee::addEvent(Event &event) {
    attendeeEvents.push_back(event);
}

//Remove event
void Attendee::removeAttendeeEvent(Event& event) {
    auto it = std::find(attendeeEvents.begin(), attendeeEvents.end(), event);
    if (it != attendeeEvents.end()) {
        attendeeEvents.erase(it);
    }
}

//Shoe all attendee events function
void Attendee::showAttendeeEvents() {
    std::vector<Event> attendeeEvents = this->getAttendeeEvents();
    if (!attendeeEvents.empty()) {
        for (Event attendeeEvent : attendeeEvents) {
            attendeeEvent.showDetails();
        }
    }
    else
    {
        std::cout <<"No events yet\n";
    }

}

//Operator overloading <<
std::ostream& operator<<(std::ostream& cout, const Attendee& attendee)
{
	cout << "First name: " << attendee.firstName << std::endl;
	cout << "Last name: " << attendee.lastName << std::endl;
	cout << "Email: " << attendee.email << std::endl;
	cout << "Phone number: " << attendee.phoneNumber << std::endl;
    cout << "Attendee ID: " << attendee._id << std::endl;

    if (!(attendee.attendeeEvents.empty())) {
        cout << "---------------------\n";

        cout << "Events:\n";

        for (int i = 0; i < attendee.attendeeEvents.size(); i++)
        {
            cout << i+1 << ") " << attendee.attendeeEvents[i];
        }

    }

	return cout;
}

//Operator overloading == (compare two attendees)
bool Attendee::operator==(const Attendee& other) {
    if (this->_id == other._id) {
        return 1;
    }
    else {
        return 0;
    }
}


//======================================================================
//Attendee's menu functions

//Navigate attendee through menu
void navigateAttendee(Attendee& attendee) {
    std::string goBack;
    std::cout << "Enter 0 to go back: ";
    std::cin >> goBack;
    if (goBack == "0") {
        system("cls");
        callUserMenu(attendee);
    }
    else {
        std::cout << "Undefined option.\nTry again: ";
        std::cin >> goBack;
    }
};

//Call Attendee's menu after authorization
void callUserMenu(Attendee& attendee) {
	userMenu.displayMenu();
    bool error;
    do
    {
        error = false;
        int choice = userMenu.chooseOption();

        switch (choice)
        {

        //Show all events
        case 1:
            system("cls");
            attendee.showAttendeeEvents();
            navigateAttendee(attendee);
            break;

        //Log out
        case 2:
            system("cls");
            initMenu();
            break;

        default:
            std::cout << "Try again: ";
            error = true;
        }

    } while (error);
}
