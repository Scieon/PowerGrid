/*
#include "Map.h"
#include "Area.h"
#include "Player.h"
#include "IOFile.h"

#include <iostream>
#include <vector>
using std::cout;


int main()
{

vector<int> areas = { 0,2,5 };

//Set game regions
//3 regions for 2 player game
if (!Area::areAdjacent(areas)) {
	cout << "impossible game";
	return 1; //exit
}
else {
	Area::setGameAreas(areas);
}

//create map
Map test = Map(); 

//Initialize players
Player* player1 = new Player("Jimmy", "red");
player1->addElectro(5);
player1->addCoal(5);
player1->addGarbage(5);
player1->addUranium(5);
player1->addOil(5);
player1->addNumberOfHouses(2);

Player* player2 = new Player("Bob", "blue");
player2->addElectro(15);
player2->addCoal(15);
player2->addGarbage(15);
player2->addUranium(15);
player2->addOil(15);
player2->addNumberOfHouses(12);

//See PowerGridUsMap_nums for index of city
//Player1 set house
Map::setPlayerHouse(0, player1->getName());

//Player2 set house
Map::setPlayerHouse(14, player2->getName());


//Save player to player.txt
IOFile::savePlayer(*player1, *player2);

//Save map to map.txt
IOFile::saveMap(); 

//Create random players for test
Player* player3 = new Player("test", "test");
Player* player4 = new Player("ttest", "ttest");


//Load players from player.txt
IOFile::loadPlayer(*player3, *player4);

//Load Map from map.txt
IOFile::loadMap();

cout << "\n";
player3->print();
cout << "\n";
player4->print();

system("pause");
return 0;
}
*/