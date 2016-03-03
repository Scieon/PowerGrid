#include "Uranium.h"

//Destructor
Uranium::~Uranium() {
}

//Default Constructor
Uranium::Uranium() {

	this->setColor("Red"); //Default color
	this->setQuantity(0); //Default amount
	cost = 14; //Arbitrary Cost
}

//Parametrized Constructor
Uranium::Uranium(int quantity) : cost(12) {
	this->setColor("Red");
	setQuantity(quantity);
}

//Accessor for cost of single Uranium resource
int Uranium::getCost() const{
	return cost;
}

//Mutator for cost of single Uranium Resource
void Uranium::setCost(int cost) {
	this->cost = cost;
}

//Return type of resource
string Uranium::getType() const {
	return type;
}