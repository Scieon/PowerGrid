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
	
	//House house;
	//current_player->getHouseManager()->addHouses(house);
	cout << "Here we are inside the AGGRESSIVE STRATEGY; I AM BUYING A HOUSE DUDE " << endl;

	
	//returns all the adjacent indices that the player pAI has (no duplicates, no houses the AI currently owns, only adjacent indices to all houses)
	vector<int> pAIAllAdjacentIndices = mapOfPlayersCity->getMap()->getAdjacentIndices(current_player->getHouseManager()->getHouseIndices());

	
	vector<string> playerNames;

	for (int index : pAIAllAdjacentIndices) {
		//if there is at least 1 player in that location
		if (mapOfPlayersCity->getHouseCount(index) > 0) {
			playerNames = mapOfPlayersCity->getPlayerNames(index);
			break;
		}
	}

	string playerNameWithLessHouses;
	//NEED TO ACCESS THE OTHER PLAYERS HOUSES
	if (playerNames.size() == 1) {
		//if there is only 1 name then find which player has this name and get him
		playerNameWithLessHouses = playerNames[0];
		
		
	}
	else {
		string player1 = playerNames[0];
		string player2 = playerNames[1];
		vector<int> player1Houses = mapOfPlayersCity->getPlayerHouses(player1);
		vector<int> player2Houses = mapOfPlayersCity->getPlayerHouses(player2);

		if (player1Houses.size() < player2Houses.size()) {
			playerNameWithLessHouses = player1;
		}
		else {
			playerNameWithLessHouses = player2;
		}
	}

	vector<int> * HousesOfPlayerWithLessHouses = new vector<int>(mapOfPlayersCity->getPlayerHouses(playerNameWithLessHouses));
	

	//get all adjacent indices that p0 has
	vector<int> p0AllAdjacentIndices = mapOfPlayersCity->getMap()->getAdjacentIndices(HousesOfPlayerWithLessHouses);

	//Go into every house the AI owns, and see if they have common houses with the player
	//if they do then remove it
	//At the end, p0AllAdjacentIndices will own all the potential houses we can build in
	//which is all the adjacent indices of p0 minus the indices that the AI already owns
	for (int AIHouse : pAIAllAdjacentIndices) {
		std::vector<int>::iterator position = std::find(p0AllAdjacentIndices.begin(), p0AllAdjacentIndices.end(), AIHouse);
		//if they own the same house then erase that house
		if (position != p0AllAdjacentIndices.end()) {
			p0AllAdjacentIndices.erase(position);
		}
	}

	//From all the potential locations to place a house
	//Check is there is space to put a house in there
	//If there is space then add a house there
	for (int HouseIndex : p0AllAdjacentIndices) {
		//if there is space then add house
		if (mapOfPlayersCity->isCityFree(HouseIndex)) {
			cout << "Aggresive strategy. Building at index " << HouseIndex << endl;
			House house(HouseIndex, mapOfPlayersCity->getIndexName(HouseIndex)); //create house
			current_player->getHouseManager()->addHouses(house); //add house to AI
			mapOfPlayersCity->setPlayerHouse(HouseIndex, current_player->getColor()); //add house in map
		}
	}

	delete HousesOfPlayerWithLessHouses;
	HousesOfPlayerWithLessHouses = NULL;

};