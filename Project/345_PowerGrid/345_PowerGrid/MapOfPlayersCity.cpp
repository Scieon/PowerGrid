#include "MapOfPlayersCity.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//Player's houses location


MapOfPlayersCity::MapOfPlayersCity(Map * map){
	player_houses = new vector<vector<string> >(42);
	city_manager = CityManager();
	this->map = map;
}


MapOfPlayersCity::~MapOfPlayersCity(){
}

vector<vector<string>>* MapOfPlayersCity::getPlayerHousesVector(){
	return player_houses;
}

void MapOfPlayersCity::setPlayerHouse(int index, string color){
	(*player_houses)[index].push_back(color);
}

//Loads values to player_houses
void MapOfPlayersCity::loadPlayerHouses(vector<vector<string> > set){
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
bool MapOfPlayersCity::isCityFree(int index){
	if (!STEP2 && (*player_houses)[index].size() == 0) {
		return true;
	}
	return false;
	
}

//Prints all the players city 
void MapOfPlayersCity::printPlayersCity(){
	cout << "Printing players in map..." << endl;
	int i = 0;

	for (vector<string> player : *player_houses){
		if (player.size() == 1) {
			cout << "Index: " << i << " Player Color: " << player[0] << endl;
		}
		else if (player.size() == 2) {
			cout << "Index: " << i << " Player Color 1: " << player[0] << " Player Color 2: " << player[1] << endl;
		}
		i++;
	}
}

//prints the valid indices available to play 
void MapOfPlayersCity::printAvailableIndices(){

	vector<int> indices =  *(map->getPlayedIndicesVector());
	
	int i = 0;
	for (int index : indices) {
		if ((*player_houses)[index].size() == 0) {
			cout << "Index: " << i << " Name: " << city_manager.getName(i) << endl;
		}
		i++;
	}

}

//Checks if the index is available. Used before purchasing house
bool MapOfPlayersCity::isIndexAvailable(int index){
	//check if user put invalid range of input
	//check if the index is in the game
	//Check if city is free
	if (index < 0 || index > 41
		|| !map->isIndexInGame(index)
		|| !isCityFree(index)) {
		return false;
	}
	return true;
}

string MapOfPlayersCity::getIndexName(int index){
	return city_manager.getName(index);
}

//returns the map as a pointer
Map* MapOfPlayersCity::getMap(){
	return map;
}

//sets map
void MapOfPlayersCity::setMap(Map * map){
	this->map = map;
}
