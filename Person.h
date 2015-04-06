#ifndef __PERSON_H__
#define __PERSON_H__
#include <string>
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

public:
	//Default Constructor
	Person();
	
	//Set Functions for Author
	void setFirstName(string firstName);
	void setMiddleName(string middleName);
	void setLastName(string lastName);
	void setBirthDate(string birthDate);
	void setDeathDate(string deathDate);
	void setGender(string gender);
	void setMother(Person& mother);
	void setFather(Person& father);

	//Print Function for Author
	void printInfo();

	//Get Functions for Author
	string getFirstName()  { return firstName;}
	string getLastName()   { return lastName;}
	string getMiddleName() { return middleName;}
	string getBirthDate()  { return birthDate;}
	string getDeathDate()  { return deathDate;}
	string getGender()     { return gender;}
	Person getMother()     { return *mother;}
	Person getFather()     { return *father;}
};
 
#endif