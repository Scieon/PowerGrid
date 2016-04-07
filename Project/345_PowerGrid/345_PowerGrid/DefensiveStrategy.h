#pragma once
#include "AStrategy.h"

class DefensiveStrategy : public AStrategy {
public:
	void execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity);
};
