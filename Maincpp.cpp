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
void addPersonToTree(map<string,Person>& familyTree, Person& currentPerson);
bool isPersonFound(string selectedPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it);
void addRelative(map<string,Person>& familyTree);
void connectRelative(string type, map<string,Person>& familyTree, Person& currentPerson);
Person createRelative();
bool hasParent(string type, Person& currentPerson);
string getConnectingChoice(string type, Person& currentPerson);
void performChoiceOne(string type, Person& currentPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it);

int main(int argCount, char *argValues[]) {
	map <string, Person> familyTree;
	map<string, Person>::iterator it;
	Person currentPerson;
	string currentCommand, selectedPerson, response;
	string firstName, lastName, birthDate;
	printIntro();

	it = familyTree.end();
	currentCommand = "";

	while (currentCommand != "Q") {
		currentCommand = "";
		cout << endl << "---------------------" << endl;
		cout << endl << "|  Modifying Stage  |" << endl;
		cout << endl << "---------------------" << endl;

		cout << endl << "What person would you like to modify (first name, last name, birthday)?"; 
		getline(cin, selectedPerson);

		//A user can quit by entering Q in the first prompt as well
		if (selectedPerson == "Q")
			break;

		// Stage One - Selecting the Person to edit in the Family Tree
		// Case 1 - The Person was found and we continue about our way.
		// Case 2 - The Person is not found and we provide an alternative creation method.

		//Stage One (Case 1)
		if (isPersonFound(selectedPerson, familyTree, it) == true) {
			while (currentCommand == "") {
				currentPerson = it->second;
				cout << endl << "Command> ";
				getline(cin, currentCommand);

				if (currentCommand == "M") {
					connectRelative("Mother", familyTree, currentPerson);
				} else if (currentCommand == "F") {
					connectRelative("Father", familyTree, currentPerson);
				} else if (currentCommand == "C") {
					connectRelative("Child", familyTree, currentPerson);
				} else if (currentCommand == "I") {

				} else if (currentCommand == "D") {
		
				} else if (currentCommand == "Q") {
					cout << endl << "Family Tree Manager Shutting Down..." << endl;
				} else {
					cout << endl << "Invalid Command" << endl;
					currentCommand = "";
				}
			}
		//Stage One (Case 2)
		} else 
			addRelative(familyTree);
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
	cout << endl << "*   M - Add a person's mother" << endl;
	cout << "*   F - Add a person's father" << endl;
	cout << "*   C - Add a person's child" << endl;
	cout << "*   I - List immediate family (parents and siblings)" << endl;
	cout << "*   D - List the number of children, grandchildren and great grandchildren" << endl;
	cout << "*   Q - Quit the application" << endl;
}

void addPersonToTree(map<string,Person>& familyTree, Person& currentPerson) {
	string firstName, lastName, birthDate;
	
	firstName = currentPerson.getFirstName();
	lastName  = currentPerson.getLastName();
	birthDate = currentPerson.getBirthDate();
	familyTree[firstName + ", " + lastName + ", " + birthDate] = currentPerson;
	cout << endl << "   * " + currentPerson.getFirstName() + " " + currentPerson.getLastName() <<
		" was added to the Family Tree." << endl;
}

Person createRelative() {
	string firstName, middleName, lastName;
	string birthDate, deathDate, gender;
	Person relative;

	firstName = lastName = birthDate = "";

	cout << endl << "---------------------" << endl;
	cout << endl << "| Creating Relative |" << endl;
	cout << endl << "---------------------" << endl;

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

	cout << endl << "The following steps were completed:" << endl;
	cout << endl << "   * Person " + relative.getFirstName() + " " + relative.getLastName() + " was created." << endl;
	return relative;
}

bool isPersonFound(string selectedPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it) {
	it = familyTree.find(selectedPerson);
	if (it == familyTree.end()) 	
		return false;
	else 
		return true;
}

//The person that was requested did not exist, prompt the user and ask
//if they would like to create a new person and add it to the Family Tree

void addRelative(map<string,Person>& familyTree) {
	string response;
	string firstName, lastName, birthDate;
	Person currentPerson;
	cout << endl << "Person does not exist!!! Would you like to create them??? (y or n):";
	getline(cin, response);

	if (response == "y" || response == "Y") {
		currentPerson = createRelative();
		addPersonToTree(familyTree, currentPerson);
	} 
}

//currentPerson:  The current person that the user has selected/working on.
//it->second the iterator pointer to Mother, Father or Child to be added.
//Choice 1:  Allows an existing a Mother/Father/Child to be connected to currentPerson
//Choice 2:  Allows the user to create a new Person to represent the Mother/Father/Child to be added

void connectRelative(string type, map<string,Person>& familyTree, Person& currentPerson) {
	string choice, connection;
	map<string, Person>::iterator it;

	cout << endl << "-------------------" << endl;
	cout << endl << "   Adding " + type  << endl;
	cout << endl << "-------------------" << endl;

	cout << endl << "Enter one of the following connecting methods (1 or 2):" << endl;
	cout << "   " << "[1] Add an existing " + type + " to " + currentPerson.getFirstName() + " " + currentPerson.getLastName() + "." << endl;
	cout << "   " << "[2] Create a " + type + " to add to " + currentPerson.getFirstName() + " " + currentPerson.getLastName() + "." << endl;
	getline(cin, choice);


	//The user wishes to add a parent and the currentPerson doe not have a mother/father.
	//Allow for Choices 1 and 2
	if (type == "Father" || type == "Mother") {
		if (!hasParent(type, currentPerson)) {
			if (choice == "1") {
				performChoiceOne(type, currentPerson, familyTree, it);
			}
		} else 
			cout << endl << "Sorry, but " + currentPerson.getFirstName() + " " + currentPerson.getLastName() + " already has " + type + ", " + (*currentPerson.getParent(type)).getFirstName() + " " <<
				(*currentPerson.getParent(type)).getLastName() << endl;
	} else if (type == "Child") {
		if (choice == "1") {
			performChoiceOne(type, currentPerson, familyTree, it);
		}
	}

	/*
			} else if (type == "Child-Of-Mother") {
				it->second.setMother(currentPerson);
				currentPerson.addChild(it->second);
				addPersonToTree(familyTree, currentPerson);
			} else if (type == "Child-Of-Father") {
				it->second.setFather(currentPerson);
				currentPerson.addChild(it->second);
				addPersonToTree(familyTree, currentPerson);
			}

		} */
}

bool hasParent(string type, Person& currentPerson) {
	if (currentPerson.getParent(type) != NULL) 
		return true;
	else 
		return false;
}

void performChoiceOne(string type, Person& currentPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it) {
	string connection;
	
	cout << endl << "What " + type + " would you like to add (first name, last name, birthday)?"; 
	getline(cin, connection);

	if (isPersonFound(connection, familyTree, it) == true) {
		if (type == "Mother" || "Father") {
			//The Parent
			it->second.addChild(currentPerson);
			//The Child
			currentPerson.setParent(type, it->second);
		} else if (type == "Child") {
			//currentPerson is the Parent in this case and it->second it the Child that was searched
			//We need to check to see if the child already has a mother or father before adding
			if (currentPerson.getGender() == "M" && it->second.getParent("Father") == NULL) {
				it->second.setParent("Father", currentPerson);
				currentPerson.addChild(it->second);
			} else if (currentPerson.getGender() == "F" && it->second.getParent("Mother") == NULL) {
				it->second.setParent("Mother", currentPerson);
				currentPerson.addChild(it->second);
			} else {
				cout << endl << "Sorry but " + it->second.getFirstName() + " " + it->second.getLastName() + " " 
					+ "already has the type of parent you are trying to add." << endl;
				return;
			}

		} 
		it = familyTree.find(currentPerson.getFirstName() + ", " + currentPerson.getLastName() + ", " + currentPerson.getBirthDate());
		it->second = currentPerson;
		cout << endl << "The following steps were completed:" << endl;
		cout << "   * " + currentPerson.getFirstName() + " " + currentPerson.getLastName() + " was added as a child of " 
			 << (*currentPerson.getParent(type)).getFirstName() + " " + (*currentPerson.getParent(type)).getLastName() + "." << endl; 
	} else
		cout << endl << "No " + type + " with the entered criteria existed, nothing was done..." << endl;
}

void choiceTwo() {

}

