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
	static void saveMap(MapOfPlayersCity * map);

	//load into static instance of player_houses (in Map class) from file
	static void loadMap(MapOfPlayersCity * map);

	//saves areas
	static void saveAreas(MapOfPlayersCity * map);

	//load areas
	static vector<Area> * loadAreas();

	//Load to players from player.txt
	static void loadPlayer(Player & player1, Player & player2);

	//Verifies if there is no player in a city where we are not playing
	static bool verifyMapCorrectness(MapOfPlayersCity *map);

	//Saves powerplants
	static void savePowerplants(PowerplantManager * pp_manager);

	//Loads powerplants
	static void loadPowerplants(PowerplantManager * pp_manager);

	//saves the number of players and the turn we are at
	static void saveNbPlayerAndTurnCounter(int nb_players, int turn);

	//loads the number of players and the turn we are at
	static void loadNbPlayersAndTurnCoutner(int &nb_players, int &turn);

private:
	
};


