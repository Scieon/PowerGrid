#ifndef POWERPLANTMANAGER_H
#define POWERPLANTMANAGER_H

#include <iostream>
#include <vector>
#include "PowerPlant.h"

using namespace std;

class PowerPlantManager{
public:
	PowerPlantManager();
	~PowerPlantManager();
	void addPowerPlant(PowerPlant powerPlant);
	int determineHighestCost();
	int getSize();

private:
	int plantCount;
	vector<PowerPlant> powerPlantVector;
};

#endif //POWERPLANTMANAGER_H