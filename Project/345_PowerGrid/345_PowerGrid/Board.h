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
	int pleaseChooseIndexToBuildIn(); //prompt player to purchase index
	void resourcePurchase(string materialType); //Not used for now

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


	
	//Gets the next player. Used for auction
	Player * getNextPlayer(Player & p);
};
