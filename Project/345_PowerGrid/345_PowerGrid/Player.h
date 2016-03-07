#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "HouseManager.h"
#include "Resource.h"
#include "PowerPlantManager.h"
#include "Powerplant.h"
#include "ResourceManager.h"




using namespace std;

class Player{
public:
	Player(string);
	Player(string color, int electro, HouseManager *hm, vector<Powerplant> *pp, ResourceManager *rm);
	Player();
	~Player();

	//Mutator functions
	void setColor(string color);
	void setElektro(int elektros);
	void subtractMoney(int elektros);

	//Accessor functions
	string getColor();
	int getElektro();
	HouseManager* getHouseManager();
	vector<Powerplant>* getPowerplantsVector();
	
	//Powerplants
	void showPlants(); //Power Plant methods added by Anhkhoi, feel free to modify
	void showInfo();
	bool isPowerplantsFull(); //checks if powerplant vector is full
	void addPlant(Powerplant * p1); //incomplete "p2->addPlant(oil3);"

	//Resources
	void addResource(string type, int quantity); //Don't care about cost 
	int getResource(string type); //Return resource quantity
	void validateResourcePurchase(int cost, int quantity, string type);
	int getTotalStorage(); //Returns total amount of resources stored across all possible power plants
	int getResourceStorage(string resource); //Returns total amount of specific resource that can be stored


private:

	static int number_of_players;
	int playerNumber;
	int elektro;
	string color;
	HouseManager* houseManager;
	ResourceManager * resources;
	vector<Powerplant> * powerplants; //Players can have up to 3 power plants stored in an array of powerplants
	int numberOfPlants = 0;  //Counter for each player
	
};

#endif //PLAYER_H
