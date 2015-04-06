#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string> 
#include "Person.h"
#include <map>
using namespace std;

//Author: Jacob R. Holcomb
//Date: 4-06-2015
//Assignment: Project 2
//Description: Maintains a Family Tree of People

void initializeTree();
void printIntro();
void addPerson(map<string,Person>& familyTree, string key, Person& currentPerson);
Person createRelative();

int main(int argCount, char *argValues[]) {
	map <string, Person> familyTree;
	Person currentPerson;
	string currentCommand, selectedPerson;
	printIntro();

	currentCommand = " ";
	while (currentCommand != "Q") {
	  cout << endl << "What person would you like to modify (first name, last name, birthday)?"; 
	  getline(cin, selectedPerson);

	  currentPerson = familyTree.find("selectedPerson")->second;

	  cout << endl << "Command> ";
	  getline(cin, currentCommand);

	  if (currentCommand == "M") {
		 currentPerson.setMother(createRelative());
	  } else if (currentCommand == "F") {
		 currentPerson.setFather(createRelative());
	  } else if (currentCommand == "C") {
	     currentPerson.addChild(createRelative());
	  } else if (currentCommand == "I") {

	  } else if (currentCommand == "D") {
		
	  } else if (currentCommand == "Q") {
		 cout << endl << "Family Tree Manager Shutting Down..." << endl;
	  } else
		 cout << endl << "Invalid Command" << endl;
	}
	return EXIT_SUCCESS;
}

//Initializes Tree based on the given structure of a text file
//This structure follows the scheme setup by Dr. Heuring.
//The code here adheres to this structure and parses strings
//accordingly.
void initializeTree() {

}

//Prints the Family Tree Manager Introduction
void printIntro() {
	cout << "Welcome to Jake's Family Tree Manager Version 1.0" << endl;
	cout << endl << "The following commands can be used:" << endl;
	cout << "*   M - Add a person's mother" << endl;
	cout << "*   F - Add a person's father" << endl;
	cout << "*   C - Add a person's child" << endl;
	cout << "*   I - List immediate family (parents and siblings)" << endl;
	cout << "*   D - List the number of children, grandchildren and great grandchildren" << endl;
	cout << "*   Q - Quit the application" << endl;
}

void addPerson(map<string,Person>& familyTree, string key, Person& currentPerson) {
	familyTree[key] = currentPerson;
}

Person createRelative() {
	string firstName, middleName, lastName;
	string birthDate, deathDate, gender;
	Person relative;

	firstName = lastName = birthDate = "";

	cout << endl << "-------------------" << endl;
	cout << endl << "| Creating Parent |" << endl;
	cout << endl << "-------------------" << endl;

	while (firstName == "") {
		cout << endl << "First Name: ";
		getline(cin, firstName);
	}

	cout << "Middle Name: ";
	getline(cin, middleName);

	while (lastName == "") {
		cout << "Last Name: ";
		getline(cin, lastName);
	}

	while (birthDate == "") {
		cout << "Birth Date: ";
		getline(cin, birthDate);
	}
	
	cout << "Date of Death: ";
	getline(cin, deathDate);
	cout << "Gender: ";
	getline(cin, gender);

	relative.setFirstName(firstName);
	relative.setMiddleName(middleName);
	relative.setLastName(lastName);
	relative.setBirthDate(birthDate);
	relative.setDeathDate(deathDate);
	relative.setGender(gender);

	return relative;
}

