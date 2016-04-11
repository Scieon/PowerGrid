#include <iostream>
#include <string>

#include "House.h"
#include "Player.h"
#include "HouseManager.h"
#include "Resource.h"
#include "Board.h"
#include "ResourceMarket.h"
#include "Powerplant.h"
#include "IOFile.h"

using namespace std;

/* Testing for resource replenish
void pause() {
	system("pause");
	cout << endl << endl << endl;

}
int main() {

	ResourceMarket * r = new ResourceMarket();
	r->showInfo();

	string resource; int qty;
	cout << "Enter resource: ";
	cin >> resource;
	cout << "\nEnter Quantity: ";
	cin >> qty;


	r->updateMarket(resource, qty);
	pause();

	r->showInfo();
	pause();

	cout << endl << endl << endl;
	r->replenish(resource, 3);
	r->showInfo();

	system("pause");
}
*/

/* Testing for turnOrder() 
AreaManager * area_manager = new AreaManager();
	Map *gameMap = new Map(area_manager);
	std::vector<Player*> vector_player;
	Player* player1 = new Player("ROB");
	Player* player2 = new Player("DANVI");
	Player* player3 = new Player("KHOI");
	Powerplant* p1 = new Powerplant(3, "coal", 3, 2);
	Powerplant* p2 = new Powerplant(4, "coal", 3, 2);
	Powerplant* p3 = new Powerplant(5, "coal", 3, 2);
	player1->addPlant(p1);
	player2->addPlant(p2);
	player3->addPlant(p3);
	player1->getHouseManager()->setHouseCount(3);
	player2->getHouseManager()->setHouseCount(2);
	player3->getHouseManager()->setHouseCount(2);
	vector_player.push_back(player1);
	vector_player.push_back(player2);
	vector_player.push_back(player3);
	Board* b1 = new Board(vector_player, gameMap);
	b1->reorderPlayersHighestNumHouses();
	*/
	
int test() {
	
	int CHANGETHISFORTURNS = 4; //number of turns to play

	cout << "Welcome to Funkenschlag" << endl;


	string color;
	std::vector<Player*> vector_player;

	//Add the number of players in the vector collection
	for (int i = 1; i < 3; i++)
	{
		/*
		cout << "\nPlayer " << i << endl << "Please insert your color: ";
		cin >> color;
		Player* p = new Player(color);
		vector_player.push_back(p);

		*/
		Player* player1 = new Player("Red");
		

		Powerplant* p1 = new Powerplant(8, "Coal", 3, 2);
	
		Powerplant* pp1 = new Powerplant(12, "Hybrid", 2, 2);

		Powerplant* pp21 = new Powerplant(13, "Eco", 0, 1);
		player1->addResource("Coal", 6);
		player1->addResource("Oil", 6);
	

		player1->addPlant(p1);

		player1->addPlant(pp1);
		player1->addPlant(pp21);

		vector_player.push_back(player1);
	
	}

	//Now we have to get the areas played from players
	//create area and city manager
	AreaManager * area_manager = new AreaManager();
	vector<Area> * areas = new vector<Area>();

	//creating areas
	Area area1(1);
	Area area2(2);
	Area area3(3);

	//create areaVector
	areas->push_back(area1);
	areas->push_back(area2);
	areas->push_back(area3);



	//Set areas
	area_manager->setGameAreas(*areas);

	//Create game map according to areas
	Map * gameMap = new Map(area_manager); //do not delete

	Board * turn = new Board(vector_player, gameMap);

	//turns
	int y = 1;
	while (y < CHANGETHISFORTURNS) {


	

		//turn->turnOrder();
		//turn->buyPowerPlant();
		// turn->buyRawMaterial();
		//turn->building();

		turn->bureaucracy();
		turn->incrementTurnCounter(); //HAS BE REMOVED AFTER WE FINISH BUREACRACY


		y++;
	}

	return 0;
}


int main(){

	int CHANGETHISFORTURNS = 4; //number of turns to play

	cout << "Welcome to Funkenschlag" << endl;
	cout << "In order to enjoy the full experience, please make sure you make "
		<< endl << "the command prompt bigger than it's original size. Thank you." << endl << endl;
	cout << "//////////////////////////////////////////" << endl;
	cout << "///////// PLEASE READ CAREFULLY //////////" << endl;
	cout << "//////////////////////////////////////////" << endl << endl;

	cout << "Press \"y\" for a NEW GAME." << endl << endl;
	cout << "OTHERWISE type press any key to LOAD a SAVED game." << endl;
	
	string answer;
	cin >> answer;
	if (answer != "y") {
		//Load game
		Player* player1 = new Player("not");
		Player* player2 = new Player("important");
		std::vector<Player*> vector_player;
		vector_player.push_back(player1);
		vector_player.push_back(player2);
		IOFile::loadPlayer(*player1, *player2); //load players
		AreaManager * area_manager = new AreaManager(); //do not delete
		area_manager->setGameAreas(*IOFile::loadAreas()); //load areas
		Map *gameMap = new Map(area_manager); //load map

		Board * turn = new Board(vector_player, gameMap);

		turn->loadGame(); //loads map, pplants, resource market

		int y = 1;
		while (y<CHANGETHISFORTURNS) {
			turn->turnOrder();
			turn->buyPowerPlant();
			turn->buyRawMaterial();
			turn->building();
			//turn->bureaucracy();
			turn->incrementTurnCounter(); //HAS BE REMOVED AFTER WE FINISH BUREACRACY

			if (turn->checkMapCorrectness()) {
				cout << "Map is correct.... Saving game.... DONE!" << endl;
				turn->saveGame(); // map is correct..save game
			}

			y++;
		}
		return 0;
	}
	else {
		cout << "\nStarting new game..." << endl;
		
		// Beginning of Second Distinct Part

		int nbPlayers;
		string color;
		cout << "You can only play with 2 players. More player option coming soon" << endl;
		
		std::vector<Player*> vector_player;

		//Add the number of players in the vector collection
		for (int i = 1; i < 3; i++)
		{
			cout << "\nPlayer " << i << endl << "Please insert your color: ";
			cin >> color;
			Player* p = new Player(color);
			vector_player.push_back(p);
		}

		//Now we have to get the areas played from players
		//create area and city manager
		AreaManager * area_manager = new AreaManager();

		cout << "\nPlease enter the areas you want to play (3 integers). " 
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
			cout << "Area 1: ";
			cin >> a1;
			cout << "Area 2: ";
			cin >> a2;
			cout << "Area 3: ";
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
		Map * gameMap = new Map(area_manager); //do not delete

		Board * turn = new Board(vector_player, gameMap);
		
		//turns
		int y = 1;
		while (y<CHANGETHISFORTURNS) {
			turn->turnOrder();
			turn->buyPowerPlant();
			turn->buyRawMaterial();
			turn->building();
			//turn->bureaucracy();
			turn->incrementTurnCounter(); //HAS BE REMOVED AFTER WE FINISH BUREACRACY

			if (turn->checkMapCorrectness()) {
				cout << "Map is correct.... Saving game.... DONE!" << endl;
				turn->saveGame(); // map is correct..save game
			}

			y++;
		}
	}
	return 0;
}
