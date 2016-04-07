#pragma once
#include "AStrategy.h"
#include "MapOfPlayersCity.h"
#include "Player.h"

class RandomStrategy : public AStrategy {
public: 
	void execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity);
};
