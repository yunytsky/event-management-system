#include "Attendee.h"
#include "Menu.h"
#include "EventManager.h"
#include <iostream>
//================================================================

//Constructor
Attendee::Attendee(std::string firstName, std::string lastName, std::string email, std::string phoneNumber, std::string password)
	: firstName(firstName), lastName(lastName), email(email), phoneNumber(phoneNumber), password(password) {
	this->attendeeEvents = {};
    this->_id = 1;
}

//Destructor
Attendee::~Attendee(){
    for (Event* event : attendeeEvents) {
        delete event;
    }
    attendeeEvents.clear();
}

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
std::vector<Event*> Attendee::getAttendeeEvents() {
    return attendeeEvents;
}

void Attendee::setId(unsigned int id) {
    _id = id;
}
void Attendee::setEvents(std::vector<Event*> events) {
    attendeeEvents = events;
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

            cout << i + 1 << ") " << *attendee.attendeeEvents[i];
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

//Assign event to an attendee
void Attendee::addEvent(Event* event) {
    attendeeEvents.push_back(event);
}

//Remove event
void Attendee::removeAttendeeEvent(Event* event) {
    auto it = std::find(attendeeEvents.begin(), attendeeEvents.end(), event);
    if (it != attendeeEvents.end()) {
        attendeeEvents.erase(it);
    }
}

void Attendee::showAttendeeEvents(std::string type) {
    bool empty = true;

    if (!attendeeEvents.empty()) {
        if (type == "") {
            std::cout << "**********************************My events**********************************\n";
            for (Event* attendeeEvent : attendeeEvents) {
                std::cout << std::endl;
                attendeeEvent->showDetails();
                std::cout << std::endl;
                std::cout << "**********************************\n";
            }
        }
        else if (type == "ProductLaunch") {
            std::cout << "**********************************My product launch events**********************************\n";
            for (Event* attendeeEvent : attendeeEvents) {
                if (ProductLaunch* productLaunchAttendeeEvent = dynamic_cast<ProductLaunch*>(attendeeEvent)) {
                    empty = false;
                    productLaunchAttendeeEvent->showDetails();
                    std::cout << "**********************************\n";
                }
            }
            if (empty) {
                std::cout << "No product launch events yet\n";
            }
        }
        else if (type == "Conference") {
            std::cout << "**********************************My conferences**********************************\n";
            for (Event* attendeeEvent : attendeeEvents) {
                if (Conference* conferenceAttendeeEvent = dynamic_cast<Conference*>(attendeeEvent)) {
                    empty = false;
                    conferenceAttendeeEvent->showDetails();
                    std::cout << "**********************************\n";
                }
            }
            if (empty) {
                std::cout << "No conferences events yet\n";
            }
        }
        else if (type == "CorporateParty") {
            std::cout << "**********************************My corporate parties**********************************\n";
            for (Event* attendeeEvent : attendeeEvents) {
                if (CorporateParty* corporatePartyAttendeeEvent = dynamic_cast<CorporateParty*>(attendeeEvent)) {
                    empty = false;
                    corporatePartyAttendeeEvent->showDetails();
                    std::cout << "**********************************\n";
                }
            }
            if (empty) {
                std::cout << "No corporate parties yet\n";
            }
        }

    }
    else
    {
        std::cout <<"No events yet\n";
    }



}


//======================================================================
//Attendee's menu functions

//Navigate attendee through menu
void navigateAttendee(Attendee& attendee) {
    std::string goBack;
    std::cout << "\nEnter 0 to go back: ";
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

//Show  attendee events functions
void callShowEventsAttendeeMenu(Attendee& attendee) {
    eventTypeDisplayMenu.displayMenu();
    std::string eventType;
    int choice;
    bool error;
    do {
        error = false;
        choice = eventTypeDisplayMenu.chooseOption();
        switch (choice) {
            //Al events
        case 1:
            system("cls");
            attendee.showAttendeeEvents(eventType);
            break;
            //Conferences
        case 2:
            eventType = "Conference";
            system("cls");
            attendee.showAttendeeEvents(eventType);
            break;
            //Product launches
        case 3:
            eventType = "ProductLaunch";
            system("cls");
            attendee.showAttendeeEvents(eventType);
            break;

            //Corporate parties
        case 4:
            eventType = "CorporateParty";
            system("cls");
            attendee.showAttendeeEvents(eventType);
            break;

            //Go back
        case 5:
            system("cls");
            callUserMenu(attendee);
            break;

        default:
            std::cout << "Try again: ";
            error = true;
        }
    } while (error);
}

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

        //Show events
        case 1:
            system("cls");
            callShowEventsAttendeeMenu(attendee);
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
