#pragma once
#include "Board.h"
class BoardBuilder
{
public:
	Board* getBoard() {
		return board;
	}

	void createNewBoard() {
		board = new Board();
	}

	void setBoard(Board* b) {
		board = b;
	}

	virtual void saveGame() = 0;
	virtual void loadGame() = 0;

	Board * board;
};

