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

	



	/*
	//----------------- -Resourcemarketsave Test ------------------//
	// To test first alter the resourcemarket.txt file to any value between 0-9 for quantities.

	// test shows default table --> loads altered market --> updates market quantities 
	// --> saves market --> alters market again --> loads previous market 
	// -->> displays previous market


	ResourceMarket  * r1 = new ResourceMarket();

	r1->saveMarket();
	r1->showInfo();	
	r1->loadMarket(); 

	r1->showInfo(); 

	system("pause");
		
	r1->updateMarket("Oil", 3); 
	
	r1->saveMarket();
	
	cout << "-----" << endl;
	r1->showInfo();

	r1->updateMarket("Uranium", 2);

	cout << "------" << endl;
	r1->showInfo();

	system("pause");


	

	r1->loadMarket();
	cout << "-----" << endl;
	r1->showInfo();

	system("pause");
	

	//-------------- END OF RESOURCE MARKET SAVE Test ------------------//
	*/

	cout << "Welcome to Funkenschlag" << endl;
	cout << "Type \"yes\" then press Enter to load a game or press any key and Enter to start a new game.   ";
	string answer;
	cin >> answer;
	if (answer == "yes") {
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

		TurnSummary * turn = new TurnSummary(vector_player, gameMap);

		turn->loadGame(); //loads map, pplants, resource market

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
		Map * gameMap = new Map(area_manager); //do not delete

		TurnSummary * turn = new TurnSummary(vector_player, gameMap);
		
		//turns
		int y = 1;
		while (y<4) {
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
}
