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

	bool hasEnoughElektroForMarket(int elektro);

	Powerplant* getAndRemoveSpecificPowerplant(int plantBid);

	
private:
	vector<Powerplant> * powerplantsVector;
};

#endif