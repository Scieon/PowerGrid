#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Resource.h"
#include "House.h"
#include "Coal.h"
#include "Oil.h"
#include "Garbage.h"
#include "Uranium.h"
#include "Powerplant.h"

using std::string;


class Player {


public:

	Player();
	Player(string color);
	~Player();
	void showInfo() const;;
	int getElektros() const;
	void setElektros(int elektros);
	void addElektros(int elektros);

	void showPlants();
	void addResource(string type, int quantity);
	void addPlant(Powerplant p1);

	


private:
	static int number_of_players;
	int elektros; //Player's currency
	Resource *resources[4]; //Each player has four resources allocated in a resource array
	House houses; //Each player has house objects
	Powerplant powerplants[3]; //Players can have up to 3 power plants stored in an array
	int numberOfPlants = 0; 

};





#endif