#include <iostream>
#include "Player.h" 
#include "House.h" 
#include "Resource.h"
#include "Powerplant.h"


using namespace std;

//Static Counter 
int Player::number_of_players = 0;

Player::Player() {}

//Constructor initializes for Players 
Player::Player(string color){
	money = 50;
	this->color = color;
	
	resources = new ResourceManager();
	houseManager = new HouseManager();
	++number_of_players;
	playerNumber = number_of_players;
}

//Destructor
Player::~Player(){

}

//Mutator function to set the color of the player/house
void Player::setColor(string color){
	this->color = color;
}

//Setter for amount of elektro
void Player::setMoney(int amount){
	this->money = amount;
}

void Player::subtractMoney(int elektros) {
	this->money -= elektros;
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

int Player::getResource(string type) {
	if (type == "Coal")
		return resources->getResourceQuantity(type);

	if (type == "Oil")
		return resources->getResourceQuantity(type);

	if (type == "Garbage")
		return resources->getResourceQuantity(type);

	if (type == "Uranium")
		return resources->getResourceQuantity(type);
}

//Adds a powerplant to a players possessions
void Player::addPlant(Powerplant * p1) {

	//Place in slot 1
	if (powerplants[0]->getBid() == -1) {
		powerplants[0] = p1; //This is a shallow copy since we do not want to create a second powerplant as if we were creating a deep copy
		numberOfPlants++;
		return;
	}

	//Place in slot 2
	if (powerplants[1]->getBid() == -1) {
		powerplants[1] = p1; 
		numberOfPlants++;
		return;
	}

	//Place in slot 3
	if (powerplants[2]->getBid() == -1) {
		powerplants[2] = p1;
		numberOfPlants++;
		return;
	}

	cout << "Player already has 3 power plants" << endl;
	system("pause");
}

//This function adds a selected amount of a resource into a players resource possessions
void Player::addResource(string type, int quantity) {
	if (type == "Coal")
		resources->addResourceQuantity("Coal",quantity);

	if (type == "Oil")
		resources->addResourceQuantity("Oil",quantity);

	if (type == "Garbage")
		resources->addResourceQuantity("Garbage",quantity);

	if (type == "Uranium")
		resources->addResourceQuantity("Uranium", quantity);

	else
		cout << "Error in adding resource quantity" << endl;
}



//Display user possessions and characteristics
void Player::showInfo(){


	cout << "Here is the player " << playerNumber <<" resources:" << endl;
	cout << "P" << playerNumber <<" Money:" << this->getMoney() << endl;
	cout << "P" << playerNumber <<" Resource Uranium: " << this->getResource("Uranium") << endl;
	cout << "P" << playerNumber <<"  Resource Garbage: " << this->getResource("Garbage") << endl;
	cout << "P" << playerNumber <<" Resource Coal: " << this->getResource("Coal") << endl;
	cout << "P" << playerNumber <<" Resource Oil: " << this->getResource("Oil") << endl << endl;


}







