#pragma once
#include <string>
using std::string;

class House {

public:
	House();
	House(string color);
	void setColor(string color);
	string getColor() const;
	int getHouses() const;
	void setHouses(int house);


private:

	int number_of_houses; //Players start with 0 Houses
	string color;

};