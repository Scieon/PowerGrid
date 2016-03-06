#pragma once
#include <vector>
#include <string>
#include "CityManager.h"
#include "Player.h"
using namespace std;

class MapOfPlayersCity
{
public:
	MapOfPlayersCity();
	MapOfPlayersCity(CityManager *);
	~MapOfPlayersCity();

	vector<vector <Player> > *getPlayerHousesVector();

	void setPlayerHouse(int index, Player name);
	void loadPlayerHouses(vector<vector<Player> > set);

private:
	//Player's houses location (holds names)
	vector<vector<Player> > * player_houses;

	CityManager *city_manager;
};

