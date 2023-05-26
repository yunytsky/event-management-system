#pragma once
#include <vector>
#include <string>

//Menu class declaration
class Menu
{
public:
	std::vector<std::string> options;

	Menu();
	Menu(std::vector<std::string>);

	void displayMenu();
	int chooseOption();
};

//Main menu initialization
void initMenu();

//=============================================================
extern Menu defaultMenu;
extern Menu adminMenu;
extern Menu userMenu;
extern Menu logInMenu;
extern Menu adminAttendeesMenu;
extern Menu adminEventsMenu;
extern Menu eventTypeMenu ;