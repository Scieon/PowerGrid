#pragma once
#include <vector>
#include <string>
#include "CityManager.h"
#include "Map.h"
using namespace std;

class MapOfPlayersCity
{
public:
	MapOfPlayersCity(Map * map);
	~MapOfPlayersCity();

	vector<vector <string> >* getPlayerHousesVector();

	void setPlayerHouse(int index, string name);
	void loadPlayerHouses(vector<vector<string> > set);

	bool isCityFree(int index);

	void printPlayersCity();

	void printAvailableIndices();

	vector<int>* getAvaiableIndices();

	bool isIndexAvailable(int index);

	string getIndexName(int index);

	Map * getMap();

	void setMap(Map * map);

	void printAvailableIndicesCost(vector<int>* houses);

	vector<double>* getAvailableIndicesCost(vector<int>* houses);

private:
	//Player's houses location (holds names)
	vector<vector<string> > * player_houses;
	CityManager city_manager;
	Map *map;

	const bool STEP2 = false; //MUST REMOVE FOR FINAL BUILD
};

