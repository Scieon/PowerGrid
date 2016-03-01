#include "Coal.h"


//Destructor
Coal::~Coal() {

}

//Default Constructor
Coal::Coal() {
	cost = 1; //Arbitrary Value
	this->setColor("Brown");
	this->setQuantity(0);
}

//Parameterized Constructor for the quantity
Coal::Coal(int quantity) : cost(1) {
	this->setColor("Brown");
	setQuantity(quantity);
}

//Accessor Function for the cost of a single Coal resource
int Coal::getCost() const {
	return cost;
}

//Mutator function to set the cost of a single Coal resource
void Coal::setCost(int cost) {
	this->cost = cost;
}

//Accessor function returning the type of resource
string Coal::getType() const {
	return type;
}