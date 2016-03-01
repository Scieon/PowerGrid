#include "Oil.h"

//Destructor
Oil::~Oil() {

}

//Default Constructor
Oil::Oil() {

	this->setColor("Black"); //Default color 
	this->setQuantity(0); //Default amount
	cost = 3; //Arbitrary cost
}


//Parameterized Constructor
Oil::Oil(int quantity) : cost(5) {
	this->setColor("Black");
	setQuantity(quantity);
}

//Mutator for cost of single oil resource
void Oil::setCost(int cost)  {
	this->cost = cost;
}

//Accessor for cost of single oil resource
int Oil::getCost() const {
	return cost;
}

//Return type of resource
string Oil::getType() const {
	return type;
}