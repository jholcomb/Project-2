#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string> 
#include "Person.h"
#include <fstream>
#include <map>
using namespace std;

//Author: Jacob R. Holcomb
//Date: 4-06-2015
//Assignment: Project 2
//Description: Maintains a Family Tree of People

void initializeTree(map<string,Person>& familyTree, map<string, Person>::iterator it);
void printIntro();
bool isPersonFound(string selectedPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it);
void addRelative(map<string,Person>& familyTree, string type, Person &currentPerson);
Person createRelative(string type);
void connectRelative(map<string,Person>& familyTree, string type, Person &currentPerson, Person &personToAttach);
bool hasParent(string type, Person& currentPerson);
void listImmediateFamily(Person& currentPerson);
void getNumOfAllChildren(Person& currentPerson, int &numChildren, int &numGrandchildren, int &numGreatGrandChildren);

int main(int argCount, char *argValues[]) {
	map <string, Person> familyTree;
	map<string, Person>::iterator it;
	Person *currentPerson, personToAttach;
	string currentCommand, selectedPerson, type;
	string firstName, lastName, birthDate;
	int numChildren, numGrandchildren, numGreatGrandChildren;

	printIntro();

	it = familyTree.end();
	
	currentCommand = "";

	initializeTree(familyTree, it);

	
	// Stage One - Selecting the Person to edit in the Family Tree
	while (currentCommand != "Q") {
		currentCommand = "";
	
		cout << endl << "-------------------------------------------------------------------------------" << endl;
		cout << endl << "                      Stage 1 - Selecting a User "  << endl;
		cout << endl << "-------------------------------------------------------------------------------" << endl;

		cout << endl << "What person would you like to modify (first name, last name, birthday)?"; 
		getline(cin, selectedPerson);

		//A user can quit by entering Q in the first prompt as well
		if (selectedPerson == "Q")
			break; 

		// Case 1 - The person is a part of the tree, continue
		if (isPersonFound(selectedPerson, familyTree, it) == true) {
			while (currentCommand == "") {
				numChildren = numGrandchildren = numGreatGrandChildren = 0;
				currentPerson = &it->second;
				cout << endl << "Command> ";
				getline(cin, currentCommand);
				
				if (currentCommand == "M" || currentCommand == "F") {
					if (currentCommand == "M")
						type = "Mother";
					else if (currentCommand == "F")
						type = "Father";

					if ((*currentPerson).getParent(type) == NULL) {
						personToAttach = createRelative(type);
						connectRelative(familyTree, type, *currentPerson, personToAttach);
						addRelative(familyTree, type, personToAttach);
					} else 
						cout << endl << (*currentPerson).getFirstName() + " " + (*currentPerson).getLastName() + " already has a " + type << endl;
				} else if (currentCommand == "C") {
					type = "Child";
					personToAttach = createRelative(type);
					connectRelative(familyTree, type, personToAttach, *currentPerson);
					addRelative(familyTree, type, personToAttach);
				} else if (currentCommand == "I") {
					listImmediateFamily(*currentPerson);
				} else if (currentCommand == "D") {
					getNumOfAllChildren(*currentPerson, numChildren, numGrandchildren, numGreatGrandChildren);
				} else if (currentCommand == "Q") {
					cout << endl << "Family Tree Manager Shutting Down..." << endl;
				} else {
					cout << endl << "Invalid Command" << endl;
					currentCommand = "";
				}
			}
		//Stage One (Case 2) - Person was not found, start over
		} else 
			cout << endl << "Entry: " + selectedPerson + " does not exist." << endl;
	}
	return EXIT_SUCCESS;
}

//Initializes Tree based on the given structure of a text file
//This structure follows the scheme setup by Dr. Heuring.
//The code here adheres to this structure and parses strings
//accordingly.
void initializeTree(map<string,Person>& familyTree, map<string, Person>::iterator it) {
	ifstream inputFile("truman.txt");
    string line1, line2, line3, line4, line5, line6;
	string type = "File";
	Person currentPerson, *selectedPerson, *personToAttach;
	bool readyForConnections = false;
	
    while(!inputFile.eof()) {
		if (readyForConnections == false) {
			getline(inputFile, line1);
			getline(inputFile, line2);
			getline(inputFile, line3);
			getline(inputFile, line4);
			getline(inputFile, line5);

			if (line5 == "mother-of" || line5 == "father-of" || line5 == "child-of") {
				readyForConnections = true;
				//Complete First Connection Here
				continue;
			}

			getline(inputFile, line6);

			currentPerson.setFirstName(line1);
			currentPerson.setMiddleName(line2);
			currentPerson.setLastName(line3);
			currentPerson.setBirthDate(line4);
			currentPerson.setDeathDate(line5);
			currentPerson.setGender(line6);

			addRelative(familyTree, type, currentPerson);
		} else if (readyForConnections == true) {
			it = familyTree.find(line1 + ", " + line3 + ", " + line4);
			selectedPerson = &it->second;

			getline(inputFile, line1);
			getline(inputFile, line2);
			getline(inputFile, line3);
			getline(inputFile, line4);

			it = familyTree.find(line1 + ", " + line3 + ", " + line4);
			personToAttach = &it->second;

			if (line5 == "mother-of") {
				(*personToAttach).setParent("Mother", *selectedPerson);
			} else if (line5 == "father-of") {
				(*personToAttach).setParent("Father", *selectedPerson);
			} else {
				(*personToAttach).addChild(*selectedPerson);
			}

			getline(inputFile, line1);
			getline(inputFile, line2);
			getline(inputFile, line3);
			getline(inputFile, line4);
			getline(inputFile, line5);
		}
    }
 
    inputFile.close();
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

//Stage 2 - Create the Relative that needs to be added to the tree
Person createRelative(string type) {
	string firstName, middleName, lastName;
	string birthDate, deathDate, gender;
	Person relative;

	firstName = lastName = birthDate = "";

	cout << endl << "-------------------------------------------------------------------------------" << endl;
	cout << endl << "                      Stage 2 - Creating " + type  << endl;
	cout << endl << "-------------------------------------------------------------------------------" << endl;

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

	if (type == "Mother")
		gender = "M";
	else if (type == "Father")
		gender = "F";
	else {
		cout << "Gender: ";
		getline(cin, gender);
	}

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

//Stage 3 - Establish any interconnections in the tree based on relationships
void connectRelative(map<string,Person>& familyTree, string type, Person &child, Person &parent) {

	cout << endl << "--------------------------------------------------------------------------------" << endl;
	cout << endl << "                      Stage 3 - Connecting " + type  << endl;
	cout << endl << "--------------------------------------------------------------------------------" << endl;

	//Reset type to be Mother or Father so that we may reuse the code below
	//This is true because adding a child is really just the opposite of adding
	//a parent.  A child still needs to have a parent set and needs to be added
	// to the Parent's child vector in both cases.

	if (type == "Child" && parent.getGender() == "M")
		type = "Father";
	else if (type == "Child" && parent.getGender() == "F")
		type = "Mother";

	if (!hasParent(type, child) && type != "Child") {
		child.setParent(type, parent);
		parent.addChild(child);
		cout << endl << "The following steps were completed:" << endl;
		cout << endl << "   * Person " + parent.getFirstName() + " " + parent.getLastName() + " was added as the " + type 
			+ " of " + child.getFirstName() + " " + child.getLastName() << endl;
		cout << "   * Person " + child.getFirstName() + " " + child.getLastName() + " was added as the child of " 
			+ parent.getFirstName() + " " + parent.getLastName() << endl; 
	}

}

//Stage 4 - Actually add the person to the tree now that all relationships are established
void addRelative(map<string,Person>& familyTree, string type, Person &currentPerson) {
	string firstName, lastName, birthDate;
	
	if (type != "File") {
		cout << endl << "--------------------------------------------------------------------------------" << endl;
		cout << endl << "                      Stage 4 - Adding " + type  << endl;
		cout << endl << "--------------------------------------------------------------------------------" << endl;
	}

	firstName = currentPerson.getFirstName();
	lastName  = currentPerson.getLastName();
	birthDate = currentPerson.getBirthDate();
	familyTree[firstName + ", " + lastName + ", " + birthDate] = currentPerson;

	if (type != "File")
		cout << endl << "   * " + currentPerson.getFirstName() + " " + currentPerson.getLastName() <<
			" was added to the Family Tree." << endl;
}

//Method for returning if a person exists in the family tree or not
bool isPersonFound(string selectedPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it) {
	it = familyTree.find(selectedPerson);
	if (it == familyTree.end()) 	
		return false;
	else 
		return true;
}

//Method for returning if a person has a parent (Mother or Father based on type variable) or not.
bool hasParent(string type, Person& currentPerson) {
	if (currentPerson.getParent(type) != NULL) 
		return true;
	else 
		return false;
}

void listImmediateFamily(Person& currentPerson) {
	vector<Person*> children;

	cout << endl << "The following people are parents of " + currentPerson.getFirstName() + " " 
		+ currentPerson.getMiddleName() + " " + currentPerson.getLastName() + ":" << endl;
	cout << "   * Mother - " + (*currentPerson.getParent("Mother")).getFirstName() + " " 
		+ (*currentPerson.getParent("Mother")).getMiddleName() + " " + (*currentPerson.getParent("Mother")).getLastName() << endl;
	cout << "   * Father - " + (*currentPerson.getParent("Father")).getFirstName() + " " 
		+ (*currentPerson.getParent("Father")).getMiddleName() + " " + (*currentPerson.getParent("Father")).getLastName() << endl;

	cout << endl << "The following people are children of " + currentPerson.getFirstName() + " " 
		+ currentPerson.getMiddleName() + " " + currentPerson.getLastName() + ":" << endl;

	for (Person* x : currentPerson.getChildren()) {
		cout << "   * Child - " + (*x).getFirstName() + " " + (*x).getMiddleName() + " " + (*x).getLastName() << endl;
	}

}

void getNumOfAllChildren(Person& currentPerson, int &numChildren, int &numGrandchildren, int &numGreatGrandChildren) {
	numChildren = currentPerson.getNumChildren();

	for (Person *x : currentPerson.getChildren()) {
		numGrandchildren += (*x).getNumChildren();
		for (Person *y : (*x).getChildren()) {
			numGreatGrandChildren += (*y).getNumChildren();
		}
	}

	cout << endl << "The following are the numbers per type of children for " + currentPerson.getFirstName() + " " 
		+ currentPerson.getMiddleName() + " " + currentPerson.getLastName() + ":" << endl;
	cout << endl <<"   * Number of Children: " << numChildren;
	cout << endl <<"   * Number of Grandchildren: " << numGrandchildren;
	cout << endl <<"   * Number of Great Grandchildren: " << numGreatGrandChildren;

}