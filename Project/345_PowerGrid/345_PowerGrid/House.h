#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
using namespace std;

class House{
public:
	House();
	~House();
	House(int, string);
	int getIndex();
	void setIndex(int);
	string getLocation();
	void setLocation(string);

private: 
	int index;
	string location;
};

#endif //HOUSE_H