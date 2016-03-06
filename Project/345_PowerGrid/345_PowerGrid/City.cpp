#include "City.h"
#include "Area.h"
#include <string>

using namespace std;

City::City() {

}

City::City(int index, string name, int area)
{
	this->index = index;
	this->name = name;
	this->area = Area(area);
}

City::~City()
{
}

int City::getIndex()
{
	return index;
}

string City::getName()
{
	return name;
}

Area City::getAreaIndex()
{
	return area;
}
