#include <iostream>
#include <string>

#include "House.h"
#include "Player.h"
#include "HouseManager.h"
#include "Resource.h"
#include "TurnSummary.h"
#include "ResourceMarket.h"
#include "Powerplant.h"
#include "IOFile.h"

using namespace std;

int main(){
	Player* player1 = new Player("red");
	Player* player2 = new Player("blue");
	int nbPlayers;
	int i = 1;
	int y = 1;
	string color;


	//--------------TESTING FOR RESOURCE MARKET PHASE 3 ------------------------------------/

	ResourceMarket * r = new ResourceMarket();
	Powerplant * coal4 = new Powerplant(4, "Coal", 3, 1); //(int min_bid, string resource_type, int resources_required, int num_cities_powered) 
	Powerplant * oil3 = new Powerplant(3, "Garbage", 2, 1);
	Powerplant * hybrid5 = new Powerplant (5, "Hybrid", 3, 1);
	//r->showInfo();

	
	player1->addPlant(coal4);
	player1->addPlant(oil3);
	player1->addPlant(hybrid5);
	player1->showPlants();

	//cout << player1->getTotalStorage() << endl;
	cout << player1->getResourceStorage("Coal") << endl;
	player1->validateResourcePurchase(33, 8,"Coal"); //(cost,quantity,type);

	system("pause");
	//Print the resources of the player 1

	player1->showInfo();

	system("pause");

	player1->validateResourcePurchase(16, 4, "Coal"); //(cost,quantity,type);

	player1->showInfo();

	system("pause");


	//Print the resources of player 2
	player2->showInfo();
	
	//Testing house save start
	House h1(0, "Seattle");
	House h2(1, "Portland");

	player1->getHouseManager()->addHouses(h1);
	player1->getHouseManager()->addHouses(h2);

	IOFile::savePlayer(*player1, *player2);
	//Testing house save end

	system("pause");
	

	//-------------- END OF TEST ------------------------------------/


	/*
	// Beginning of Second Distinct Part
	cout << "How many players will there be?" << endl;
	cin >> nbPlayers;
	std::vector<Player*> vector_player;

	//Add the number of players in the vector collection
	while (i < nbPlayers+1)
	{
		cout << "Insert the player color: " << endl;
		cin >> color;
		Player* p = new Player(color);
		vector_player.push_back(p);
		i++;
	}

	for (Player * p : vector_player)
	{
		cout <<"Here is the color of player " << p->getColor() << endl;
	}
	*/

	std::vector<Player*> vector_player;
	vector_player.push_back(player1);
	vector_player.push_back(player2);

	TurnSummary * turn = new TurnSummary(vector_player);
	while (y<4){
		//turn->turnOrder();
		//turn->buyPowerPlant();
		turn->buyRawMaterial();
		//turn->building();
		//turn->bureaucracy();
		y++;
	}
	
	
	cin.get();
	return 0;
}