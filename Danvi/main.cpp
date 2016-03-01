#include <iostream>
#include <string>

#include "House.h"
#include "Player.h"
#include "HouseManager.h"
#include "Resource.h"
#include "TurnSummary.h"

using namespace std;

int main(){
	Player* player1 = new Player("red", 1);
	Player* player2 = new Player("blue", 2);
	int nbPlayers;
	int i = 1;
	int y = 1;
	string color;

	//Print the resources of the player 1
	cout << "Here is the player 1 resources:" << endl;
	cout << "P1 Money:" << player1->getMoney() << endl;
	cout << "P1 Resource Uranium: " << player1->getResources()->getUranium() << endl;
	cout << "P1 Resource Garbage: " << player1->getResources()->getGarbage() << endl;
	cout << "P1 Resource Coal: " << player1->getResources()->getCoal() << endl;
	cout << "P1 Resource Oil: " << player1->getResources()->getOil() << endl;
	player1->getResources()->setOil(50);
	cout << "P1 Setting 50 into oil " << player1->getResources()->getOil()<< endl << endl;

	//Print the resources of player 2
	cout << "Here is the player 2 resources:" << endl;
	cout << "P2 Money:" << player2->getMoney() << endl;
	cout << "P2 Resource Uranium: " << player2->getResources()->getUranium() << endl;
	cout << "P2 Resource Garbage: " << player2->getResources()->getGarbage() << endl;
	cout << "P2 Resource Coal: " << player2->getResources()->getCoal() << endl;
	cout << "P2 Resource Oil: " << player2->getResources()->getOil() << endl << endl;

	/* Beginning of Second Distinct Part*/
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

	TurnSummary * turn = new TurnSummary(vector_player);
	while (y<4){
		turn->turnOrder();
		turn->buyPowerPlant();
		turn->buyRawMaterial();
		turn->building();
		turn->bureaucracy();
		y++;
	}
	
	//Destruct them
	delete turn;
	delete player1;
	delete player2;
	
	//Fake system pause
	char hello;
	cin >> hello;
	return 0;
}