/*
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


int main() {

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
	int a1 = 0;
	int a2 = 1;
	int a3 = 2;
	vector<Area> * areas = new vector<Area>();
	

		//creating areas
		Area area1(a1);
		Area area2(a2);
		Area area3(a3);

		//create areaVector
		areas->push_back(area1);
		areas->push_back(area2);
		areas->push_back(area3);


	//Set areas
	area_manager->setGameAreas(*areas);

	//Create game map according to areas
	Map * gameMap = new Map(area_manager); //do not delete

	Board * turn = new Board(vector_player, gameMap);

	std::vector<double> min_distance;
	std::vector<int> previous;
	gameMap->DijkstraComputePaths(0, *(gameMap->getMap()), min_distance, previous);
	std::cout << "Distance from 0 to 20: " << min_distance[20] << std::endl;
	std::list<int> path = gameMap->DijkstraGetShortestPathTo(20, previous);
	std::cout << "Path : ";
	std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	system("pause");

}
*/