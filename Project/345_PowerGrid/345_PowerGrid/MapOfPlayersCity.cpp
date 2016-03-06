#include "MapOfPlayersCity.h"

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