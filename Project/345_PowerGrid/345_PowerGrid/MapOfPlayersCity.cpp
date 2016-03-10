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
	int i = 0;

	for (vector<string> player : *player_houses){

		if (!map->indexInGame(i)) {
			i++;
			continue;
		}
		else if (player.size() == 0) {
			cout << "Index: " << i << " Name: " << city_manager.getName(i) << " -- Available"<< endl;
		}
		else if (player.size() == 1) {
			cout << "Index: " << i <<  " Name: " << city_manager.getName(i) << " -- Player: " << player[0] << endl;
		}
		else if (player.size() == 2) {
			cout << "Index: " << i << " Name: " << city_manager.getName(i) << " -- Player1: " << player[0] << " -- Player2: " << player[1] << endl;
		}
		i++;
	}
}

//prints the valid indices available to put a player in
void MapOfPlayersCity::printAvailableIndices(){

	vector<int> indices =  *(map->getPlayedIndicesVector());
	
	int i = 0;
	for (int index : indices) {
		if ((*player_houses)[index].size() == 0) {
			cout << "Index: " << index << " Name: " << city_manager.getName(index) << endl;
		}
		i++;
	}

}

//gets the vertices that are free to put a player in (empty) and are in game
vector<int> * MapOfPlayersCity::getAvaiableIndices() {
	vector<int> indices = *(map->getPlayedIndicesVector());
	vector<int> * emptyIndices = new vector<int>();

	//for each index that is in the game check if there is no player inside
	for (int index : indices) {
		if ((*player_houses)[index].size() == 0) {
			emptyIndices->push_back(index);
		}
	}
	return emptyIndices;
}

//Checks if the index is available to put a player in (is empty). Used before purchasing house
bool MapOfPlayersCity::isIndexAvailable(int index){
	//check if user put invalid range of input
	//check if the index is in the game
	//Check if city is free
	if (index < 0 || index > 41
		|| !map->indexInGame(index)
		|| !isCityFree(index)) {
		return false;
	}
	return true;
}

//returns the name of city using the index
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

//prints the lowest cost from our houses to of each avaiable city
void MapOfPlayersCity::printAvailableIndicesCost(vector<int> * houses) {

	vector<int> * availableIndices = getAvaiableIndices(); //gets available indices ex: 1 3 5 6 8 10
	int size = availableIndices->size(); //size of avaiable indices vector

	vector<double> * costOfEachAvaiableIndices = new vector<double>(size, 99999);

	vector<double> min_distance;
	vector<int> previous;

	int count = 0;
	for (int index : *houses) {
		count = 0; //reinitalize

		for (int cities : *availableIndices) {
			//computes distance from index to to all vertices in map
			map->DijkstraComputePaths(index, *(map->getMap()), min_distance, previous);
			//if cost is less from a city then change it
			if (min_distance[cities] < (*costOfEachAvaiableIndices)[count]) {
				(*costOfEachAvaiableIndices)[count] = min_distance[cities];
			}
			count++;
		}
	}
	count = 0;

	//print out costs to go in that location
	for (int index : *availableIndices) {
		cout << "Index: " << index << " Name: " << city_manager.getName(count) << " -- Cost: " << (*costOfEachAvaiableIndices)[count] << endl;
		count++;
	}

	delete availableIndices;
	availableIndices = NULL;
	delete costOfEachAvaiableIndices;
	costOfEachAvaiableIndices = NULL;

}

//returns the lowest cost from our houses to of each avaiable city
vector<double>* MapOfPlayersCity::getAvailableIndicesCost(vector<int> * houses) {
	vector<int> * availableIndices = getAvaiableIndices(); //gets available indices ex: 1 3 5 6 8 10
	int size = availableIndices->size(); //size of avaiable indices vector

	vector<double> * costOfEachAvaiableIndices = new vector<double>(size, 99999);

	vector<double> min_distance;
	vector<int> previous;

	int count = 0;
	for (int index : *houses) {
		count = 0; //reinitalize

		for (int cities : *availableIndices) {
			//computes distance from index to to all vertices in map
			map->DijkstraComputePaths(index, *(map->getMap()), min_distance, previous);
			//if cost is less from a city then change it
			if (min_distance[cities] < (*costOfEachAvaiableIndices)[count]) {
				(*costOfEachAvaiableIndices)[count] = min_distance[cities];
			}
			count++;
		}
	}

	return costOfEachAvaiableIndices;

}
