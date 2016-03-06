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
	Player(string, int);
	Player();
	~Player();
	void setTurnOrder(int);
	void setColor(string color);
	void setMoney(int elektros);
	void subtractMoney(int elektros);
	int getTurnOrder();
	string getColor();
	int getMoney();
   
	void showInfo();
	HouseManager* getHouseManager();

	//Power Plant methods added by Anhkhoi, feel free to modify
	void showPlants();

	void addPlant(Powerplant * p1); //incomplete "p2->addPlant(oil3);"
	void addResource(string type, int quantity); //Don't care about cost 
	int getResource(string type); //Return resource quantity


private:

	static int number_of_players;
	int playerNumber;
	int money;
	int turnOrder;
	string color;
	HouseManager* houseManager;
	//Resource * resources[4]; 
	ResourceManager * resources;
	Powerplant * powerplants[3]; //Players can have up to 3 power plants stored in an array of powerplants
	int numberOfPlants = 0;  //Counter for each player
	
};

#endif //PLAYER_H
