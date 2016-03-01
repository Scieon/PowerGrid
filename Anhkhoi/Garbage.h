#pragma once
#include "Resource.h"


class Garbage : public Resource {

public:
    Garbage();
	Garbage(int quantity);
	~Garbage();
	void setCost(int cost);
	int getCost() const;
	string getType() const;

private:
	int cost;
	string type = "Garbage";


};

