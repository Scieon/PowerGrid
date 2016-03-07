#ifndef TURNSUMMARY_H
#define TURNSUMMARY_H
#include "Player.h"
#include "Map.h"
#include "MapOfPlayersCity.h"
#include <iostream>
using namespace std;

class TurnSummary{
public:
	TurnSummary();
	TurnSummary(std::vector<Player*> vector_player, Map * map);
	~TurnSummary();
	void setTurnCounter(int turnCounter);
	int getTurnCounter();
	void turnOrder();
	void buyPowerPlant();
	void buyRawMaterial();
	void building();
	void bureaucracy();

	

	


private:
	int turnCounter;
	int nbOfPlayer = 0;
	std::vector<Player*> vector_player;
	PowerplantManager * powerplants_Vector;
	Map * map;
	MapOfPlayersCity * mapOfPlayersCity;


	

	Player * getNextPlayer(Player & p);
};

#endif //TURNSUMMARY_H