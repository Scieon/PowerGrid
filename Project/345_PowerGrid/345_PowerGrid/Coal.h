#ifndef COAL_H
#define COAL_H

#include "Resource.h"


class Coal : public Resource {

public:
	~Coal();
	Coal();
	Coal(int quantity);
	string getType() const;

private:
	string type = "Coal";
};


#endif