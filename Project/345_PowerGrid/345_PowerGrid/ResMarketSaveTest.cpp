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
	

}
*/