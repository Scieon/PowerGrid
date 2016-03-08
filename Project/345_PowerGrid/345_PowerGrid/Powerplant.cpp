#include <iostream>
#include "Powerplant.h"

using namespace std;

//Default Constructor
Powerplant::Powerplant() {

}

//Destructor
Powerplant::~Powerplant() {

}

//Paramterized Constructor

Powerplant::Powerplant(int min_bid, string resource_type, int resources_required, int num_cities_powered) {

	this->min_bid = min_bid; //The initial cost of purchasing the powerplant
	this->resource_type = resource_type; //The required resource type to power the plant
	this->resources_required = resources_required; //The number of resources required to supply power to the plant
	this->num_cities_powered = num_cities_powered; //The number of cities that the powerplant can supply power to
	this->storage = 2 * resources_required; //The number of resources that can be stored in the plant
}

//Accessor function to get the minimum current bid on the power plant
int Powerplant::getBid() {
	return min_bid;
}


//Mutator function to set a new bid
void Powerplant::setBid(int bid) {
	min_bid = bid;
}

//Accessor function that returns the resource type of the plant
string Powerplant::getType() {
	return resource_type;
}

//Return the number of cities that the plant can supply power to
int Powerplant::getCitiesPowered() {
	return num_cities_powered;
}

//Return number of resources required to supply power to the plant
int Powerplant::getResourceReq() {
	return resources_required;
}

//Returns number of resources that can be stored on the plant
int Powerplant::getStorage() {
	return storage;
}

//Fucntion that displays a single power plants characteristics
void Powerplant::showPlantInfo() {
	string type = resource_type;

	if (resource_type == "Hybrid")
		type = "Coal or Oil";
	cout << resource_type << " Power Plant" << endl
		<< "-----------------------------------------" << endl
		<< "Minimum Price: " << min_bid << " elektros" << endl
		<< "Operation Cost: " << resources_required << " units of " << type << endl
		<< "Number of powered cities:  " << num_cities_powered << endl << endl;
}

//Used to sort market.
bool Powerplant::operator<(const Powerplant & pp)
{
	return min_bid < pp.min_bid;
}

