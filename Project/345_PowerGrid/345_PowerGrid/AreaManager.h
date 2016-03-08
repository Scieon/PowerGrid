#pragma once
#include "Area.h"
#include <vector>

using namespace std;



class AreaManager
{
public:
	AreaManager();
	~AreaManager();

	bool areAdjacent(vector<Area> colors);

	void setGameAreas(vector<Area> colors);

	vector<bool>* getAreaPlayed();


private:
	vector<bool> * area_is_played;
};

