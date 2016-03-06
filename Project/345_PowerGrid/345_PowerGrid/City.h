#pragma once
#include "Area.h"
#include <string>

using namespace std;

class City
{
public:
	City();
	City(int index, string name, int area);
	~City();

	int getIndex();
	string getName();
	Area getAreaIndex();




private:
	int index;
	string name;
	Area area;



};

