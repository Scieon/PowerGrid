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
	void setResources(Resource);
	int getTurnOrder();
	string getColor();
	int getMoney();
	HouseManager* getHouseManager();
	Resource* getResources();
	PowerPlantManager* getPowerPlantManager();

private:
	int money;
	int turnOrder;
	string color;
	HouseManager* houseManager;
	Resource* resource;
	PowerPlantManager* powerPlantManager;
};

#endif //PLAYER_H