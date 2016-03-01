#include "Garbage.h"

//Destructor
Garbage::~Garbage() {

}

//Default Constructor
Garbage::Garbage() {
	cost = 7; //Arbitrary Value
	this->setColor("Yellow"); //Defautl Color
	this->setQuantity(0); //Default amount
}

//Parameterized Constructor
Garbage::Garbage(int quantity) : cost(8) {
	this->setColor("Yellow");
	setQuantity(quantity);
}

//Mutator for cost of single garbage resource
void Garbage :: setCost(int cost) {
	this->cost = cost;
}

//Accessor for cost of single garbage resource
int Garbage::getCost() const {
	return cost;
}

//Returns type of resource
string Garbage::getType() const {
	return type;
}

