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

	vector<Powerplant> * getPowerplantVector();

	void setPowerplantVector(vector<Powerplant> * pp_vector);

	string getPlantType(int index);

	int getPlantReq(int index);

	bool getStep3Trigger();

	void setStep3(bool value);

	void setStep3Trigger(bool value);

	void buildingPhaseReorder(int highestNumberOfHouses);

	void bureaucracyPhaseReorder();

	void removeLowestPowerplant();
	
private:
	vector<Powerplant> * powerplantsVector;
	bool step3trigger;
	bool step3;
};

#endif