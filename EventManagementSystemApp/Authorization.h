#pragma once
#include <string>
#include <fstream>

void logIn();
void logInAdmin();
void logInAttendee();
void signUp();
bool verifyValue(std::ifstream&, std::string&);
std::string getHiddenInput();