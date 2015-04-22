#ifndef __PERSON_H__
#define __PERSON_H__
#include <string>
#include <vector>
using namespace std;

//Author: Jacob R. Holcomb
//Date: 4-06-2015
//Assignment: Project 2
//Description: Creates a reusable Person Class

class Person {
private:
	string firstName, middleName, lastName;
	string birthDate, deathDate, gender;
	Person *mother, *father;
	vector<Person*> children;

public:
	//Default Constructor 
	Person();
	
	//Set Functions for Person
	void setFirstName(string firstName);
	void setMiddleName(string middleName);
	void setLastName(string lastName);
	void setBirthDate(string birthDate);
	void setDeathDate(string deathDate);
	void setGender(string gender);
	void setParent(string type, Person& mother);
	void addChild(Person& child);

	//Print Function for Person
	void printInfo();

	//Get Functions for Person
	string getFirstName()  { return firstName;}
	string getLastName()   { return lastName;}
	string getMiddleName() { return middleName;}
	string getBirthDate()  { return birthDate;}
	string getDeathDate()  { return deathDate;}
	string getGender()     { return gender;}
	int getNumChildren()   { return children.size();}
	vector<Person*> getChildren() { return children;}

	Person* getParent(string type) {
		if (type == "Mother") 
			return mother;
		else
			return father;
	}
};
 
#endif