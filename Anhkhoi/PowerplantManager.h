#ifndef POWERPLANTMANAGER_H
#define POWERPLANTMANAGER_H
#include "Powerplant.h"
#include <vector>
#include <algorithm>

using namespace std;

class PowerplantManager {


public:
	PowerplantManager();
	~PowerplantManager();

	void printMarket();

	int findPowerplantIndexInActualMarket(int bid);

	bool isPowerplantInActualMarket(int bid);

	void sortMarket();
	

private:
	Powerplant powerplants[3];
	int numberOfPlants;
	vector<Powerplant> * powerplantsVector;


};




#endif