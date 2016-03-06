#include "MapOfPlayersCity.h"
#include <vector>

using namespace std;
//Player's houses location

MapOfPlayersCity::~MapOfPlayersCity()
{
}

MapOfPlayersCity::MapOfPlayersCity()
{
	player_houses = new vector<vector<Player> >(42);

	//clear vectors with default player values
	for (vector<Player> vec : *player_houses) {
		vec.clear();
	}
}

MapOfPlayersCity::MapOfPlayersCity(CityManager *city)
{
	city_manager = city;
}



vector<vector<Player> >* MapOfPlayersCity::getPlayerHousesVector()
{
	return player_houses;
}

void MapOfPlayersCity::setPlayerHouse(int index, Player player)
{
	(*player_houses)[index].push_back(player);
}

//Loads values to player_houses
void MapOfPlayersCity::loadPlayerHouses(vector<vector<Player> > set)
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