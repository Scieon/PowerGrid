#ifndef POWERPLANTMANAGER_H
#define POWERPLANTMANAGER_H
#include "Powerplant.h"

class PowerplantManager {


public:
	PowerplantManager();
	~PowerplantManager();

private:
	Powerplant powerplants[3];
	int numberOfPlants;


};




#endif