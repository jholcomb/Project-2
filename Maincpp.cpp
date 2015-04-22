//------------------------------------------Imports-------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string> 
#include "Person.h"
#include <fstream>
#include <map>
using namespace std;

//-------------------------------------Project Information------------------------------------------------

//Author: Jacob R. Holcomb
//Date: 4-06-2015
//Assignment: Project 2
//Description: Maintains a Family Tree of People

//------------------------Prototypes for all methods in this program---------------------------------------

//Initializes Family Tree based on a text file, provided with the project
void initializeTree(map<string,Person>& familyTree, map<string, Person>::iterator it);

//Prints the program's headder information
void printIntro();

//Prints whether a person is found in the Family Tree or not.
bool isPersonFound(string selectedPerson, map<string,Person>& familyTree, map<string, Person>::iterator& it);

//Adds a relative to the Family Tree, which is represented as a Map
void addRelative(map<string,Person>& familyTree, string type, Person &currentPerson);

//Creates a new Person to be added to the Family Tree
Person createRelative(string type);

//Connects all relationships between the new person and the existing members of the tree
void connectRelative(map<string,Person>& familyTree, string type, Person &currentPerson, Person &personToAttach, map<string, Person>::iterator it);

//Returns true if a child has a parent of either type = Father or type = Mother
bool hasParent(string type, Person& currentPerson);

//Lists all immediate family members of the current Person
void listImmediateFamily(Person& currentPerson);

//Prints the number of children, grandchildren, and great grandchildren
void getNumOfAllChildren(Person& currentPerson, int &numChildren, int &numGrandchildren, int &numGreatGrandChildren);

//Provides printing methods for listing different relations of the Person
void printListHeader(string relationType, Person &currentPerson);
void printParentList(Person &currentPerson);
void printChildrenList(Person &currentPerson);

//-------------------------------------------Main Program---------------------------------------------------

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

	//Attempt to load all entries from the provided file.
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
		if (selectedPerson == "Q") {
			cout << endl << "Family Tree Manager Shutting Down..." << endl;
			break;
		}

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

					if ((*currentPerson).getParent(type) == NULL) 
						connectRelative(familyTree, type, *currentPerson, createRelative(type), it);
					else 
						cout << endl << (*currentPerson).getFirstName() + " " + (*currentPerson).getLastName() + " already has a " + type << endl;
				} else if (currentCommand == "C") {
					type = "Child";
					connectRelative(familyTree, type, createRelative(type), *currentPerson, it);
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

//-------------------------------------------External Methods---------------------------------------------------

//Initializes Tree based on the given structure of a text file
//This structure follows the scheme setup by Dr. Heuring.
//The intialization is completed in two steps:
//Step 1 - Load all the people into the tree until ready for connections.
//Step 2 - Connect all of the relationships of the tree based on the file.

void initializeTree(map<string,Person>& familyTree, map<string, Person>::iterator it) {
	ifstream inputFile("truman.txt");
    string junk, line1, line2, line3, line4, line5, line6;
	string type = "File";
	Person currentPerson, *selectedPerson, *personToAttach;
	bool readyForConnections = false;

	//Remove the 27 at the top of the tect file
	getline(inputFile, junk);
	
	//Step 1 (As described above)
	if (inputFile.is_open()) {
		while(!inputFile.eof()) {
			if (readyForConnections == false) {
				getline(inputFile, line1);
				getline(inputFile, line2);
				getline(inputFile, line3);
				getline(inputFile, line4);
				getline(inputFile, line5);

				if (line5 == "mother-of" || line5 == "father-of" || line5 == "child-of") {
					readyForConnections = true;
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

			//Step 2 (As described above)
			} else if (readyForConnections == true) {
				it = familyTree.find(line1 + ", " + line3 + ", " + line4);
				selectedPerson = &it->second;

				getline(inputFile, line1);
				getline(inputFile, line2);
				getline(inputFile, line3);
				getline(inputFile, line4);

				it = familyTree.find(line1 + ", " + line3 + ", " + line4);
				personToAttach = &it->second;

				if (line5 == "mother-of") 
					(*personToAttach).setParent("Mother", *selectedPerson);
				else if (line5 == "father-of") 
					(*personToAttach).setParent("Father", *selectedPerson);
				else 
					(*personToAttach).addChild(*selectedPerson);
			
				getline(inputFile, line1);
				getline(inputFile, line2);
				getline(inputFile, line3);
				getline(inputFile, line4);
				getline(inputFile, line5);
			}
		}
		inputFile.close();
	} else {
		//The default tree could be more complex but this was just included
		//to handle the case where the file does not exist.  It is meant to
		//provide enough information to get the program to still run correctly.
		type = "Child";
		cout << endl << "File did not open, please create the first person for the Family Tree:" << endl;

		//Create an single node without any parents
		currentPerson = createRelative(type);
		//Adds the person to the Family Tree
		addRelative(familyTree, type, currentPerson);
	}
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

	//Require First Name
	while (firstName == "") {
		cout << endl << "First Name: ";
		getline(cin, firstName);
	}

	cout << "Middle Name: ";
	getline(cin, middleName);

	//Require Last Name
	while (lastName == "") {
		cout << "Last Name: ";
		getline(cin, lastName);
	}

	//Require Birthdate
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
		cout << "Gender:";
		getline(cin, gender);
	}

	//Setup the relative to be added based on input
	relative.setFirstName(firstName);
	relative.setMiddleName(middleName);
	relative.setLastName(lastName);
	relative.setBirthDate(birthDate);
	relative.setDeathDate(deathDate);
	relative.setGender(gender);

	//Output the steps that occured during this Stage
	cout << endl << "The following steps were completed:" << endl;
	cout << endl << "   * Person " + relative.getFirstName() + " " + relative.getLastName() + " was created." << endl;
	return relative;
}

//Stage 3 - Actually add the person to the tree 
void addRelative(map<string,Person>& familyTree, string type, Person &currentPerson) {
	string firstName, lastName, birthDate;
	
	//If we are reading from a file, turn all verbose off in this Stage
	if (type != "File") {
		cout << endl << "--------------------------------------------------------------------------------" << endl;
		cout << endl << "                      Stage 3 - Adding " + type  << endl;
		cout << endl << "--------------------------------------------------------------------------------" << endl;
	}

	firstName = currentPerson.getFirstName();
	lastName  = currentPerson.getLastName();
	birthDate = currentPerson.getBirthDate();
	familyTree[firstName + ", " + lastName + ", " + birthDate] = currentPerson;

	if (type != "File")
		//Output for the steps that occured during this Stage
		cout << endl << "   * " + currentPerson.getFirstName() + " " + currentPerson.getLastName() <<
			" was added to the Family Tree." << endl;
}

//Stage 4 - Establish any interconnections in the tree based on relationships
void connectRelative(map<string,Person>& familyTree, string type, Person &child, Person &parent, map<string, Person>::iterator it) {
	string originalType = type;
	Person *parentPtr,*childPtr;

	parentPtr = NULL;
	childPtr  = NULL;

	//Reset type to be Mother or Father so that we may reuse the code below
	//This is true because adding a child is really just the opposite of adding
	//a parent.  A child still needs to have a parent set and needs to be added
	// to the Parent's child vector in both cases.

	if (type == "Child" && parent.getGender() == "M")
		type = "Father";
	else if (type == "Child" && parent.getGender() == "F")
		type = "Mother";

	if (!hasParent(type, child)) {
		//We need to add the person before making the connections.
		//If this was done in the reverse order, we would point out of
		//scope and get null objects.
		if (originalType != "Child") {
			addRelative(familyTree, originalType, parent);
		} else 
			addRelative(familyTree, originalType, child);
		
		it = familyTree.find(parent.getFirstName() + ", " + parent.getLastName() + ", " + parent.getBirthDate());
		parentPtr = &it->second;

		it = familyTree.find(child.getFirstName() + ", " + child.getLastName() + ", " + child.getBirthDate());
		childPtr = &it->second;

		//If pointers to the Family Tree entries are not used,
		//the People in ther tree will need re-added.
		(*childPtr).setParent(type, *parentPtr);
		(*parentPtr).addChild(*childPtr);

		cout << endl << "--------------------------------------------------------------------------------" << endl;
		cout << endl << "                      Stage 4 - Connecting " + originalType  << endl;
		cout << endl << "--------------------------------------------------------------------------------" << endl;

		//Output for the steps that occurred during this Stage
		cout << endl << "The following steps were completed:" << endl;

		cout << endl << "   * Person " + parent.getFirstName() + " " + parent.getLastName() + " was added as the " + type 
			+ " of " + child.getFirstName() + " " + child.getLastName() << endl;

		cout << "   * Person " + child.getFirstName() + " " + child.getLastName() + " was added as the child of " 
			+ parent.getFirstName() + " " + parent.getLastName() << endl; 	
	}
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

//A simple method for listing all of the immediate family members of said person
void listImmediateFamily(Person& currentPerson) {
	vector<Person*> children;
	//Prints the Mother and Father of the person (If they exist)
	printListHeader("parents", currentPerson);
	printParentList(currentPerson);

	//Prints the Children of the person (If they exist)
	printListHeader("children", currentPerson);
	printChildrenList(currentPerson);
}

//Simple method for printing out the number of children, grandchildren and great grandchildren a person has
void getNumOfAllChildren(Person& currentPerson, int &numChildren, int &numGrandchildren, int &numGreatGrandChildren) {
	numChildren = currentPerson.getNumChildren();

	//Note this method does not print anything past great grandchildren
	//Thus, great great grandchildren and below are not included.
	//This was based on the requirements for the project.
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

void printListHeader(string relationType, Person &currentPerson) {
	cout << endl << "The following people are " + relationType+ " of " + currentPerson.getFirstName() + " " 
		+ currentPerson.getMiddleName() + " " + currentPerson.getLastName() + ":" << endl;
}

void printParentList(Person &currentPerson) {
	//If they have a mother/father, print her/his entire name out
	if (hasParent("Mother", currentPerson))
		cout << "   * Mother - " + (*currentPerson.getParent("Mother")).getFirstName() + " " 
			+ (*currentPerson.getParent("Mother")).getMiddleName() + " " + (*currentPerson.getParent("Mother")).getLastName() << endl;
	//If they have a father, print his entire name out
	if (hasParent("Father", currentPerson))
		cout << "   * Father - " + (*currentPerson.getParent("Father")).getFirstName() + " " 
			+ (*currentPerson.getParent("Father")).getMiddleName() + " " + (*currentPerson.getParent("Father")).getLastName() << endl;
}

void printChildrenList(Person &currentPerson) {
	//For every child in the person's child vector, print the child's entire name
	for (Person* x : currentPerson.getChildren()) 
		cout << "   * Child - " + (*x).getFirstName() + " " + (*x).getMiddleName() + " " + (*x).getLastName() << endl;
}