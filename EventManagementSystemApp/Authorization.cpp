#include "Authorization.h"
#include "EventManager.h"
#include "Menu.h"
#include "Attendee.h"
#include "Admin.h"
#include <iostream>
#include<limits>
#include <chrono>
#include <conio.h>
#include <thread>
#include <json/json.h>

//Function to hide an input of a password/key
std::string getHiddenInput() {
    std::string input;
    char c;
    while ((c = _getch()) != '\r') {
        if (c == '\b') { 
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b"; 
            }
        }
        else {
            input.push_back(c);
            std::cout << '*'; 
        }
    }
    std::cout << std::endl;
    return input;
}

//Function to verify that the value is present in a file (that imitates db)
bool verifyValue(std::ifstream& file, std::string& value)
{
    bool found = false;

    std::string line;
    while (getline(file, line))
    {
        if (line == value)
        {
            found = true;
            break;
        }
    }

    file.clear();
    file.seekg(0);
    return found;
}

//Authorization functions
void logIn() {
    logInMenu.displayMenu();

    bool error;
    do
    {
        error = false;
        int choice = logInMenu.chooseOption();

        switch (choice)
        {
            //Log in as an admin
        case 1:
            system("cls");
            logInAdmin();
            break;

            //Log in as an attendee
        case 2:
            system("cls");
            logInAttendee();
            break;

            //Go back
        case 3:
            system("cls");
            initMenu();
            break;

        default:
            std::cout << "Try again: ";
            error = true;
        }

    } while (error);
}

void logInAdmin() {
    std::string adminPassword;
    bool authorized = false;
    std::ifstream db_admin;

    std::cout << "Enter your admin password or enter 0 to go back: ";
    adminPassword = getHiddenInput();

    if (adminPassword == "0") {
        logIn();
        return;
    }

    db_admin.open("./Data/db_admin.txt");

    if (db_admin.is_open())
    {
        while (!authorized)
        {
            authorized = verifyValue(db_admin, adminPassword);

            if (authorized == false)
            {
                std::cout << "Wrong password\nTry again: ";
                adminPassword = getHiddenInput();
            }
            else
            {   
                system("cls");
                callAdminMenu();
                break;
            }
        }
    }
    else
    {
        std::cout << "Error" << std::endl;
    }

    db_admin.close();
}

void logInAttendee() {
    std::string fullName;
    std::string attendeePassword;
    bool authorized = false;

    std::cout << "Enter your full name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, fullName);
   
    while (!authorized) {
        for (Attendee& attendee : eventManager.getAllAttendees()) {
            if ((attendee.getFirstName() + " " + attendee.getLastName()) == fullName) {
                std::cout << "Enter your password: ";
                attendeePassword = getHiddenInput();
                if (attendee.getPassword() == attendeePassword) {
                    system("cls");
                    callUserMenu(attendee);
                    authorized = true;
                    break;
                }
            }
        }

        if (!authorized) {
            std::cout << "Wrong credentials, try again, or enter \"0\" to go back to the main menu:\n";
            std::cout << "Enter your full name: ";
    
            std::getline(std::cin, fullName);
            if (fullName == "0") {
                system("cls");
                initMenu();
                break;
            }

        }
    }
}

void signUp() {
    std::string key, firstName, lastName, email, password, phoneNumber;
    std::ifstream keys;
    bool authorized = false;

    std::cout << "Please enter the key for registration provided by an admin or enter 0 to go back: ";
    key = getHiddenInput();


    if (key == "0") {
        system("cls");
        initMenu();
        return;
    }

    keys.open("./Data/keys.txt");

    if (keys.is_open()) {
        while (!authorized)
        {
            authorized = verifyValue(keys, key);

            if (authorized == false)
            {
                std::cout << "Wrong key\nTry again: ";
                key = getHiddenInput();
            }
            else
            {
                system("cls");
                std::cout << "Fill in the information.\n";
                std::cout << "First name: ";
                std::cin >> firstName;
                std::cout << "Last name: ";
                std::cin >> lastName;
                std::cout << "E-mail: ";
                std::cin >> email;
                std::cout << "Phone number (without +,- symbols and spaces): ";
                std::cin >> phoneNumber;
                std::cout << "Password: ";
                password = getHiddenInput();

                Attendee newAttendee = Attendee(firstName, lastName, email, phoneNumber, password);
                if (eventManager.addAttendee(newAttendee)) {
                    std::cout << "Account has been successfully created";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    system("cls");
                    initMenu();
                }
                else {
                    std::cout << "Error. Faield to create an account.";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    system("cls");
                    initMenu();
                }

                break;
            }
        }
    }
    else
    {
        std::cout << "Error" << std::endl;
    }
};