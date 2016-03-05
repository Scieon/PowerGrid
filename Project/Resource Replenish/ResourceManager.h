#pragma once

#include "Coal.h"
#include "Oil.h"
#include "Garbage.h"
#include "Uranium.h"
#include <string>

class ResourceManager {
public:
	ResourceManager(); //Constructor
	~ResourceManager(); //Destructor
	void edit(string type, int quantity, int cost); //Change function name
	void initialize(string type, int cost);

	int getResourceQuantity(string resource);
	int getResourceCost(string resource);

private:

	Coal * coal;
	Oil * oil;
	Garbage * garbage;
	Uranium * uranium;
};