#pragma once
#include "AStrategy.h"

class AggressiveStrategy : public AStrategy {
public: 
	void execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity);
};
