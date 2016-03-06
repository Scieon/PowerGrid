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
        Resource *resource[4];
	HouseManager* getHouseManager();


private:
	int money;
	int turnOrder;
	string color;
	HouseManager* houseManager;
	
};

#endif //PLAYER_H
