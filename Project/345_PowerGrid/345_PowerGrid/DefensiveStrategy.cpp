#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
#include "AStrategy.h"
#include "Player.h"
#include "Board.h"
#include "MapOfPlayersCity.h"
#include "Map.h"

//random: randomly choose between powering houses or not, 
//then if powering, choose a random valid target house.


void DefensiveStrategy::execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity) {
	//House house;
	//current_player->getHouseManager()->addHouses(house);
	cout << endl << "HERE I AM INSIDE THE DEFENSIVE STRATEGY BUYIGN SOME HOUSE TOO" << endl;

	int indexToBuy = -1; //contains the index to buy a house in
	vector<int> pAIHouseIndices = *(current_player->getHouseManager()->getHouseIndices()); //player house vertices

	//This loop checks every the hard coded adjacent indices to see if AI has all of the 
	//adjacent indices, but not the index that is adjacent to them all
	int mapsize = 42;
	for (int i = 0; i < mapsize; i++) {

		if (mapOfPlayersCity->getMap()->indexInGame(i)) {
			vector<int> adjacentIndices = mapOfPlayersCity->getMap()->getAdjacentIndices(i); //hard coded adjacent indices to index i
			bool notFound = false; //used if 1 adjacent vertex is not found, to skip to the next index

								   //if the player already own a house at index i, then skip
			if (mapOfPlayersCity->ownsHouse(current_player->getColor(), i)) {
				continue;
			}

			//This loop checks if the player owns all the adjacent indices to an index
			//it stops when if the player does not own one of adjacent indices
			for (int index : adjacentIndices) {
				//find index in the houses
				std::vector<int>::iterator position = std::find(pAIHouseIndices.begin(), pAIHouseIndices.end(), index);
				if (position == pAIHouseIndices.end()) {
					notFound = true;
					break;
				}
			}
			//one of them was not found, then go to the next index in the map
			if (notFound) {
				continue; //goto next index in the map
			}
			else {
				//index was found
				indexToBuy = i;
				break; //get out of loop to buy house
			}
		}


	}

	if (indexToBuy == -1) {
		cout << "THERE IS NO INDEX THAT IS ADJACENT TO ALL OF THE OTHER INDICES" << endl;
	}
	else {
		double shorestPathCost = 99999; //set to very big value

										//get the shorest path from all the owned house indices to the index to buy to
		for (int houseIndex : pAIHouseIndices) {
			//get cost of path to buy to index
			double costToIndex = mapOfPlayersCity->getMap()->getCostTo(indexToBuy);

			//if we find a lower cost, then change the cost
			if (costToIndex < shorestPathCost) {
				shorestPathCost = costToIndex;
			}
		}

		cout << endl << "Buying house with index " << indexToBuy << " in the defensive strategy" << endl;
		//Add house section
		current_player->subtractMoney((int)shorestPathCost + mapOfPlayersCity->costToBuildHouse(indexToBuy)); //substract shortest path cost + house cost
		House house(indexToBuy, mapOfPlayersCity->getIndexName(indexToBuy)); //create house
		current_player->getHouseManager()->addHouses(house); //add house to player
		mapOfPlayersCity->setPlayerHouse(indexToBuy, current_player->getColor()); //add house in map
		cout << "House with index " << indexToBuy << " bought!" << endl << endl;
	}




};