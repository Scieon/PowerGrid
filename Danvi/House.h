#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
using namespace std;

class House{
public:
	House();
	~House();
	House(string);
	string getLocation();
	void setLocation(string);

private: 
	int house;
	string location;
};

#endif //HOUSE_H