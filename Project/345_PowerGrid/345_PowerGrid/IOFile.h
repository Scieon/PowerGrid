#pragma once
#include "Player.h"
#include "MapOfPlayersCity.h"
#include "Area.h"
#include <vector>

using std::vector;

class IOFile
{
public:
	IOFile();
	~IOFile();

	//Saves players to player.txt
	static void savePlayer(Player & player1, Player & player2);

	//save to file from static instance of player_houses (in Map class)
	static void saveMap(MapOfPlayersCity *);

	//load into static instance of player_houses (in Map class) from file
	static void loadMap(MapOfPlayersCity *);

	//saves areas
	static void saveAreas(MapOfPlayersCity * map);

	//load areas
	static vector<Area> * loadAreas();

	//Load to players from player.txt
	static void loadPlayer(Player & player1, Player & player2);

	//Verifies if there is no player in a city where we are not playing
	static bool verifyMapCorrectness(MapOfPlayersCity *map);

	static void savePowerplants(PowerplantManager * pp_manager);

	static void loadPowerplants(PowerplantManager * pp_manager);

private:
	
};


