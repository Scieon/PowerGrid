
#pragma once
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

private:
	Coal coal;
	Oil oil;
	Garbage garbage;
	Uranium uranium;

};

