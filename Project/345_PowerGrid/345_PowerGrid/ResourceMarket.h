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

	void showInfo();
	void refill(int step, int players);

	int findEmpty(string resource); //Finds the last index that is empty, this will be the index used to refill the resource
	int findPartial(string resource); //Finds the last index that is not full but not empty

	void replenish(string resource, int quantity); //Quantity to be filled  

private:
	ResourceManager * market[12];
	
	/*
	These Functions should be private for final build
		int findEmpty(string resource); 
		find partial
		void replenish(string resource, int quantity);
	*/

};

