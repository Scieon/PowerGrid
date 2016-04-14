#pragma once
#include "Player.h"
#include "Subject.h"
#include "Map.h"
#include "MapOfPlayersCity.h"
#include "ResourceMarket.h"
#include <iostream>


using namespace std;

class Board : public Subject{
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
	void reOrderHighestPlayerPwp();
	int indexOfHighestPwp(vector<Player*> vector, int startIndex);
	void swapValues(Player& p1, Player& p2);
	void setStep3();
	void setStep2();
	int getNumberOfPlayers();
	int getNumberOfPlayersThatHaveAucitoned();


	//prompt player to purchase index
	pair<int, int> pleaseChooseIndexToBuildIn(vector<list<int>> vectorListOfPaths);
	int pleaseChooseIndexToBuildIn();
	
	void incrementTurnCounter(); //TO BE REMOVED AFTER WE FINISH BUREACRACY!


	bool checkMapCorrectness();

	//general load/savegame
	void loadGame(string playerText, string areaText, string mapText, string powerplantText, string nbPlayerAndTurnText);
	void saveGame(string playerText, string areaText, string mapText, string powerplantText, string nbPlayerAndTurnText);
	//Save Game section
	void savePlayer(string);
	void loadPlayer(string);
	void saveMap(string, string);
	void loadMap(string, string);
	void savePowerplants(string);
	void loadPowerplants(string);
	void saveNbPlayerAndTurnCounter(string);
	void loadNbPlayersAndTurnCoutner(string);

	friend class BasicStatistics;
	friend class ElektrosStats;
	friend class ResourceStats;

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

