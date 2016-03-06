#pragma once
#include "City.h"
#include <vector>

using namespace std;

class CityManager
{
public:
	CityManager();
	~CityManager();

	string getName(int index);

	int getAreaIndex(int index);

	


private:
	//City index, cityName, Area ; Indices are found in "PowerGridUsMap_nums.vector_cityjpg"
	City * array_city;

	void addIndexNameArea(int index, string name, int area);
};

