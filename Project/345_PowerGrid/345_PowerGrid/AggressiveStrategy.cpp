#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
#include "AStrategy.h"
#include "AggressiveStrategy.h"
#include "Player.h"
#include "Board.h"
#include "MapOfPlayersCity.h"
#include "Map.h"

//random: randomly choose between powering houses or not, 
//then if powering, choose a random valid target house.


void AggressiveStrategy::execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity) {
	House house;

	current_player->getHouseManager()->addHouses(house);
	cout << "Here we are inside the AGGRESSIVE STRATEGY; I AM BUYING A HOUSE DUDE " << endl;
};