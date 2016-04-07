#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
#include "AStrategy.h"
#include "RandomStrategy.h"
#include "Player.h"
#include "Board.h"
#include "MapOfPlayersCity.h"
#include "Map.h"

//random: randomly choose between powering houses or not, 
//then if powering, choose a random valid target house.


void RandomStrategy::execute(Player* current_player, MapOfPlayersCity* mapOfPlayersCity) {

	/*cout << "Randomly choose between powering houses or not, then if powering, choose a random valid target house.\n" << endl;

	int random = rand() % 2;

	while (random == 0) {
	cout << "You will be powering house(s)." << endl;
	int random = rand() % 2;
	}*/

	//Player* current_player = vector_player[2]; //AI player? 
	//RANDOMLY CHOOSE IF THE AI IS GOING TO BUY OR NOT

	
	int start = rand() % 2; //generates a random number between 0 and 1, 50% chance to start
	bool enoughMoney = true;

	if (start == 0) {
		cout << "The AI will play (Randomly decide to play)" << endl;
	}
	else {
		cout << "The AI will not play (Randomly decided not to play)" << endl;
	}

	while (enoughMoney && start == 0) {

		int houseCount = current_player->getHouseManager()->getHouseCount();

		//if player does not have enough elektro to purchase 1 house of 10 elektro
		if (!current_player->hasEnoughtElektroFor(10)) {
			cout << "Player " << current_player->getColor() << " You do not have enough elektro to place a house." << endl;
			enoughMoney = false;
			break;
		}

		//if player has no houses yet
		if (houseCount == 0) {
			cout << "You can build in these Cities:" << endl;

			//print free locations
			mapOfPlayersCity->printAvailableIndices();

			cout << "You currently have " << current_player->getElektro() << " elektro" << endl;

			vector<int> availableIndices = mapOfPlayersCity->getAvaiableIndices();
			int index;
			if (availableIndices.size() == 0)
			{
				index = rand() % 1; //generates a random number between 0 and size of available indices

			}
			else
				index = rand() % availableIndices.size(); //generates a random number between 0 and size of available indices

			House house(index, mapOfPlayersCity->getIndexName(index));

			current_player->subtractMoney(mapOfPlayersCity->costToBuildHouse(index));
			current_player->getHouseManager()->addHouses(house);
			mapOfPlayersCity->setPlayerHouse(index, current_player->getColor());
			cout << endl << "Map presentation: " << endl;
			mapOfPlayersCity->printPlayersCity();
			cout << endl << "Purchase completed" << endl;
			cout << "You now have " << current_player->getElektro() << " elektro" << endl;

			start = rand() % 2; //generates a random number between 0 and 1, 50% chance to start

			if (start == 0) {
				cout << "The AI will try to replay (after the first buy)" << endl;
			}
			else {
				cout << "The AI decided not to replay (after the first buy)" << endl;
			}
		}

		else {
			//if start == 0, then play, else don't play
			while (start == 0) {

				pair<vector<double>, vector<list<int>>> costAndPath = mapOfPlayersCity->getAvailableIndicesCost(current_player->getHouseManager()->getHouseIndices(), current_player->getElektro());
				vector<double> costVector = costAndPath.first;
				vector<list<int> > pathVector = costAndPath.second;

				//If there is no free city to put a house in
				if (costAndPath == pair<vector<double>, vector<list<int>>>()) {
					cout << "Player " << current_player->getColor() << "There is no city in that map that is free to play." << endl;
					enoughMoney = false;
					break;
				}

				else {
					cout << endl << "You currently have " << current_player->getElektro() << " elektro" << endl;
					cout << "These are the houses you can purchase: " << endl;

					//print indices
					mapOfPlayersCity->printAvailableIndicesCost(current_player->getHouseManager()->getHouseIndices(), current_player->getElektro());

					//I DID THE RANDOMLY GENERATED INDEX
					//Get input from the AI
					int RandIndex = rand() % costVector.size(); //generates a random number between 0 and size of available indices

					cout << "You are purchasing the house at Index " << RandIndex << endl;

					//Go from the shortest path and build houses that the player 
					//does not currently own and have an empty space
					for (int index : pathVector[RandIndex]) {

						//if the player does not currently own the house and the city is free to build then build house
						if (mapOfPlayersCity->playerOwnsHouseAndCityHasEmptySpace(current_player->getHouseManager()->getHouseIndices(), index)) {

							House house(index, mapOfPlayersCity->getIndexName(index)); //create house
							current_player->getHouseManager()->addHouses(house); //add house to player
							mapOfPlayersCity->setPlayerHouse(index, current_player->getColor()); //add house in map
							cout << "House index " << index << " name: " << mapOfPlayersCity->getIndexName(index) << " purchased" << endl;
						}

					}

					//Get cost of purchase of the index the player wants to purchase
					int costOfPurchase = (int)costVector[RandIndex];
					current_player->subtractMoney(costOfPurchase); //substract elektro

					cout << endl << "Map presentation: " << endl;
					mapOfPlayersCity->printPlayersCity();
					cout << endl << "Purchase completed" << endl;
					cout << "You now have " << current_player->getElektro() << " elektro" << endl;

					start = rand() % 2; //generates a random number between 0 and 1, 50% chance to start
					if (start == 0) {
						cout << "The AI will try to replay (already has house)" << endl;
					}
					else {
						cout << "The AI will not play (already has house)" << endl;
					}
				}
			}
		}

		//END OF PART 3
	}

}