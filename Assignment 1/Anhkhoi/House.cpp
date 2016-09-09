#include "House.h"


//Default Constructor initializing everything to default values
House::House() : color(""), number_of_houses(0)  {

}

//Parameterized constructor taking in a color
House::House(string color) : color(color), number_of_houses(0) {

}

//Muator function for setting color
void House::setColor(string color) {
	this->color = color;
}

//Accessor function returning color of a players house
string House::getColor() const {
	return color;
}

//Accessor function returning the total number of houses a player possess
int House::getHouses() const {
	return number_of_houses;
}

//Mutator method for changing number of houses where house is the new number of houses to be added to existing number of houses.
void House::setHouses(int house) { 
	this->number_of_houses += house; 
}

