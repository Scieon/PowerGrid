#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "HouseManager.h"
#include "Resource.h"
#include "PowerPlantManager.h"
using namespace std;

class Player{
public:
	Player(string, int);
	~Player();
	void setTurnOrder(int);
	void setColor(string);
	void setMoney(int);
	int getTurnOrder();
	string getColor();
	int getMoney();
    Resource *resource[4]; //Should put this private since its attribute
	HouseManager* getHouseManager();

	//Power Plant methods added by Anhkhoi, feel free to modify
	void showPlants();
	void addPlant(Powerplant p1); //incomplete "p2->addPlant(oil3);"


private:


	int money;
	int turnOrder;
	string color;
	HouseManager* houseManager;
	Powerplant * powerplants[3]; //Players can have up to 3 power plants stored in an array of powerplants
	int numberOfPlants = 0;  //Counter for each player
	
};

#endif //PLAYER_H
