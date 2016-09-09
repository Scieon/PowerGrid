/*
#include "Player.h"
#include "IOFile.h"
#include "Map.h"


int main() {
	Map *test = new Map();

	Player* player1 = new Player("Jimmy", "red");
	Player* player2 = new Player("Bob", "blue");

	(*player1).addElectro(5);

	(*player2).addCoal(7);

	IOFile::savePlayer(*player1, *player2);

	
	Map::setPlayerHouse(0, player1->getName());
	Map::setPlayerHouse(0, player2->getName());
	Map::setPlayerHouse(10, player1->getName());
	Map::setPlayerHouse(20, player2->getName());
	Map::setPlayerHouse(30, player1->getName());
	Map::setPlayerHouse(40, player2->getName());

	//saves to map.txt
	IOFile::saveMap();

	system("pause");
	return 0;
}
*/