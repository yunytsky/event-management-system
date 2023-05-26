#include "Admin.h"
#include "Menu.h"
#include "EventManager.h"
#include <chrono>
#include <thread>
#include <iostream>

//Create an event function
void createEvent(std::string eventType) {
  
    std::string name, location, date, time;
    std::cout << "Fill in the information.\n";
    std::cout << "Name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    std::cout << "Location: ";
    std::getline(std::cin, location);
    std::cout << "Date: ";
    std::getline(std::cin, date);
    std::cout << "Time: ";
    std::getline(std::cin, time);

    if (eventType == "Conference") {
        std::string topic;
        std::cout << "Topic: ";
        std::getline(std::cin, topic);

        Conference event = Conference(name, location, date, time, topic);
        if (eventManager.addEvent(event)) {
            std::cout << "\nEvent has been successfully added";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            callAdminMenu();
        }
        else {
            std::cout << "\nError. Faield to add an event";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            callAdminMenu();
        }


    }
    else if (eventType == "ProductLaunch") {
        std::string product;
        std::cout << "Product: ";
        std::getline(std::cin, product);

        ProductLaunch event = ProductLaunch(name, location, date, time, product);

        if (eventManager.addEvent(event)) {
            std::cout << "\nEvent has been successfully added";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            callAdminMenu();
        }
        else {
            std::cout << "\nError. Faield to add an event";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            callAdminMenu();
        }

    }
    else if (eventType == "CorporateParty") {
        std::string attire;
        std::cout << "Attire: ";
        std::getline(std::cin, attire);

        CorporateParty event = CorporateParty(name, location, date, time, attire);

        if (eventManager.addEvent(event)) {
            std::cout << "\nEvent has been successfully added";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            callAdminMenu();
        }
        else {
            std::cout << "\nError. Faield to add an event";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            callAdminMenu();
        }
    }
}

//Auxiliary functions
void chooseEventType() {
    eventTypeMenu.displayMenu();
    std::string eventType;
    int choice;
    std::cout << "Choose event type or enter 0 to go back: ";
    std::cin >> choice;
    bool error;
    do {
        error = false;
        switch (choice) {

            //Go back
        case 0:
            system("cls");
            callAdminMenu();
            break;
            //Conference
        case 1:
            eventType = "Conference";
            createEvent(eventType);
            break;
            //Product launch
        case 2:
            eventType = "ProductLaunch";
            createEvent(eventType);
            break;

            //Corporate party
        case 3:
            eventType = "CorporateParty";
            createEvent(eventType);
            break;

        default:
            std::cout << "Try again: ";
            error = true;
        }
    } while (error);
}
unsigned int pickAnAttendee() {
    unsigned int id;
    eventManager.showAllAttendees();
    std::cout << "Enter an ID of the attendee: ";
    std::cin >> id;
    return id;
}
unsigned int pickAnEvent() {
    unsigned int id;
    eventManager.showAllEvents();
    std::cout << "Enter an ID of the event: ";
    std::cin >> id;
    return id;
}

//Functions to assign an event to an attendee
void inviteAttendeeToAnEvent() {
    unsigned int pickedAttendeeId = pickAnAttendee();
    system("cls");

    std::vector<Attendee> allAttendees = eventManager.getAllAttendees();
    std::vector<Event> allEvents = eventManager.getAllEvents();

    bool attendeeFound = false;
    bool eventFound = false;

    while (!attendeeFound) {
    for (Attendee& attendee : allAttendees) {
        if (attendee.getId() == pickedAttendeeId) {
            attendeeFound = true;
            unsigned int pickedEventId = pickAnEvent();
            eventFound = false; // Reset eventFound to false before searching for the event
            while (!eventFound) {
                for (Event& event : allEvents) {
                    if (event.getId() == pickedEventId) {
                        eventFound = true;
                        if (eventManager.assignEvent(event, attendee)) {
                            std::cout << "\nThe attnedee has been successfully invited to the event";
                            std::this_thread::sleep_for(std::chrono::seconds(3));
                            system("cls");
                            callAdminMenu();
                        }
                        else {
                            std::cout << "\nFailed to invite the attendee to the event";
                            std::this_thread::sleep_for(std::chrono::seconds(3));
                            system("cls");
                            callAdminMenu();
                        }
                        break;
                    }
                }
                if (!eventFound) {
                    std::cout << "Wrong Event's ID. Try again\n";
                    pickedEventId = pickAnEvent();
                }
            }
            break;
        }
    }

    if (!attendeeFound) {
        std::cout << "Wrong Attendee's ID. Try again\n\n\n";
        pickedAttendeeId = pickAnAttendee();
    }
}
}

//Delete an event by id function
void deleteEventById(unsigned int id) {
    bool eventFound = false;
    while (!eventFound) {
        for (Event& event : eventManager.getAllEvents()) {
            if (event.getId() == id) {
                eventFound = true;
                if (eventManager.deleteEvent(event)) {
                    std::cout << "\nThe event has been successfully removed";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    system("cls");
                    callAdminMenu();
                }
                else {
                    std::cout << "\nFailed to remove the event";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    system("cls");
                    callAdminMenu();
                }
                break;
            }
        }

        if (!eventFound) {
            std::cout << "Wrong Attendee's ID. Try again\n\n\n";
            id = pickAnEvent();
        }
    }

}

//Navigate an admin through menu
void navigateAdmin() {
    std::string goBack;
    std::cout << "Enter 0 to go back: ";
    std::cin >> goBack;
    if (goBack == "0") {
        system("cls");
        callAdminMenu();
    }
    else {
        std::cout << "Undefined option.\nTry again: ";
        std::cin >> goBack;
    }
}

//Call admin menu function
void callAdminMenu() {
    adminMenu.displayMenu();
    bool error;
    
    do{
        error = false;
        int choice = adminMenu.chooseOption();
        switch (choice)
        {
            //Show all attendees
        case 1:
            system("cls");
            eventManager.showAllAttendees();
            navigateAdmin();
            break;

            //Show events
        case 2:
            system("cls");
            eventManager.showAllEvents();
            navigateAdmin();
            break;

            //Add an event
        case 3:
            system("cls");
            chooseEventType();
            break;

            //Delete an event
        case 4:
            system("cls");
      
            deleteEventById(pickAnEvent());
            break;


            //Invite attendee to an event
        case 5:
            system("cls");
            inviteAttendeeToAnEvent();
            break;

            //Log out
        case 6:
            system("cls");
            initMenu();
            break;

        default:
            std::cout << "Try again: ";
            error = true;
        }

    } while (error);
}
