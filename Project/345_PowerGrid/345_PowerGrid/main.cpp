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

	

	/*/--------------TESTING FOR RESOURCE MARKET PHASE 3 ------------------------------------/

	Player* player1 = new Player("red");

	ResourceMarket * r = new ResourceMarket();
	Powerplant * coal4 = new Powerplant(4, "Coal", 3, 1); //(int min_bid, string resource_type, int resources_required, int num_cities_powered) 
	Powerplant * oil3 = new Powerplant(3, "Garbage", 2, 1);
	Powerplant * hybrid5 = new Powerplant(5, "Hybrid", 3, 1);
	r->showInfo();
	//cout << endl << "Amount: " << r->getMarketQuantity("Garbage") << endl;


	player1->addPlant(coal4);
	player1->addPlant(oil3);
	player1->addPlant(hybrid5);
	//player1->showPlants();

	//cout << player1->getTotalStorage() << endl;
	//cout << player1->getResourceStorage("Coal") << endl;
	player1->validateResourcePurchase(33, 8, "Coal"); //(cost,quantity,type);
	player1->showInfo();
	
	string type;
	int q;

	cin >> type >> q;
	r->updateMarket(type, q);
	r->showInfo();
	//cout << "Cost: " << r->getMarketCost("Coal", 7) << endl;
	//cout << "Cost: " << r->getMarketCost("Uranium", 2)<< endl;
	//cout << "Cost: " << r->getMarketCost("Uranium", 1) << endl;


	cin.get();
	//-------------- END OF TEST ------------------------------------/





	/*
	When asked for areas you can simply type 1,2,3
	*/
	
	
	cout << "Welcome to Funkenschlag" << endl;
	cout << "Do you want to load a game? Type \"yes\" if so" << endl;
	string answer;
	cin >> answer;
	if (answer == "yes") {
		//Load game


		return 0;
	}
	else {
		cout << "Starting new game..." << endl;
		
		// Beginning of Second Distinct Part

		int nbPlayers;
		string color;
		cout << "You can only play with 2 players. More player option coming soon" << endl;
		
		std::vector<Player*> vector_player;

		//Add the number of players in the vector collection
		for (int i = 1; i < 3; i++)
		{
			cout << "Player " << i << endl << "Please insert your color: ";
			cin >> color;
			Player* p = new Player(color);
			vector_player.push_back(p);
		}

		//Now we have to get the areas played from players
		//create area and city manager
		AreaManager * area_manager = new AreaManager();
		CityManager * cityManager = new CityManager();

		cout << "Please enter the areas you want to play (3 integers). " 
			<< "See image for details." 
			<< endl 
			<< "The areas must be connected..."
			<< endl;
		int a1;
		int a2;
		int a3;
		vector<Area> * areas = new vector<Area>();
		int count = 0;

		//do while loop
		//Checking if areas are possible
		do {
			if (count != 0) {
				cout << "This is an impossible game. Please try again. Check image for details." << endl;
				areas->clear();
			}
			cin >> a1;
			cin >> a2;
			cin >> a3;

			//creating areas
			Area area1(a1);
			Area area2(a2);
			Area area3(a3);

			//create areaVector
			areas->push_back(area1);
			areas->push_back(area2);
			areas->push_back(area3);
			count++;
		}
		while (!area_manager->areAdjacent(*areas));


		//Set areas
		area_manager->setGameAreas(*areas);
		
		//Create game map according to areas
		Map * gameMap = new Map(area_manager, cityManager); //do not delete

		TurnSummary * turn = new TurnSummary(vector_player, gameMap);
		
		//turns
		int y = 1;
		while (y<4) {
			//turn->turnOrder();
			//turn->buyPowerPlant();
			//turn->buyRawMaterial();
			turn->building();
			//turn->bureaucracy();
			y++;
		}
		return 0;
	} 
	/*
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
/*
	std::vector<Player*> vector_player;
	vector_player.push_back(player1);
	vector_player.push_back(player2);

	TurnSummary * turn = new TurnSummary(vector_player, gameMap);
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
	*/

}