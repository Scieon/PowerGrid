//concerete bulider 1

#pragma once
#include "BoardBuilder.h"

class NormalGameBuilder : public BoardBuilder {

public:
	virtual void saveGame() {
		board->saveGame();
	}

	virtual void loadGame() {
		board->loadGame("player.txt", "area.txt", "map.txt", "powerplant.txt", "nbPlayerAndTurn.txt");

	}
};