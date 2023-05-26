#pragma once
#include <string>
#include <fstream>
//================================================================

//Declaring authorization functions
void logIn();
void logInAdmin();
void logInAttendee();
void signUp();
bool verifyValue(std::ifstream&, std::string&);
std::string getHiddenInput();