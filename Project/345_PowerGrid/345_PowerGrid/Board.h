#pragma once
#include "Player.h"
#include "Map.h"
#include "MapOfPlayersCity.h"
#include "ResourceMarket.h"
#include <iostream>
using namespace std;

class Board{
public:
	Board();
	Board(std::vector<Player*> vector_player, Map * map);
	~Board();
	void setTurnCounter(int turnCounter);
	int getTurnCounter();
	void turnOrder();
	void buyPowerPlant();
	void buyRawMaterial();
	void building();
	void bureaucracy();
	void houseScoringTrack();
	void reorderPlayersHighestNumHouses();
	int getHighestNumHousesOfPlayers();
	int indexOfHighest(vector<Player*> vector, int index);
	void swapValues(Player& p1, Player& p2);
	void setStep3();
	int getNumberOfPlayers();

	int getPosition(string color) {

		for (int i = 0; i < getNumberOfPlayers(); i++) {
			if (vector_player[i]->getColor() == color)
				return i;
		}
		cout << "Not found" << endl; system("pause");
		return -2;
	}

	//prompt player to purchase index
	pair<int, int> pleaseChooseIndexToBuildIn(vector<list<int>> vectorListOfPaths);
	int pleaseChooseIndexToBuildIn();
	


	void loadGame();
	void saveGame();
	void incrementTurnCounter(); //TO BE REMOVED AFTER WE FINISH BUREACRACY!

	bool checkMapCorrectness();

private:
	int turnCounter;
	int nbOfPlayer = 0;
	std::vector<Player*> vector_player;
	PowerplantManager * powerplants_Vector;
	ResourceMarket * market;
	MapOfPlayersCity * mapOfPlayersCity;

	bool step2;
	bool step3;


	
	//Gets the next player. Used for auction
	Player * getNextPlayer(Player & p);
};

