#include "Event.h"

//Base class 
//Constructor
Event::Event(std::string name, std::string location, std::string date, std::string time)
	:name(name), location(location), date(date), time(time)
{
	this->_id = 1;
}

//Destructor
Event::~Event(){}

//Virtual functions
void Event::showDetails() {
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Location: " << this->location << std::endl;
	std::cout << "Date: " << this->date << std::endl;
	std::cout << "Time: " << this->time << std::endl;
	std::cout << "Event ID: " << this->_id << std::endl;
}

void Conference::showDetails() {
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Location: " << this->location << std::endl;
	std::cout << "Date: " << this->date << std::endl;
	std::cout << "Time: " << this->time << std::endl;
	std::cout << "Event ID : " << this->_id << std::endl;
	std::cout << "Event type: " << "conference" << std::endl;
	std::cout << "Topic : " << this->topic << std::endl;
}

void CorporateParty::showDetails() {
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Location: " << this->location << std::endl;
	std::cout << "Date: " << this->date << std::endl;
	std::cout << "Time: " << this->time << std::endl;
	std::cout << "Event ID : " << this->_id << std::endl;
	std::cout << "Event type: " << "corporate party" << std::endl;
	std::cout << "Attire : " << this->attire << std::endl;
}


void ProductLaunch::showDetails() {
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Location: " << this->location << std::endl;
	std::cout << "Date: " << this->date << std::endl;
	std::cout << "Time: " << this->time << std::endl;
	std::cout << "Event ID : " << this->_id << std::endl;
	std::cout << "Event type: " << "product launch" << std::endl;
	std::cout << "Product: " << this->product << std::endl;
}

//Getters, setters
std::string Event::getName() {
	return name;
}
std::string Event::getLocation() {
	return location;
}
std::string Event::getDate() {
	return date;
}
std::string Event::getTime() {
	return time;
}
unsigned int Event::getId() {
	return _id;
}
void Event::setId(unsigned int id) {
	_id = id;
}

//Operator overloading <<
std::ostream& operator<<(std::ostream& cout, const Event& event)
{
	cout << "Name: " << event.name << std::endl;
	cout << "Event ID: " << event._id << std::endl;
	return cout;
}

//Operator overloading == (compare two events)
bool Event::operator==(const Event& other) {
	if (this->_id == other._id) {
		return 1;
	}
	else {
		return 0;
	}
}

//Derived classes
//Constructors
Conference::Conference(std::string name, std::string location, std::string date, std::string time, std::string topic)
	:Event(name, location, date, time) {
	this->topic = topic;
}
ProductLaunch::ProductLaunch(std::string name, std::string location, std::string date, std::string time, std::string product)
	:Event(name, location, date, time) {
	this->product = product;
}
CorporateParty::CorporateParty(std::string name, std::string location, std::string date, std::string time, std::string attire)
	:Event(name, location, date, time) {
	this->attire = attire;
}

//Getters
std::string Conference::getTopic() {
	return topic;
}
std::string ProductLaunch::getProduct() {
	return product;
}
std::string CorporateParty::getAttire() {
	return attire;
}
