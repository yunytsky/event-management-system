#include "EventManager.h"
#include "Attendee.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <memory>
#include <json/json.h>

//Constructor
EventManager::EventManager() {
    //Get all events from json file
    std::ifstream db_events;
    Json::Value events;

    db_events.open("./Data/db_events.json", std::ifstream::binary);
    if (db_events.is_open()) {
        db_events >> events;

        for (Json::ValueIterator itr = events.begin(); itr != events.end(); itr++) {
            std::string event = itr.key().asString();
            if (events[event]["type"] == "conference") {
                Conference conference = Conference(
                    event,
                    events[event]["location"].asString(),
                    events[event]["date"].asString(),
                    events[event]["time"].asString(),
                    events[event]["topic"].asString()
                );
                conference.setId(events[event]["id"].asUInt());
                allEvents.push_back(conference);

            }
            else if (events[event]["type"] == "product launch") {
                ProductLaunch productLaunch = ProductLaunch(
                    event,
                    events[event]["location"].asString(),
                    events[event]["date"].asString(),
                    events[event]["time"].asString(),
                    events[event]["product"].asString()
                );
                productLaunch.setId(events[event]["id"].asUInt());
                allEvents.push_back(productLaunch);

            }
            else if (events[event]["type"] == "corporate party") {
                CorporateParty corporateParty = CorporateParty(
                    event,
                    events[event]["location"].asString(),
                    events[event]["date"].asString(),
                    events[event]["time"].asString(),
                    events[event]["topic"].asString()
                );
                corporateParty.setId(events[event]["id"].asUInt());
                allEvents.push_back(corporateParty);
            }
        }
    }
    else {
        std::cout << "Error\n";
    }

    db_events.close();

    //Get all attendees (users) from json file
    std::ifstream db_users;
    Json::Value users;

    db_users.open("./Data/db_users.json", std::ifstream::binary);
    if (db_users.is_open()) {
        db_users >> users;

        for (Json::ValueIterator itr = users.begin(); itr != users.end(); itr++) {
            std::string user = itr.key().asString();
            Attendee attendee = Attendee(
                user.substr(0, user.find(' ')),
                user.substr(user.find(' ') + 1),
                users[user]["email"].asString(),
                users[user]["phoneNumber"].asString(),
                users[user]["password"].asString()
            );
            attendee.setId(users[user]["id"].asUInt());

            //Vector that contains all ids of particular user's events
            std::vector<unsigned int> userEventsIds = {};
            std::vector<Event> userEventsObj= {};

            Json::Value userEvents = users[user]["events"];
            for (Json::ValueIterator itr = userEvents.begin(); itr != userEvents.end(); itr++) {
                std::string userEvent = itr.key().asString();
                userEventsIds.push_back(userEvents[userEvent]["id"].asUInt());
            }

            for (Json::ValueIterator itr = events.begin(); itr != events.end(); itr++) {
                std::string event = itr.key().asString();
                if ((std::find(userEventsIds.begin(), userEventsIds.end(), events[event]["id"].asUInt())) != userEventsIds.end()) {
                    for (Event& eventObj : allEvents) {
                        if (eventObj.getId() == events[event]["id"].asUInt()) {
                            userEventsObj.push_back(eventObj);
                        }
                    }
                }
            }

            attendee.setEvents(userEventsObj);
            allAttendees.push_back(attendee);


        }
    }
    else {
        std::cout << "Error\n";
    }

    db_users.close();

}

//Getters 
std::vector<Attendee> EventManager::getAllAttendees() {
    return allAttendees;
}

std::vector<Event> EventManager::getAllEvents() {
    return allEvents;
}

//Show all attendees function
void EventManager::showAllAttendees() {
    std::cout << "**********************************All attendees**********************************\n";
        for (Attendee& attendee : allAttendees)
    {
        std::cout << attendee << std::endl;
        std::cout << "**********************************\n";
    }
}

//Show all events function
void EventManager::showAllEvents() {
    std::cout << "**********************************All events**********************************\n";
    for (Event& event : allEvents)
    {
        event.showDetails();
        std::cout << "**********************************\n";

    }
}

//Add an attendee
bool EventManager::addAttendee(Attendee& attendee) {
    std::ifstream db_users_input;
    std::ofstream db_users_output;
    Json::Value users;
    Json::Value events(Json::objectValue);


    //Check if Id of this attendee was already taken
    unsigned int id = attendee.getId();
    bool idIsTaken = false;
    if (!allEvents.empty()) {
        for (Attendee& otherAttendee : allAttendees) {
            if (otherAttendee.getId() == id) {
                idIsTaken = true;
                break;
            }
        }
    }

    while (idIsTaken) {
        id++;
        idIsTaken = false;

        for (Attendee& otherAttendee : allAttendees) {
            if (otherAttendee.getId() == id) {
                idIsTaken = true;
                break;
            }
        }
    } 

    attendee.setId(id);


    //Parse JSON object
    db_users_input.open("./Data/db_users.json", std::ifstream::binary);
    if (db_users_input.is_open()) {
        db_users_input >> users;
        db_users_input.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    //Append a user to a JSON object
    db_users_output.open("./Data/db_users.json");
    if (db_users_output.is_open()) {

        std::string fullName = attendee.getFirstName() + " " + attendee.getLastName();
        std::string email = attendee.getEmail();
        std::string phoneNumber = attendee.getPhoneNumber();
        unsigned int id = attendee.getId();
        std::string password = attendee.getPassword();

        users[fullName]["email"] = email;
        users[fullName]["phoneNumber"] = phoneNumber;
        users[fullName]["password"] = password;
        users[fullName]["id"] = id;
        users[fullName]["events"] = events;

        db_users_output << users;
        db_users_output.close();
        if (db_users_output.fail()) {
            std::cout << "Error. Failed to write JSON to the output stream." << std::endl;
            return 0;
        }
        else {
            allAttendees.push_back(attendee);
            return 1;
        }
        return 1;

    }
    else {
        std::cout << "Error\n";
        return 0;
    }
}

//Add an event
bool EventManager::addEvent(Event& event) {
    std::ifstream db_events_input;
    std::ofstream db_events_output;
    Json::Value events;


    //Check if Id of this event was already taken
    unsigned int id = event.getId();
    bool idIsTaken = false;
    if (!allEvents.empty()) {
        for (Event& otherEvent : allEvents) {
            if (otherEvent.getId() == id) {
                idIsTaken = true;
                break;
            }
        }
    }

    while (idIsTaken) {
        id++;
        idIsTaken = false;

        for (Event& otherEvent : allEvents) {
            if (otherEvent.getId() == id) {
                idIsTaken = true;
                break;
            }
        }
    }

    event.setId(id);


    //Parse JSON object
    db_events_input.open("./Data/db_events.json", std::ifstream::binary);
    if (db_events_input.is_open()) {
        db_events_input >> events;

        db_events_input.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    //Append an event to a JSON object
    db_events_output.open("./Data/db_events.json");
    if (db_events_output.is_open()) {

        std::string name = event.getName();
        std::string location = event.getLocation();
        std::string date = event.getDate();
        std::string time = event.getTime();


        events[name]["location"] = location;
        events[name]["date"] = date;
        events[name]["time"] = time;
        events[name]["id"] = id;

        //Check what type of an event was passed as an argument
        if(Conference* conference = dynamic_cast<Conference*>(&event)) {
            std::string topic = conference->getTopic();
            events[name]["type"] = "conference";
            events[name]["topic"] = topic;
        }else if (ProductLaunch* productLaunch = dynamic_cast<ProductLaunch*>(&event)) {
            std::string product = productLaunch->getProduct();
            events[name]["type"] = "product launch";
            events[name]["product"] = product;
        }
        else if (CorporateParty* corporateParty = dynamic_cast<CorporateParty*>(&event)) {
            std::string attire = corporateParty->getAttire();
            events[name]["type"] = "corporate party";
            events[name]["attire"] = attire;
        }

        db_events_output << events;
        db_events_output.close();
        if (db_events_output.fail()) {
            std::cout << "Error. Failed to write JSON to the output stream." << std::endl;
            return 0;
        }
        else {
            allEvents.push_back(event);
            return 1;
        }
    }
    else {
        std::cout << "Error\n";
        return 0;
    }
}

//Delete an event
bool EventManager::deleteEvent(Event& event) {
    std::ifstream db_events_input;
    std::ofstream db_events_output;
    std::ifstream db_users_input;
    std::ofstream db_users_output;
    Json::Value events;
    Json::Value users;


    // Parse JSON objects
    db_events_input.open("./Data/db_events.json", std::ifstream::binary);
    if (db_events_input.is_open()) {
        db_events_input >> events;
        db_events_input.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    db_users_input.open("./Data/db_users.json", std::ifstream::binary);
    if (db_users_input.is_open()) {
        db_users_input >> users;
        db_users_input.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    // Remove the event from the JSON objects
    std::string eventName = event.getName();
    std::vector<std::string> userNames;

    if (events.isMember(eventName)) {
        for (Json::ValueIterator itr = users.begin(); itr != users.end(); itr++) {
            std::string userKey = itr.key().asString();
            if (users[userKey]["events"].isMember(eventName)) {
                users[userKey]["events"].removeMember(eventName);
                userNames.push_back(userKey);
            }
        }

        events.removeMember(eventName);


    }
    else {
        std::cout << "Event is not found\n";
        return 0;
    }


    // Save the modified JSON objects
    db_users_output.open("./Data/db_users.json");
    db_events_output.open("./Data/db_events.json");

    if (db_users_output.is_open() && db_events_output.is_open()) {
        db_users_output << users;
        db_events_output << events;
        db_events_output.close();
        db_users_output.close();
        if (db_users_output.good() && db_events_output.good()) {
            // Remove the event from the attendee events vector
            for (std::string userName : userNames) {
                for (Attendee& attendee : allAttendees) {
                    if (attendee.getFirstName() + " " + attendee.getLastName() == userName) {
                        attendee.removeAttendeeEvent(event);
                    }
                }
            }
            // Remove the event from the allEvents vector
            auto it = std::find(allEvents.begin(), allEvents.end(), event);
            if (it != allEvents.end()) {
                allEvents.erase(it);
                return 1;
            }

            return 0;

        }
        else {
            std::cout << "Error. Failed to write JSON to the output stream." << std::endl;
            return 0;
        }
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

}


//Assign an event to an attendee
bool EventManager::assignEvent(Event& event, Attendee& attendee) {
    std::ifstream db_events;
    std::ifstream db_users_input;
    std::ofstream db_users_output;

    Json::Value events;
    Json::Value users;
 
    bool found = false;

    db_events.open("./Data/db_events.json", std::ifstream::binary);
    if (db_events.is_open()) {
        db_events >> events;
        db_events.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    db_users_input.open("./Data/db_users.json", std::ifstream::binary);
    if (db_users_input.is_open()) {
        db_users_input >> users;
        db_users_input.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    std::string userName = attendee.getFirstName() + " " + attendee.getLastName();
    std::string eventName = event.getName();

    if (events.isMember(eventName) && users.isMember(userName)) {
        if (users[userName]["events"].isMember(eventName)) {
            std::cout << "Attendee is already invited to this event\n";
            return 0;
        }
        users[userName]["events"][eventName] = events[eventName];
    }
    else {
        std::cout << "Event or user not found\n";
        return 0;
    }

    db_users_output.open("./Data/db_users.json");
    if (db_users_output.is_open()) {
        db_users_output << users;
        attendee.addEvent(event);
        for (Attendee& otherAttendee : allAttendees) {
            if (otherAttendee == attendee) {
                std::vector<Event> attendeeEvents = attendee.getAttendeeEvents();
                otherAttendee.setEvents(attendeeEvents);
                break;
            }
        }
        db_users_output.close();
    }
    else {
        std::cout << "Error\n";
        return 0;
    }

    if (db_users_output.fail()) {
        std::cout << "Error. Failed to write JSON to the output stream." << std::endl;
        return 0;
    }
    else {
        return 1;
    }

}

//Initialization of global eventManager object
EventManager eventManager = EventManager();