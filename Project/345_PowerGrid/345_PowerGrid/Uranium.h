#ifndef URANIUM_H
#define URANIUM_H
#include "Resource.h"

class Uranium : public Resource {

public:
	Uranium();
	~Uranium();
	Uranium(int quantity);
	string getType() const;

private:
	
	string type = "Uranium";
};

#endif