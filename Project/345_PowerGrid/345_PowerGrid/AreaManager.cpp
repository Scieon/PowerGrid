#include "AreaManager.h"
#include "Area.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


AreaManager::AreaManager()
{
	area_is_played = new vector<bool>{ false,false,false,false,false,false };
}


AreaManager::~AreaManager()
{
	delete area_is_played;
	area_is_played = NULL;
}

/*
Sets game areas
*/
void AreaManager::setGameAreas(vector<Area> colors) {
	for (Area a : colors) {
		(*area_is_played)[a.getIndex()] = true;
	}
}

//returns area played
vector<bool> * AreaManager::getAreaPlayed()
{
	return area_is_played;
}


/*
Checks if the areas chosen by the players are adjacent
*/
bool AreaManager::areAdjacent(vector<Area> colors) {

	std::sort(colors.begin(), colors.end());
	int size = colors.size();

	if (size < 3 || size > 5) {
		return false;
	}

	else if (size == 3) {

		int first = colors[0].getIndex();
		int second = colors[1].getIndex();
		int third = colors[2].getIndex();

		//impossible games
		if ((first == 0 && second == 1 && third == 4)
			|| (first == 0 && second == 1 && third == 5)
			|| (first == 0 && second == 2 && third == 4)
			|| (first == 0 && second == 4 && third == 5)
			|| (first == 1 && second == 2 && third == 4)
			|| (first == 1 && second == 3 && third == 4)
			|| (first == 1 && second == 3 && third == 5)
			|| (first == 1 && second == 4 && third == 5)) {
			return false;
		}
		return true;
	}
	else if (size == 4) {

		int first = colors[0].getIndex();
		int second = colors[1].getIndex();
		int third = colors[2].getIndex();
		int fourth = colors[3].getIndex();
		//impossible games
		if ((first == 0 && second == 1 && third == 4 && fourth == 5)
			|| (first == 0 && second == 1 && third == 2 && fourth == 4)
			|| (first == 1 && second == 3 && third == 4 && fourth == 5)) {
			return false;
		}
		return true;
	}

	//else game of 5 is always possible
	return true;


}
