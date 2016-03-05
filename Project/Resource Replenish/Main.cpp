#include <iostream>
#include "Player.h"
#include "Powerplant.h"
#include "ResourceMarket.h"
#include "Resource.h"
#include "PowerplantManager.h"

using namespace std;

int main() {
	
	
	ResourceMarket * market = new ResourceMarket();

	//cout << market->findEmpty("Coal") << endl;
//	market->refill(1, 2);
//	cout << market->findEmpty("Coal") << endl;

	market->showInfo("Garbage");
	cin.get();

	return 0;
}	
	