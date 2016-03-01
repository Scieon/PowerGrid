#include <iostream>
#include "Player.h"
#include "Powerplant.h"
#include "ResourceMarket.h"
#include "Resource.h"
#include "PowerplantManager.h"

using namespace std;

int main() {
	
	//Testing Resource Market
	ResourceMarket r1;
	r1.showInfo();

	cout << "blob" << endl;

	Player *p1 = new Player("Green");
	p1->showInfo();
	
	Player *p2 = new Player("Red");
	p2->showInfo();

	//Testing Player 1
	cout << "Adding 20 elektros  and four units of oil to player 1." << endl << endl;

	system("pause");
	p1->addElektros(20);
	p1->addResource("Coal", 4);
	p1->showInfo();
	cout << "Adding 10 elektros  and two units of Uranium to player 2." << endl <<"Adding two powerplants to player 2"  << endl<< endl;
	system("pause");

	//Testing Player 2

	p2->addElektros(10);
	p2->addResource("Uranium", 2);
	Powerplant oil3(3, "Oil", 2, 1);
	Powerplant coal20(20, "Coal", 3, 5);

	p2->addPlant(oil3);
	p2->addPlant(coal20);

	p2->showInfo();

	//Testing Player 2 Powerplants
	cout << "Displaying players 2 powerplant characteristics." << endl << endl;
	system("pause");

	p2->showPlants();


	cin.get();

	return 0;
}	
	