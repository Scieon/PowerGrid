#pragma once
#include "Player.h"
class IOFile
{
public:
	IOFile();
	~IOFile();

	//Saves players to player.txt
	static void savePlayer(Player & player1, Player & player2);

	//save to file from static instance of player_houses (in Map class)
	static void saveMap();

	//load into static instance of player_houses (in Map class) from file
	static void loadMap();

	//Load to players from player.txt
	static void loadPlayer(Player & player1, Player & player2);
};


