#include <iostream>
#include "Player.h" 
#include "House.h" 
#include "Resource.h"
#include "Powerplant.h"
#include "Board.h"


using namespace std;

//Static Counter 
int Player::number_of_players = 0;

Player::Player()
{
	powerplants = new vector<Powerplant>();
	powerplants->clear();
}

//Constructor initializes for Players 
Player::Player(string color) {
	elektro = 50;
	this->color = color;

	resources = new ResourceManager();
	houseManager = new HouseManager();
	++number_of_players;
	playerNumber = number_of_players;
	powerplants = new vector<Powerplant>();

	powerplants->clear(); //clears default initialization
}

Player::Player(string color, int elektro, HouseManager * hm, vector<Powerplant> * pp, ResourceManager * rm)
{
	this->color = color;
	this->elektro = elektro;
	this->houseManager = hm;
	this->powerplants = pp;
	this->resources = rm;
}

//Destructor
Player::~Player() {

}

//Mutator function to set the color of the player/house
void Player::setColor(string color) {
	this->color = color;
}

//Setter for amount of elektro
void Player::setElektro(int amount) {
	this->elektro = amount;
}

void Player::subtractMoney(int elektros) {
	this->elektro -= elektros;
}

//Accessor function to get the color of the player
string Player::getColor() {
	return color;
}

//Mutator function player gets paid according to number of cities they supply
void Player::getPaid(int houses) {

	int paymentTable[21] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };
	this->setElektro(this->elektro + paymentTable[houses]);
	
	cout << "Player " << getColor() << " has been paid " << paymentTable[houses] << " elektros." << endl;

}

//Accessor function returning number houses a lpayer owns
int Player::getNumberHouses() {
	return houseManager->getHouseCount();
}
//Accessor function of elektro
int Player::getElektro() {
	return elektro;
}

//Accessor function of HouseManager to get collection of house
HouseManager* Player::getHouseManager() {
	return houseManager;
}

//returns the powerplant vector
vector<Powerplant>* Player::getPowerplantsVector() {
	return powerplants;
}

//returns the resource quantity
int Player::getResource(string type) {

	return resources->getResourceQuantity(type);
}

//Adds a powerplant to a players possessions
void Player::addPlant(Powerplant * p1) {

	if (this->isPowerplantsFull()) {
		return;
	}
	else {
		powerplants->push_back(*p1);
		numberOfPlants++;
		subtractMoney(p1->getBid());
	}
}

//validates the resources that we purchased
bool Player::validateResourcePurchase(int cost, int quantity, string type) {

	if (this->getElektro() < cost) {
		cout << "Not enough elektros to purchase resources!" << endl;
		return false;
	}


	if (type == "Coal") {
		bool condition1 = getResourceStorage("Coal") < (getResource("Coal") + quantity); //Cannot buy more resources than total storage
		bool condition2 = getTotalStorage() < (getResource("Coal") + getResource("Oil") + quantity); //Cannot buy specific quantity that exceeds that types storage

		if (condition1 || condition2) {
			cout << "Cannot store that many Coal!" << endl;
			return false;
		}
		//cout << "Validated" << endl;
	}

	if (type == "Oil") {
		bool condition1 = getResourceStorage("Oil") < (getResource("Oil") + quantity);
		bool condition2 = getTotalStorage() < (getResource("Coal") + getResource("Oil") + quantity);

		if (condition1 || condition2) {
			cout << "Cannot store that many Oil!" << endl;
			return false;
		}
		//cout << "Validated" << endl;
	}

	if (type == "Garbage") {
		if (getResourceStorage("Garbage") < getResource("Garbage") + quantity) {
			cout << "Cannot store that many Garbage!" << endl;
			return false;
		}
		//cout << "Validated" << endl;
	}

	if (type == "Uranium") {
		if (getResourceStorage("Uranium") < getResource("Uranium") + quantity) {
			cout << "Cannot store that many Uranium!" << endl;
			return false;
		}
		//cout << "Validated" << endl;
	}

	//At this point all validation have passed we can let user buy it.
	this->addResource(type, quantity);
	this->subtractMoney(cost);
	return true;

}

//Returns total amount of resources stored across all possible power plants
int Player::getTotalStorage() {
	int storage = 0;
	for (Powerplant pp : *powerplants) {
		storage += pp.getStorage();
	}
	return storage;
}

//Returns total amount of specific resource that can be stored
int Player::getResourceStorage(string resource) {
	int storage = 0;

	for (Powerplant pp : *powerplants) {
		if (pp.getType() == resource) {
			storage += pp.getStorage();
		}

		if (pp.getType() == "Hybrid" && (resource == "Coal" || resource == "Oil")) {
			storage += pp.getStorage();
		}

	}
	return storage;
}

//This function adds a selected amount of a resource into a players resource possessions
void Player::addResource(string type, int quantity) {

	resources->addResourceQuantity(type, quantity);
	return;

	cout << "Error in adding resource quantity" << endl;
}


//Hepler function that displays the info of all a players powerplants
void Player::showPlants() {

	for (Powerplant pp : *powerplants) {
		pp.showPlantInfo();
	}
}

//Displays all plants that can be powered, i.e., they have enough resources on them
void Player::showPlantsToPower() {
	//int i = 1;
	for (Powerplant pp : *powerplants) {

		//Checking if player has enough resources to power given plant

		if (this->getResource(pp.getType()) >= pp.getResourceReq()) {
			cout << "Powerplant " << pp.getBid() << " can power " << pp.getCitiesPowered() << " cities at a cost of " << pp.getResourceReq() << " units of " << pp.getType() << endl;

		}

		if (pp.getType() == "Hybrid") {

			if (getResource("Coal") >= pp.getResourceReq() || getResource("Oil") >= pp.getResourceReq()) {
				cout << "Powerplant " << pp.getBid() << " can power " << pp.getCitiesPowered() << " cities at a cost of " << pp.getResourceReq() << " units of either Coal or Oil." << endl;
			}
		}

		if (pp.getType() == "Eco")
			cout << "Powerplant " << pp.getBid() << " can power " << pp.getCitiesPowered() << " cities at not cost." << endl;

		cout << endl;
	}
}

//Checks if player owns certain powerplant
bool Player::validatePlantPossession(int plantNumber) {
	for (Powerplant pp : *powerplants) {
		if (pp.getBid() == plantNumber) {
			return true;
		}
	}
	return false;
}
void Player::powerCity(int plantNumber) {
	PowerplantManager * pp = new PowerplantManager();

	int index = pp->findPowerplant(plantNumber);
	string type = pp->getPlantType(index);
	int amount = pp->getPlantReq(index);
	if (type == "Hybrid") {

		string choice;
		if (getResource("Coal") >= amount && getResource("Oil") >= amount) {

			while (choice != "Oil" && choice != "oil" && choice != "Coal" && choice != "coal") {
				cout << "Would you like to remove " << amount << " units of Coal or Oil? ";
				cin >> choice;

				if (choice == "Oil" || choice == "oil") {
					this->resources->remove("Oil", amount);
				}

				if (choice == "Coal" || choice == "coal") {
					this->resources->remove("Coal", amount);
				}
				cout << endl;
			}
		}

		else if (getResource("Coal") >= amount) {
			choice = "Coal";
			this->resources->remove(choice, amount);
		}

		else if (getResource("Oil") >= amount) {
			choice = "Oil";
			this->resources->remove(choice, amount);
		}

		cout << "Removed(hybrid) " << amount << " units of " << choice << endl;
		delete pp;
		return;
	}

	if (type == "Eco") {
		delete pp;
		return;
	}


	this->resources->remove(type, amount);

	cout << "Removed " << amount << " units of " << type << endl;

	delete pp; //Freeing heap

}

//Display user possessions and characteristics
void Player::showInfo() {

	cout << "Player " << color << "'s resources:" << endl;
	cout << "Elektro:" << this->getElektro() << endl;
	cout << "Resource Coal: " << this->getResource("Coal") << endl;
	cout << "Resource Oil: " << this->getResource("Oil") << endl;
	cout << "Resource Garbage: " << this->getResource("Garbage") << endl;
	cout << "Resource Uranium: " << this->getResource("Uranium") << endl << endl;
}


//Checks if the player has 3 power plants
bool Player::isPowerplantsFull() {
	return (powerplants->size() == 3);
}

//For simple use. Should do overload the equal operator instead
bool Player::comparePlayer(Player* pp) {
	if (pp->getColor() == this->color) {
		return true;
	}
	else
	{
		return false;
	}
}

//Need to see which player has the highest powerplant number and iterate through their maximum of 3 powerplants possession
int Player::getHighestMinBid() {
	int highest = 0; //By default
	for (Powerplant pp : *powerplants) {

		if (highest < pp.getBid()) {
			highest = pp.getBid();
		}
	}

	return highest;
}

//Check if the player has enough money to buy
bool Player::hasEnoughtElektroFor(int amount) {

	int temp = elektro;
	if ((temp - amount) >= 0) {
		return true;
	}
	return false;
}



//Returns number of cities that players powerplant cant supply power to
int Player::getPowerplantPower(int min_bid) {

	PowerplantManager * pp = new PowerplantManager();

	int index = pp->findPowerplant(min_bid);
	return pp->getCitiesPowered(index);

	delete pp; //Freeing heap
}