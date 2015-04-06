#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string> 
#include "Person.h"
#include <vector>
using namespace std;

//Author: Jacob R. Holcomb
//Date: 4-06-2015
//Assignment: Project 2
//Description: Maintains a Family Tree of People

int main(int argCount, char *argValues[]) {
Person currentPerson, mother, father;
currentPerson = Person();
mother = Person();
father = Person();

mother.setFirstName("Jenny");
father.setFirstName("Kyle");

currentPerson.setMother(mother);
currentPerson.setFather(father);

cout << currentPerson.getMother().getFirstName() << endl;
cout << currentPerson.getFather().getFirstName() << endl;
}