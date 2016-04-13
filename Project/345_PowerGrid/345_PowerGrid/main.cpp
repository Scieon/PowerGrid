#include <iostream>
#include <string>

#include "House.h"
#include "Player.h"
#include "HouseManager.h"
#include "Resource.h"
#include "Board.h"
#include "ResourceMarket.h"
#include "Powerplant.h"
#include "BoardBuilder.h"
#include "NormalGameBuilder.h"
#include "GameLoaderSaver.h"
#include "BasicStatistics.h"
#include "ElektrosStats.h"
#include "ResourceStats.h"

using namespace std;



int main(){

	int CHANGETHISFORTURNS = 100; //number of turns to play

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
		Board * turn = new Board();


		GameLoaderSaver gameLoaderSaver; //director
		NormalGameBuilder* normalGame = new NormalGameBuilder;
		gameLoaderSaver.setGameBuilder(normalGame);
		gameLoaderSaver.loadBoard(); //load board in builder pattern
	    turn = gameLoaderSaver.getBoard();
		

		turn->loadGame(); //loads map, pplants, resource market

		int y = 1;
		while (y<CHANGETHISFORTURNS) {
			turn->turnOrder();
			turn->buyPowerPlant();
			turn->buyRawMaterial();
			turn->building();
			//turn->bureaucracy();
			turn->incrementTurnCounter(); 

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

		do {
			cout << "How many players would like to play the game? (2-3): ";
			cin >> nbPlayers;
		} while (nbPlayers != 2 && nbPlayers != 3);

		string stats = "";
		do {
			cout << "Would you like to log game statistics during the game? (y/n): "; 
			cin >> stats;
		} while (stats != "y" && stats != "n");

		
		
		std::vector<Player*> vector_player;

		//Add the number of players in the vector collection
		for (int i = 1; i < nbPlayers+1; i++)
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
		
		if (stats == "y") {

			Statistics * b1 = new BasicStatistics(turn);
			b1 = new ElektrosStats(b1);
			b1 = new ResourceStats(b1);

		}
		//turns
		int y = 1;
		while (y<CHANGETHISFORTURNS) {
			turn->turnOrder();
			turn->buyPowerPlant();
			turn->buyRawMaterial();
			turn->building();
			turn->bureaucracy();
			turn->incrementTurnCounter(); 

			if (turn->checkMapCorrectness()) {
				cout << "Map is correct.... Saving game.... DONE!" << endl;
				turn->saveGame(); // map is correct..save game
			}

			y++;
		}
	}
	return 0;
}
