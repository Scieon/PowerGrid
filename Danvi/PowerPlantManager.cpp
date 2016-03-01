#include <iostream>
#include <string>
#include "PowerPlantManager.h"

using namespace std;

//Default constructor
PowerPlantManager::PowerPlantManager(){
	plantCount = 0;
}

//Destructor
PowerPlantManager::~PowerPlantManager(){

}

//Function that adds the power plants to the vector collection of power plants
void PowerPlantManager::addPowerPlant(PowerPlant powerPlant)
{
	powerPlantVector.push_back(powerPlant);
	plantCount++;
}

//Accessor function that gets the number of power plants in the player
int PowerPlantManager::getSize()
{
	return powerPlantVector.size();
}

//Function that takes the highest cost of the power plant between the players
int PowerPlantManager::determineHighestCost(){
	int temp = 0;

	for (int i = 0; i < powerPlantVector.size(); i++){
		int currentCost = powerPlantVector[i].getMinPlantCost();
		if (temp <= currentCost){
			temp = currentCost;
		}
	}
	return temp;
}




