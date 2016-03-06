#include <iostream>
#include <string>

#include "House.h"
#include "Player.h"
#include "HouseManager.h"
#include "Resource.h"
#include "TurnSummary.h"
#include "ResourceMarket.h"

using namespace std;

int main(){
	Player* player1 = new Player("red");
	Player* player2 = new Player("blue");
	int nbPlayers;
	int i = 1;
	int y = 1;
	string color;


	ResourceMarket * r = new ResourceMarket();

	r->showInfo();

	system("pause");
	//Print the resources of the player 1

	player1->showInfo();


	//Print the resources of player 2
	player2->showInfo();

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
		Player* p = new Player(color, i);
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