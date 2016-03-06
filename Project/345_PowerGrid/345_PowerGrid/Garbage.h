#pragma once
#include "Resource.h"


class Garbage : public Resource {

public:
    Garbage();
	Garbage(int quantity);
	~Garbage();

	string getType() const;

private:
	
	string type = "Garbage";


};

