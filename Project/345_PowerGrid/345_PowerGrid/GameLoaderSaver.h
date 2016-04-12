//Director
#include "BoardBuilder.h"
#pragma once
class GameLoaderSaver {
public:
	void setGameBuilder(BoardBuilder* bb) {
		m_boardBuilder = bb;
	}

	Board* getBoard() {
		return m_boardBuilder->getBoard();
	}

	void saveBoard(Board* b) {
		m_boardBuilder->setBoard(b);
		m_boardBuilder->saveGame();
	}

	void loadBoard() {
		m_boardBuilder->createNewBoard();
		m_boardBuilder->loadGame();
	}

private:

	BoardBuilder* m_boardBuilder;

};