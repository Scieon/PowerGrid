#include "Area.h"
#include <vector>
#include <string>

using namespace std;

using std::vector;
using std::string;

const string Area::PURPLE = "purple"; // 0
const string Area::BLUE = "blue"; // 1
const string Area::RED = "red"; // 2
const string Area::YELLOW = "yellow"; // 3
const string Area::GREEN = "green"; // 4
const string Area::BROWN = "brown"; // 5

Area::Area()
{
}

Area::Area(int index)
{
	this->index = index;

	switch (index) {
	case 0: 
		color = PURPLE;
		break;
	case 1:
		color = BLUE;
		break;
	case 2:
		color = RED;
		break;
	case 3:
		color = YELLOW;
		break;
	case 4:
		color = GREEN;
		break;
	case 5:
		color = BROWN;
		break;
	}


}

Area::~Area()
{
}

string Area::getColor()
{
	return color;
}

int Area::getIndex()
{
	return index;
}

void Area::setColor(string color)
{
	this->color = color;
}

void Area::setIndex(int index)
{
	this->index = index;
}

//Used to sort Areas.
bool Area::operator<(const Area area) const
{
	return index < area.index;
}
