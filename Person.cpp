#include "Person.h"
#include <iostream>
#include <iomanip>
 
//Author: Jacob R. Holcomb
//Date: 4-06-2015
//Assignment: Project 2
//Description: Describes the Person Class 
//Implements the set and print functions

//Person constructor, could be expanded for defaults
//Set Pointers to NULL to provide a way to check if they are empty
Person::Person() {
	mother = NULL;
	father = NULL;
}

//Defines all of the Set Functions
void Person::setFirstName(string firstName) {
	this->firstName = firstName;
}

void Person::setMiddleName(string middleName) {
	this->middleName = middleName;
}

void Person::setLastName(string lastName) {
	this->lastName = lastName;
}

void Person::setBirthDate(string birthDate) {
	this->birthDate = birthDate;
}

void Person::setDeathDate(string deathDate) {
	this->deathDate = deathDate;
}

void Person::setGender(string gender) {
	this->gender = gender;
}

void Person::setParent(string type, Person& parent) {
	if (type == "Mother")
		this->mother = &parent;
	else
		this->father = &parent;
}

void Person::addChild(Person& child) {
	this->children.push_back(&child);
}

//Defines the Print Function for Person, prints a table.
void Person::printInfo() {
	const int stdColumnWidth = 10;
    cout << left << setw(stdColumnWidth + 5) << firstName;
	cout << left << setw(stdColumnWidth + 5) << middleName;
	cout << left << setw(stdColumnWidth + 5) << lastName;
	cout << left << setw(stdColumnWidth) << birthDate;
	cout << left << setw(stdColumnWidth) << deathDate;
	cout << left << setw(stdColumnWidth) << gender;
    cout << endl;
}