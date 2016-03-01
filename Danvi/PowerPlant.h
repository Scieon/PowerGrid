#ifndef POWERPLANT_H
#define POWERPLANT_H

#include <iostream>
#include "Resource.h"
using namespace std;

class PowerPlant{
public:
	PowerPlant();
	~PowerPlant();
	PowerPlant(int, string, int);
	void setMinPlantCost(int minPlantCost);
	void setType(string type);
	void setHouse(int house);
	int getMinPlantCost();
	string getType();
	int getHouse();
	void printPowerPlantSummary();

private:
	int minPlantCost;
	string type;
	int typeCost;
	int house;
};

#endif //POWERPLANT_H