#include <iostream>
#include "Player.h" 
#include "House.h" 
#include "Resource.h"

using namespace std;


//Constructor initializes for Players 
Player::Player(string color, int turnOrder){
	money = 50;
	this->turnOrder = turnOrder;
	this->color = color;
	resource = new Resource();
	powerPlantManager = new PowerPlantManager();
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

//Accessor function of Resources such as oil, uranium, garbage or coal
Resource* Player::getResources(){
	return resource;
}

//Accessor function of HouseManager to get collection of house
HouseManager* Player::getHouseManager(){
	return houseManager;
}

//Accessor function of PowerPlantManager to get collection of PowerPlants
PowerPlantManager* Player::getPowerPlantManager(){
	return powerPlantManager;
}










