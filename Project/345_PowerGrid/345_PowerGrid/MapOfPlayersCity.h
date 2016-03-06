#pragma once
#include <vector>
#include <string>
using namespace std;

class MapOfPlayersCity
{
public:
	MapOfPlayersCity();
	~MapOfPlayersCity();

	vector<vector <string> >* getPlayerHousesVector();

	void setPlayerHouse(int index, string name);
	void loadPlayerHouses(vector<vector<string> > set);

private:
	//Player's houses location (holds names)
	vector<vector<string> > * player_houses;
};

