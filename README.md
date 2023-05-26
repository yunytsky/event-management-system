# Event Management System - C++ Console Application


<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/3_mainMenu.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/3_mainMenu.png">
  <img alt="Shows the main menu of the app" src="https://github.com/yunytsky/event-management-system/blob/main/Samples/3_mainMenu.png">
</picture>


## Functionality
The program provides an ability to manage a collection of events and attendees, it allows to log in to the system either as an attendee (also referred to as a user in the program) or as an admin.

Attendee can display events they are invited to (filter by category or display all of them). 
An attendee (user) can also sign up by providing the registration-key. 

Admin can display all events (filter by category or display all of the existing events), display all of the existing users (along with events they are invited to), create a new event, delete an existing event (it will also delete if from the vectors with events of all users that were invited to that event), invite attendee to an event.

Users (attendees) cannot invite themselves to events, only admin can. 

Navigation throught the different sections is implemented, there's no need to re-open an application.

## Screenshots

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/4_logInMenu.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/4_logInMenu.png">
  <img alt="Shows the login menu" src="https://github.com/yunytsky/event-management-system/blob/main/Samples/4_logInMenu.png">
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/6_userMenu.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/6_userMenu.png">
  <img alt="Shows the user (attendee) menu" src="https://github.com/yunytsky/event-management-system/blob/main/Samples/6_userMenu.png">
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/5_adminMenu.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/5_adminMenu.png">
  <img alt="Shows the admin menu" src="https://github.com/yunytsky/event-management-system/blob/main/Samples/5_adminMenu.png">
</picture>


## Authorization
Authorization is implemented by using JSON files (as well as some txt files for simplicity) to store the data about events and users (attendees) with **jsoncpp** library.

All the sample files are stored under Data directory, directory was not added to .gitignore by intenton. *Passwords and keys in the files are not encrypted*.

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/1_events_json_sample.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/1_events_json_sample.png">
  <img alt="Shows a sample of json file that stores events" src="https://github.com/yunytsky/event-management-system/blob/main/Samples/1_events_json_sample.png">
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/2_users_json_sample.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/yunytsky/event-management-system/blob/main/Samples/2_users_json_sample.png">
  <img alt="Shows a sample of json file that stores users" src="https://github.com/yunytsky/event-management-system/blob/main/Samples/2_users_json_sample.png">
</picture>


### Classes
- Attendee
- Event
- ProductLaunch:Event
- Conference:Event
- CorporateParty:Event
- EventManager
- Menu


### Project structure
Project contains of 6 header files, 6 implementation files and Main.cpp.
- Menu.h, Menu.cpp. Declaration and implementation of Menu class and creating objects of Menu class (menus that will be used in the program), declaration and implementation of initMenu() function that initializes the main menu.
- Authorization.h, Authotization.cpp. Declaration and implementation of functions that are used for authorizing a user (attendee) or an admin.
- Admin.h, Admin.cpp. Declaration and implementation of a function that calls menu for an authorized admin, declaration and implementation of functions that are available in admin menu.
- Attendee.h, Attendee.cpp. Declaration and implementation of an Attendee class, declaration and implementation of a function that calls menu for an authorized user (attendee),declaration and implementation of functions that are available in user (attendee) menu. 
- Event.h, Event.cpp. Declaration and implementation of an Event base class and derived from Event classes.
- Main.cpp. The program is being initalized in main function, using initMenu() function declared in  Menu.h


### How to use
```
git clone https://github.com/yunytsky/event-management-system.git
```
For more information about **jsoncpp** library follow the [link](https://github.com/open-source-parsers/jsoncpp)




