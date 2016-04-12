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
	void setStep2();
	int getNumberOfPlayers();

	//prompt player to purchase index
	pair<int, int> pleaseChooseIndexToBuildIn(vector<list<int>> vectorListOfPaths);
	int pleaseChooseIndexToBuildIn();
	
	void incrementTurnCounter(); //TO BE REMOVED AFTER WE FINISH BUREACRACY!


	bool checkMapCorrectness();

	//general load/savegame
	void loadGame();
	void saveGame();
	//Save Game section
	void savePlayer();
	void loadPlayer();
	void saveMap();
	void loadMap();
	void savePowerplants();
	void loadPowerplants();
	void saveNbPlayerAndTurnCounter();
	void loadNbPlayersAndTurnCoutner();

private:
	int turnCounter;
	int nbOfPlayer = 0;
	std::vector<Player*> vector_player;
	PowerplantManager * powerplants_Vector;
	ResourceMarket * market;
	MapOfPlayersCity * mapOfPlayersCity;

	bool step2;
	bool step3;
	bool endGameTriggered = false;


	
	//Gets the next player. Used for auction
	Player * getNextPlayer(Player & p);
};

