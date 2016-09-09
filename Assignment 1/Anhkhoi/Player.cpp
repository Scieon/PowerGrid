#include "Player.h"
#include <string>
#include <iostream>


using namespace std;

//Static Counter
int Player::number_of_players = 0;


//Defaault Constructor initalizing elektro and number of plants
Player::Player() : elektros(50), numberOfPlants(0) {

	resources[0] = new Coal();
	resources[1] = new Oil();
	resources[2] = new Garbage();
	resources[3] = new Uranium();
	++number_of_players;
}

//Parameterized constructor assigning a color to a  player
Player::Player(string color) : elektros(50), numberOfPlants(0) {

	houses.setColor(color);
	resources[0] = new Coal();
	resources[1] = new Oil();
	resources[2] = new Garbage();
	resources[3] = new Uranium();
	++number_of_players;
}

//Destructor
Player::~Player() {
	--number_of_players;
}




//This function adds a selected amount of a resource into a players resource possessions
void Player::addResource(string type, int quantity) {
	if (type == "Coal")
		resources[0]->addQuantity(quantity);

	if (type == "Oil")
		resources[1]->addQuantity(quantity);

	if (type == "Garbage")
		resources[2]->addQuantity(quantity);

	if (type == "Uranium")
		resources[3]->addQuantity(quantity);

	else
		cout << "Error in adding resource quantity" << endl;
}

//Accessor function returning a players money
int Player::getElektros() const {
	return elektros;
}

//Mutator function setting player's money
void Player::setElektros(int elektros) {
	this->elektros = elektros;
}

//Variation of setElektros but simply adds to existing player money
void Player::addElektros(int elektros) {
	this->elektros += elektros;
}


//Adds a powerplant to a players possessions
void Player::addPlant(Powerplant p1) {

	if (powerplants[0].getBid() == -1) {
		powerplants[0] = p1; //This is a shallow copy since we do not want to create a second powerplant as if we were creating a deep copy
		numberOfPlants++;
	}

	else {
		powerplants[1] = p1;
		numberOfPlants++;
	}
}


//Hepler function that displays the info of all a players powerplants
void Player::showPlants() {

	if (powerplants[0].getBid() != -1)
		powerplants[0].showPlantInfo();

	if (powerplants[1].getBid() != -1)
		powerplants[1].showPlantInfo();

	if (powerplants[2].getBid() != -1)
		powerplants[2].showPlantInfo();

}

//Display user possessions and characteristics
void Player::showInfo() const {

	cout << "-------------------- Player " << number_of_players << ": Details" << "--------------------" << endl;
	cout << "Elektros: " << elektros << endl << "Color: " << houses.getColor() << endl;
	cout << "Number of Houses " << houses.getHouses() << endl;
	cout << "Number of Powerplants: " << numberOfPlants << endl << endl;
	cout << "Coal Quantity: " << resources[0]->getQuantity() << endl;
	cout << "Oil Quantity: " << resources[1]->getQuantity() << endl;
	cout << "Garbage Quantity: " << resources[2]->getQuantity() << endl;
	cout << "Uranium Quantity: " << resources[3]->getQuantity() << endl << endl;


}