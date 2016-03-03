#ifndef RESOURCE_H
#define RESOURCE_H


#include <string>
#include <iostream>

using namespace std;

//Abstract class where the four resources will inherit from
class Resource {

public:

	virtual ~Resource();
	Resource();
	
	void setQuantity(int qty);
	void addQuantity(int qty);
	int getQuantity() const;
	void setColor(string color);
	string getColor() const;
	//Virtual functions to make the class abstract
	virtual int getCost() const = 0;
	virtual void setCost(int cost) = 0;


private:
	int quantity; //Amount of resources
	string color; //Color of the resource object
};


#endif