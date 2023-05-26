#pragma once
#include <string>
#include <iostream>
//================================================================

//Declaring Event base class
class Event{
protected:
	std::string name, location, date, time;
	unsigned int _id;
public:
	Event(std::string, std::string, std::string, std::string);

	std::string getName();
	std::string getLocation();
	std::string getDate();
	std::string getTime();
	unsigned int getId();
	void setId(unsigned int id);

	virtual void showDetails();

	friend std::ostream& operator<<(std::ostream&, const Event&);
	bool operator==(const Event& other);
};


//Declaring derived classes
class Conference:public Event{
private:
	std::string topic;
public:
	Conference(std::string, std::string, std::string, std::string, std::string);
	std::string getTopic();
	void showDetails() override;
};

class ProductLaunch:public Event {
private:
	std::string product;
public:
	ProductLaunch(std::string, std::string, std::string, std::string, std::string);
	std::string getProduct();
	void showDetails() override;

};

class CorporateParty: public Event {
private:
	std::string attire;
public:
	std::string getAttire();
	CorporateParty(std::string, std::string, std::string, std::string, std::string);
	void showDetails() override;
};