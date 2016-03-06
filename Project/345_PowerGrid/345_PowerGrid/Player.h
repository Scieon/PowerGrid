#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "HouseManager.h"
#include "Resource.h"
#include "PowerPlantManager.h"
#include "Powerplant.h"
#include "ResourceManager.h"




using namespace std;

class Player{
public:
	Player(string);
	Player(string color, int electro, HouseManager *hm, Powerplant *pp, ResourceManager *rm);
	Player();
	~Player();
	void setColor(string color);
	void setElektro(int elektros);
	void subtractMoney(int elektros);
	string getColor();
	int getElektro();
   
	void showInfo();
	HouseManager* getHouseManager();

	//Power Plant methods added by Anhkhoi, feel free to modify
	void showPlants();

	void addPlant(Powerplant * p1); //incomplete "p2->addPlant(oil3);"
	void addResource(string type, int quantity); //Don't care about cost 
	int getResource(string type); //Return resource quantity


private:

	static int number_of_players;
	int playerNumber;
	int elektro;
	string color;
	HouseManager* houseManager;
	//Resource * resources[4]; 
	ResourceManager * resources;
	Powerplant * powerplants; //Players can have up to 3 power plants stored in an array of powerplants
	int numberOfPlants = 0;  //Counter for each player
	
};

#endif //PLAYER_H
