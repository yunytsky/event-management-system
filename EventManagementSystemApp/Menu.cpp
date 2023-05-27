#include "Menu.h"
#include "Authorization.h"
#include "Event.h"
#include <iostream>
//================================================================

//Default constructor
Menu::Menu() {

}
//Constructor
Menu::Menu(std::vector<std::string> options)
{
    this->options = options;
}

//Display menu
void Menu::displayMenu()
{
    std::cout << "*******************************************************\n";
    std::cout << "****************EVENT MANAGEMENT SYSTEM****************\n";
    std::cout << "*******************************************************\n";
    
    for (int i = 0; i < this->options.size(); i++)
    {
        std::cout << "[" << i + 1 << "]" << options[i] << std::endl;
    }

    std::cout << std::endl;
}

//Choose an option
int Menu::chooseOption()
{
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    return choice;
}

//================================================================
Menu defaultMenu = Menu({ "Log in", "Sign up", "Exit" });
Menu adminMenu = Menu({ "Show attendees", "Show events", "Add an event", "Delete an event", "Invite attendee to an event", "Log out"});
Menu userMenu = Menu({ "Show my events", "Log out" });
Menu logInMenu = Menu({ "Log in as an admin", "Log in as an attendee", "Go back" });
Menu adminAttendeesMenu = Menu({ "Show all attendees", "Show one attendee by ID", "Show all attendees invited to a particular event" ,"Go back"});
Menu eventTypeCreateMenu = Menu({ "Conference", "Product launch", "Corporate party", "Go back" });
Menu eventTypeDisplayMenu = Menu({ "Show all events", "Conferences", "Product launches", "Corporate parties", "Go back" });

//================================================================

//Main menu initialization function
void initMenu()
{
    defaultMenu.displayMenu();
    bool error;
    do
    {
        error = false;
        int choice = defaultMenu.chooseOption();

        switch (choice)
        {
            //Log in
        case 1:
            system("cls");
            logIn();
            break;

            //Sign up
        case 2:
            system("cls");
            signUp();
            break;

            //Exit
        case 3:
            system("cls");
            std::cout << "Thank you for using Event Manager System" << std::endl;
            break;

        default:
            std::cout << "Try again: ";
            error = true;
        }

    } while (error);
}

