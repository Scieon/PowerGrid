#include "MapOfPlayersCity.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//Player's houses location


MapOfPlayersCity::MapOfPlayersCity()
{
	player_houses = new vector<vector<string> >(42);
}


MapOfPlayersCity::~MapOfPlayersCity()
{
}

vector<vector<string>>* MapOfPlayersCity::getPlayerHousesVector()
{
	return player_houses;
}

void MapOfPlayersCity::setPlayerHouse(int index, string name)
{
	(*player_houses)[index].push_back(name);
}

//Loads values to player_houses
void MapOfPlayersCity::loadPlayerHouses(vector<vector<string> > set)
{
	//0-41 (size of the map)
	for (unsigned int i = 0; i < set.size(); i++) {
		//clears by setting to all values to zero.
		(*player_houses)[i].clear();

		//copies player names to house locations (from second vector)
		for (unsigned int j = 0; j < set[i].size(); j++) {
			(*player_houses)[i].push_back(set[i][j]);
		}

	}
}

//Checks if step 2 is not started
bool MapOfPlayersCity::isCityFree(int index)
{
	if (!STEP2) {
		if (player_houses[index].size() == 0) {
			return true;
		}
		return false;
	}
	
}

//Prints all the players city 
void MapOfPlayersCity::printPlayersCity()
{
	cout << "Printing players in map..." << endl;
	int i = 0;

	for (vector<string> player : *player_houses) {
		if (player.size() == 1) {
			cout << "Index: " << i << " Player Color: " << player[0] << endl;
		}
		else if (player.size() == 2) {
			cout << "Index: " << i << " Player Color 1: " << player[0] << " Player Color 2: " << player[1] << endl;
		}
		i++;
	}
}