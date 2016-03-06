#include <iostream>
#include "Player.h" 
#include "House.h" 
#include "Resource.h"
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











