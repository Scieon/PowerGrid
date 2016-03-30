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

	void setStep2(bool);
	void setStep3(bool);

	bool isCityFree(int index);

	void printPlayersCity();

	void printAvailableIndices();

	vector<int> getAvaiableIndices();

	bool isIndexAvailable(int index);

	string getIndexName(int index);

	Map * getMap();

	void setMap(Map * map);

	void printAvailableIndicesCost(vector<int>* houses, int playerElektro);

	pair<vector<double>, vector<list<int> > > getAvailableIndicesCost(vector<int>* houses, int playerElektro);

	int costToBuildHouse(int index);

	bool playerOwnsHouseAndCityHasEmptySpace(vector<int>* houses, int houseIndex);

private:
	//Player's houses location (holds names)
	vector<vector<string> > * player_houses;
	CityManager city_manager;
	Map *map;

	bool step2;
	bool step3;
};

