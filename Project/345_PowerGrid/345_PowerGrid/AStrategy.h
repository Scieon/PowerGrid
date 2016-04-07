#pragma once
#include "MapOfPlayersCity.h"
using namespace std;

class Player;

class AStrategy {
public: 
	virtual void execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity) = 0;
};
