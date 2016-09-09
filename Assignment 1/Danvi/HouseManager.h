#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#include <iostream>
#include <vector>
#include "House.h"
using namespace std;

class HouseManager{
public:
	HouseManager();
	~HouseManager();
	void setHouseCount(int houseCount);
	void addHouses(House house);
	int getHouseCount();

private:
	int houseCount;
	vector<House> houseVector;
};

#endif //HOUSES_H