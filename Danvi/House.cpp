#include <iostream>
#include <string>
#include "House.h";

using namespace std;

//Default constructor
House::House(){
	location = "somewhere"; //arbitrary location
}

//Destructor 
House::~House(){

}

//Constructor initializes house location 
House::House(string location){
	this->location = location;
}

//Mutator function to set location of house
void House::setLocation(string location){
	this->location = location;
}

//Acccessor function to get location of house
string House::getLocation(){
	return location;
}



