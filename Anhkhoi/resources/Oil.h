#ifndef OIL_H
#define OIL_H
#include "Resource.h"

class Oil : public Resource {
public:

	Oil();
	Oil(int quantity);
	~Oil();
	int getCost() const;
	void setCost(int cost);
	string getType() const;

private:
	int cost;
	string type = "Oil";

};

#endif