#ifndef COAL_H
#define COAL_H


#include "Resource.h"


class Coal : public Resource {

public:
	~Coal();
	Coal();
	Coal(int quantity);
	int getCost() const;
	void setCost(int cost);
	string getType() const;

private:
	int cost;
	string type = "Coal";
};


#endif