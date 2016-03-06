#include <iostream>
#include "Player.h" 
#include "House.h" 
#include "Resource.h"
#include "Powerplant.h"
#include "Verify.h"

using namespace std;


//Constructor initializes for Players 
Player::Player(string color, int turnOrder){
	money = 50;
	this->turnOrder = turnOrder;
	this->color = color;
	
	resource[0] = new Coal(1, 0);
	resource[1] = new Oil(3,0);
	resource[2] = new Garbage(8,0);
	resource[3] = new Uranium(12,0);
	
	houseManager = new HouseManager();
}

//Destructor
Player::~Player(){

}

//Mutator function to set who goes first
void Player::setTurnOrder(int turnOrder){
	this->turnOrder = turnOrder;
}

//Mutator function to set the color of the player/house
void Player::setColor(string color){
	this->color = color;
}

//Setter for amount of elektro
void Player::setMoney(int amount){
	this->money = amount;
}

//Accessor function to get the order of who is going first 
int Player::getTurnOrder(){
	return turnOrder;
}

//Accessor function to get the color of the player
string Player::getColor(){
	return color;
}

//Accessor function of money
int Player::getMoney(){
	return money;
}

//Accessor function of HouseManager to get collection of house
HouseManager* Player::getHouseManager(){
	return houseManager;
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







