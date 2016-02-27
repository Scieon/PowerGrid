/*

#include "Player.h"
#include "IOFile.h"
#include "Map.h"


int main() {
Map *test = new Map();

Player* player1 = new Player("Frank", "pink");
Player* player2 = new Player("Timmy", "yellow");

//player1->print();
//player2->print();

IOFile::loadPlayer(*player1, *player2);

//player1->print();
//player2->print();

Map * testmap = new Map();

Map::setPlayerHouse(0, player1->getName());
Map::setPlayerHouse(0, player2->getName());
Map::setPlayerHouse(1, player2->getName());
Map::setPlayerHouse(1, player1->getName());
Map::setPlayerHouse(10, player1->getName());
Map::setPlayerHouse(20, player2->getName());
Map::setPlayerHouse(30, player1->getName());
Map::setPlayerHouse(40, player2->getName());

IOFile::loadMap();

system("pause");
return 0;
}
*/