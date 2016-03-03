#ifndef URANIUM_H
#define URANIUM_H
#include "Resource.h"

class Uranium : public Resource {

public:
	Uranium();
	~Uranium();
	Uranium(int quantity);
	int getCost() const;
	void setCost(int cost);
	string getType() const;

private:
	int cost;
	string type = "Uranium";
};

#endif