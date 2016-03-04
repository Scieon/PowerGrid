#include <iostream>
#include <string>
#include "HouseManager.h"

using namespace std;

//Default constructor
HouseManager::HouseManager(){ 
	houseCount = 0;
}

//Destructor
HouseManager::~HouseManager(){

}

//Setter to take into account the number of houses/cities claimed bought
void HouseManager::setHouseCount(int houseCount){
	this->houseCount = houseCount;
}

//Getter
int HouseManager::getHouseCount(){
	return houseCount;
}

//Adding the number of bought houses/cities to the collection
void HouseManager::addHouses(House house)
{
	houseVector.push_back(house);
	houseCount++;
}




