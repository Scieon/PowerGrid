#include <iostream>
#include <string>
#include "HouseManager.h"

using namespace std;

//Default constructor
HouseManager::HouseManager(){ 
	houseCount = 0;
	houseVector = vector<House>();

	houseVector.clear();
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

//Check if the maximum number of houses per player is reached
bool HouseManager::isHouseCountMax()
{
	return houseCount == MAX_HOUSE_COUNT;
}

//Adding the number of bought houses/cities to the collection
void HouseManager::addHouses(House house)
{
	houseVector.push_back(house);
	houseCount++;
}




