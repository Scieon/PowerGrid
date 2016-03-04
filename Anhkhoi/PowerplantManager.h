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

	void sortMarket();
	

private:
	Powerplant powerplants[3];
	int numberOfPlants;
	vector<Powerplant> * powerplantsVector;


};




#endif