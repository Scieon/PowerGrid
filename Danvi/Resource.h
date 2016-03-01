#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

using namespace std;

class Resource{
public:
	Resource();
	~Resource();
	Resource(int, int, int, int);
	void setUranium(int uranium);
	void setOil(int oil);
	void setGarbage(int garbage);
	void setCoal(int coal);
	int getUranium();
	int getOil();
	int getGarbage();
	int getCoal();

private:
	int uranium;
	int oil;
	int garbage;
	int coal;
};

#endif //RESOURCE_H