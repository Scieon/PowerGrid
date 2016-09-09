#include "ResourceMarket.h"

//Default constructor setting up arbitrary cost values for the four resources in the game
ResourceMarket::ResourceMarket() {

	this->coal = Coal(20);
	this->oil = Oil(15);
	this->garbage = Garbage(10);
	this->uranium = Uranium(5);
}

//Destructor
ResourceMarket::~ResourceMarket() {

}

//Helper function that displays each resources characteristics
void ResourceMarket::showInfo() {

	cout << "Resource Market" << endl << endl;
	cout << coal.getType() << " quantity = " << coal.getQuantity() << ", Color: " <<coal.getColor() << " , cost = " << coal.getCost() <<" elektros"<< endl;
	cout << oil.getType() << " quantity = " << oil.getQuantity() << ", Color: " << oil.getColor() << " , cost = " << oil.getCost() << " elektros" <<endl;
	cout << garbage.getType() << " quantity = " << garbage.getQuantity() << ", Color: " << garbage.getColor() << " , cost = " << garbage.getCost() << " elektros"<< endl;
	cout << uranium.getType() << " quantity = " << uranium.getQuantity() << ", Color: " << uranium.getColor() << " , cost = " << uranium.getCost() << " elektros"<< endl;
}

