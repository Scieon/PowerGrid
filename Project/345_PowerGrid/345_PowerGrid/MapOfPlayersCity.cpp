#include "MapOfPlayersCity.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <utility> //pair

using namespace std;
//Player's houses location


MapOfPlayersCity::MapOfPlayersCity(Map * map) {
	player_houses = new vector<vector<string> >(42);
	city_manager = CityManager();
	this->map = map;
	step2 = false;
	step3 = false;
}


MapOfPlayersCity::~MapOfPlayersCity() {
}

vector<vector<string>>* MapOfPlayersCity::getPlayerHousesVector() {
	return player_houses;
}

void MapOfPlayersCity::setPlayerHouse(int index, string color) {
	(*player_houses)[index].push_back(color);
}

//Loads values to player_houses
void MapOfPlayersCity::loadPlayerHouses(vector<vector<string> > set) {
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

void MapOfPlayersCity::setStep2(bool value)
{
	step2 = value;
}

void MapOfPlayersCity::setStep3(bool value)
{
	step3 = value;
}

//Checks if there is at least an empty space in the city
bool MapOfPlayersCity::isCityFree(int index) {

	if (step3 && (*player_houses)[index].size() <= 2) {
		return true;
	}

	if (step2 && (*player_houses)[index].size() <= 1) {
		return true;
	}

	if ((*player_houses)[index].size() == 0) {
		return true;
	}

	return false; //city not free
}

//Prints all the players city 
void MapOfPlayersCity::printPlayersCity() {
	int i = 0;

	for (vector<string> player : *player_houses) {

		if (!map->indexInGame(i)) {
			i++;
			continue;
		}
		else if (player.size() == 0) {
			cout << "Index: " << i << " Name: " << city_manager.getName(i) << " -- Available" << endl;
		}
		else if (player.size() == 1) {
			cout << "Index: " << i << " Name: " << city_manager.getName(i) << " -- Player: " << player[0] << endl;
		}
		else if (player.size() == 2) {
			cout << "Index: " << i << " Name: " << city_manager.getName(i) << " -- Player1: " << player[0] << " -- Player2: " << player[1] << endl;
		}
		i++;
	}
}

//prints the valid indices available to put a player in
void MapOfPlayersCity::printAvailableIndices() {

	vector<int> indices = map->getPlayedIndicesVector();

	int i = 0;
	for (int index : indices) {
		if ((*player_houses)[index].size() == 0) {
			cout << "Index: " << index << " Name: " << city_manager.getName(index) << endl;
		}
		i++;
	}

}

//gets the vertices that are free to put a player in (empty) and are in game
vector<int> MapOfPlayersCity::getAvaiableIndices() {
	vector<int> indices = map->getPlayedIndicesVector();
	vector<int> emptyIndices =  vector<int>();

	//check if there is at least 1 empty space for each city
	if (step3) {
		for (int index : indices) {
			if ((*player_houses)[index].size() <= 2) {
				emptyIndices.push_back(index);
			}
		}
	}

	else if (step2) {
		for (int index : indices) {
			if ((*player_houses)[index].size() <= 1) {
				emptyIndices.push_back(index);
			}
		}
	}

	else {
		for (int index : indices) {
			if ((*player_houses)[index].size() == 0) {
				emptyIndices.push_back(index);
			}
		}
	}

	return emptyIndices;
}

//Checks if the index is available to put a player in (is empty). Used before purchasing house
bool MapOfPlayersCity::isIndexAvailable(int index) {
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
string MapOfPlayersCity::getIndexName(int index) {
	return city_manager.getName(index);
}

//returns the map as a pointer
Map* MapOfPlayersCity::getMap() {
	return map;
}

//sets map
void MapOfPlayersCity::setMap(Map * map) {
	this->map = map;
}

//prints the lowest cost from our houses to of each avaiable city
void MapOfPlayersCity::printAvailableIndicesCost(vector<int> * houses, int playerElektro) {

	pair<vector<double>, vector<list<int> > > costAndPath = getAvailableIndicesCost(houses, playerElektro);

	//If it is empty, then don't print
	if (costAndPath == pair<vector<double>, vector<list<int> > >()) {
		return;
	}

	cout << "These are all the destinations you can build in" << endl << endl;

	for (int i = 0; i < costAndPath.first.size(); i++) {

		int index = costAndPath.second.at(i).back(); //last element of the list holds the destination

		cout << "Index: " << index << endl; 
		cout << "Name: " << city_manager.getName(index) << endl;

		cout << "Path to take: ";
		for (int pathIndex : costAndPath.second.at(i)) {
			cout << pathIndex << " ";
		}
		cout << endl;

		cout << "Houses to purchase on path: " << endl;
		for (int pathIndex : costAndPath.second.at(i)) {
			
			//used to find if the house  is already owned by the player
			std::vector<int>::iterator position = std::find(houses->begin(), houses->end(), pathIndex); 
			//Print houses that have one empty space and that tha player does not already own
			if (costToBuildHouse(pathIndex) != 0 && position == houses->end()) {
				cout << "Index: " << pathIndex << " ";
				cout << "Name: " << city_manager.getName(pathIndex) << " ";
				cout << "House cost: " << costToBuildHouse(pathIndex) << endl;
			}
		}
			
		cout << "Total Cost: " << (int)costAndPath.first.at(i) << endl << endl;
	}
}

/*
	This function returns a pair of values that have the cost to each available city
	and the path to that available city.
	This function takes into account how much elektro the player has and returns only 
	cities that the player can purchase
*/
pair<vector<double>, vector<list<int> > > MapOfPlayersCity::getAvailableIndicesCost(vector<int> * houses, int playerElektro) {

	vector<int> availableIndices = getAvaiableIndices(); //gets indices with at least 1 free space available

	
	//For each index with an empty space, remove the indices that we already own 
	for (int i = 0; i < availableIndices.size(); i++) {
		std::vector<int>::iterator pos = std::find(houses->begin(), houses->end(), availableIndices[i]);
		if (pos != houses->end()) {
			availableIndices.erase(availableIndices.begin() + i);
			i--; //since size goes down while index goes up and skips 1 otherwise
		}
	}

	//size of avaiable indices vector
	int size = availableIndices.size(); 


	//IF availableIndicesSIZE == 0, then return an empty pair vector
	if (size == 0) {
		return pair<vector<double>, vector<list<int> > >(); //Empty vector
	}

	vector<double> costOfEachAvaiableIndex =  vector<double>(size, 99999); //vector initalized to 99999 as placeholder
	vector<list<int> > pathOfEachAvailableIndex =  vector<list<int> >(size); //holds shortest path to each available city

	pair<vector<double>, vector<list<int> > >  costAndPath = pair<vector<double>, vector<list<int> > >();

	vector<double> min_distance;
	vector<int> previous;

	int count = 0; //used for the index of vectors to be returned
	for (int index : *houses) {
		count = 0; //reinitalize

		//computes distance from index to to all vertices in map
		map->DijkstraComputePaths(index, *(map->getMap()), min_distance, previous);

		//for each city that has an empty space in the map see if there is a shorter path than already found
		for (int cities : availableIndices) {

			double totalCost = 0; //total cost of distance + houses
			totalCost += min_distance[cities]; //Add cost of distance

			//gets the path from house index to destination
			list<int> path = map->DijkstraGetShortestPathTo(cities, previous); 

			//Goes through each index in the path and add cost to build if the player does not own a house in the city
			for (int houseIndex : path) {

				std::vector<int>::iterator position = std::find(houses->begin(), houses->end(), houseIndex);

				//if the city has a free space and if the player does not currently own that city
				if (isCityFree(houseIndex) && position == houses->end()) {
					//Add the cost to build house in city
					totalCost += costToBuildHouse(houseIndex);
				}
			}

			//if cost is less from a city then change it and add the cost of each house to be purchased in the path
			if (totalCost < costOfEachAvaiableIndex[count]) {

				costOfEachAvaiableIndex[count] = totalCost; //set total cost
				pathOfEachAvailableIndex[count] = path; //set shortest path
			}
			count++;
		}
	}

	//Remove indices where the cost is more than what the player can afford
	for (int i = 0; i < costOfEachAvaiableIndex.size(); i++) {
		int temp = playerElektro;
		double cost = (int)costOfEachAvaiableIndex[i];
		if ((temp - cost) < 0) {
			costOfEachAvaiableIndex.erase(costOfEachAvaiableIndex.begin() + i);
			pathOfEachAvailableIndex.erase(pathOfEachAvailableIndex.begin() + i);
			i--; //recheck the index if we remove (skips one otherwise)
		}
	}

	costAndPath.first = costOfEachAvaiableIndex; //set cost vecor in pair
	costAndPath.second = pathOfEachAvailableIndex; //set path vector in pair


	return costAndPath;

}

int MapOfPlayersCity::costToBuildHouse(int index)
{

	//check if there is at least 1 empty space for each city
	if (step3) {
		switch ((*player_houses)[index].size()) {
		case 0:
			return 10;
		case 1:
			return 15;
		case 2:
			return 20;
		default:
			return 0; //not empty
		}
	}

	else if (step2) {
		switch ((*player_houses)[index].size()) {
		case 0:
			return 10;
		case 1:
			return 15;
		default:
			return 0; //not empty
		}
	}

	else {
		
		switch ((*player_houses)[index].size()) {
		case 0:
			return 10;
		default:
			return 0; //not empty
		}

	}
}

bool MapOfPlayersCity::playerOwnsHouseAndCityHasEmptySpace(vector<int>* houses, int houseIndex)
{
	//Goes through each index in the path
	for (int index : *houses) {

		std::vector<int>::iterator position = std::find(houses->begin(), houses->end(), houseIndex);

		//if the city has a free space and if the player does not currently own a house in that city
		if (isCityFree(houseIndex) && position == houses->end()) {
			return true;
		}
	}


	return false;
}
