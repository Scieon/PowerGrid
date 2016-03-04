#ifndef POWERPLANTMANAGER_H
#define POWERPLANTMANAGER_H
#include "Powerplant.h"
#include <vector>
#include <algorithm>

using namespace std;

class PowerplantManager {


public:
	
	~PowerplantManager();

	static PowerplantManager* getInstance()
	{
		static PowerplantManager * instance = new PowerplantManager();
		return instance;
	}

	void printMarket();

	int findPowerplantIndexInActualMarket(int bid);

	bool isPowerplantInActualMarket(int bid);

	void sortMarket();
	

private:
	PowerplantManager(); //Constructor is private
	PowerplantManager(PowerplantManager const&) = delete; // Don't Implement
	void operator=(PowerplantManager const&) = delete; // Don't implement

	Powerplant powerplants[3];
	int numberOfPlants;
	vector<Powerplant> * powerplantsVector;
};




#endif