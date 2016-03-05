#pragma once

#include "ResourceManager.h"
#include "Coal.h"
#include "Oil.h"
#include "Garbage.h"
#include "Uranium.h"

//This class is the resource market that holds all four resources that players will buy from
class ResourceMarket {

public:
	ResourceMarket();
	~ResourceMarket();

	void showInfo(string resource);
	void refill(int step, int players);

	int findEmpty(string resource); //Finds the last index that is empty, this will be the index used to refill the resource

private:
	ResourceManager * market[12];
	//int findEmpty(string resource); //Finds the last index that is empty, this will be the index used to refill the resource

};

