#include "ResourceMarket.h"
#include "ResourceManager.h"


//Resource Market intializes game resources according to rules
ResourceMarket::ResourceMarket() {
	market[0] = new ResourceManager();
	market[0]->edit("Coal", 3, 1); //edit(type,quantity,cost)
	market[0]->edit("Oil", 0, 1);
	market[0]->edit("Garbage", 0, 1);
	market[0]->edit("Uranium", 0, 1);


	market[1] = new ResourceManager();
	market[1]->edit("Coal", 3, 2);
	market[1]->edit("Oil", 0, 2);
	market[1]->edit("Garbage", 0, 2);
	market[1]->edit("Uranium", 0, 2);

	market[2] = new ResourceManager();
	market[2]->edit("Coal", 3, 3);
	market[2]->edit("Oil", 3, 3);
	market[2]->edit("Garbage", 0, 3);
	market[2]->edit("Uranium", 0, 3);

	market[3] = new ResourceManager();
	market[3]->edit("Coal", 3, 4);
	market[3]->edit("Oil", 3, 4);
	market[3]->edit("Garbage", 0, 4);
	market[3]->edit("Uranium", 0, 4);


	market[4] = new ResourceManager();
	market[4]->edit("Coal", 3, 5);
	market[4]->edit("Oil", 3, 5);
	market[4]->edit("Garbage", 0, 5);
	market[4]->edit("Uranium", 0, 5);

	market[5] = new ResourceManager();
	market[5]->edit("Coal", 3, 6);
	market[5]->edit("Oil", 3, 6);
	market[5]->edit("Garbage", 0, 6);
	market[5]->edit("Uranium", 0, 6);


	market[6] = new ResourceManager();
	market[6]->edit("Coal", 3, 7);
	market[6]->edit("Oil", 3, 7);
	market[6]->edit("Garbage", 3, 7);
	market[6]->edit("Uranium", 0, 7);


	market[7] = new ResourceManager();
	market[7]->edit("Coal", 3, 8);
	market[7]->edit("Oil", 3, 8);
	market[7]->edit("Garbage", 3, 8);
	market[7]->edit("Uranium", 0, 8);

	//Just Uranium from here on
	market[8] = new ResourceManager();
	market[8]->edit("Uranium", 0, 10);

	market[9] = new ResourceManager();
	market[9]->edit("Uranium", 0, 12);

	market[10] = new ResourceManager();
	market[10]->edit("Uranium", 1, 14);

	market[11] = new ResourceManager();
	market[11]->edit("Uranium", 1, 16);

}

//Calls the replenish method accordingly
//Replenish is helper method for this function
void ResourceMarket::refill(int step, int players) {


	switch (players) {

	case 2:
		if (step == 1) {

			// Replenish("Coal",3);
			// Replenish("Oil",2);
			// Replenish("Garbage,1);
			// Replenish("Uranium,1);
		
		}

		if (step == 2) {
			//Do refill right to left
		}

		if (step == 3) {

		}

		else if (step != 1 && step != 2 && step != 3) {
			cout << "Error not step 1,2,3" << endl;
			system("pause");
		}

		break;
		
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;

	default:
		cout << "Error number of players" << endl;
		system("pause");

	}


}

//Replenish resources at any quantity
void ResourceMarket::replenish(string resource, int quantity) {

	//Quantity could be 9 should loop until quantity = 0 storing resources accordingly
	int emptyCoal = this->findEmpty("Coal");
	int emptyOil = this->findEmpty("Oil");
	int emptyGarbage = this->findEmpty("Garbage");
	int emptyUranium = this->findEmpty("Uranium");

	int partialCoal = this->findPartial("Coal");
	int partialOil = this->findPartial("Oil");
	int partialGarbage = this->findPartial("Garbage");

	/*
	if (emptyCoal != -1) {
		market[emptyCoal]->edit("Coal", 3, emptyCoal + 1); //(Coal,qty,cost)
	}

	if (emptyOil != -1) {
		market[emptyOil]->edit("Oil", 2, emptyOil + 1);
	}

	if (emptyGarbage != -1) {
		market[emptyGarbage]->edit("Garbage", 1, emptyGarbage + 1);
	}

	if (partialCoal != -1) {

		//Case 1 : Market index has 2 Coal
		if (market[partialCoal]->getResourceQuantity("Coal") == 2) {
			market[partialCoal]->edit("Coal", 3, partialCoal + 1); //Add one more
			if (partialCoal != 0)
				market[partialCoal - 1]->edit("Coal", 2, partialCoal); //Add remaining 2
		}

		//Case 2 : Market index has 1 Coal
		if (market[partialCoal]->getResourceQuantity("Coal") == 1) {
			market[partialCoal]->edit("Coal", 3, partialCoal + 1); //Add 2 more
			if (partialCoal != 0)
				market[partialCoal - 1]->edit("Coal", 1, partialCoal); //Add remaining 1
		}

	}
	
	Do 2 cases for garbage and oil

	*/
}

//Return -1 if no empty cells
int ResourceMarket::findEmpty(string resource) {

	int i = 11;
	if (resource == "Oil" || resource == "Coal" || resource == "Garbage")
		i = 7;

	for (i; i >= 0; i--) {

		//If index has empty "Resource" 
		if (market[i]->getResourceQuantity(resource) == 0) {
			return i;
		}
	}

	return -1;
}

//Should not use this function for Uranium
//Returns index with partial amount of resources
int ResourceMarket::findPartial(string resource) {

	if (resource == "Uranium")
		return findEmpty("Uranium");

	for (int i = 7; i >= 0; i--) {

		//If index is not full
		if (market[i]->getResourceQuantity(resource) == 1 || market[i]->getResourceQuantity(resource) == 2) {
			return i;
		}
	}

	return -1;
}



//Destructor
ResourceMarket::~ResourceMarket() {


}


void ResourceMarket::showInfo() {

	for (int i = 0; i <= 11; i++) {
		
		 cout << "Slot[" << i << "]: " << "Coal, Oil, Garbage, Uranium" << endl << "Quantity: " <<
			 market[i]->getResourceQuantity("Coal") <<",  "<< 
			 market[i]->getResourceQuantity("Oil") << ",  " << 
			 market[i]->getResourceQuantity("Garbage") << ",  " <<
			 market[i]->getResourceQuantity("Uranium") << "  " <<  endl << "Price: " << market[i]->getResourceCost("Uranium") << endl << endl;
	}

}

