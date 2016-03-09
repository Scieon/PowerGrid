#include "ResourceMarket.h"
#include "ResourceManager.h"
#include "IOFile.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>


using namespace std;



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

//Destructor
ResourceMarket::~ResourceMarket() {

}


//Returns current cost of an valid quantity of a resource
int ResourceMarket::getMarketCost(string resource, int quantity) {

	if (quantity > this->getMarketQuantity(resource)) {
		cout << "The market does not have " << quantity << " units of " << resource << "!" << endl;
		return -1;
	}

	//The following are helpful counters for the functionality of the method
	int index = 0;
	int index1 = findPartial(resource); //-1 is everything is full or not empty
	int index2 = findEmpty(resource); //-1 if nothing is empty
	int counter = 0;
	bool insideIndex = true;

	//The cost of the resource
	int cost = 0;

	//The following two if statements allow us to start at the proper resource slot
	if (index1 != -1)
		index = index1;

	else if (index2 != -1)
		index = index2;

	//Looping through market to find cost the desired quantity
	//We require a rather convoluted setup because we do not want to make actual changes to the resource market
	while (quantity != 0) {
		insideIndex = true;
		int amountAtIndex = market[index + counter]->getResourceQuantity(resource);

		while (insideIndex) {

			if (amountAtIndex != 0) {
				cost += market[index + counter]->getResourceCost(resource); //Computing cost of 1 unit at that index
				quantity -= 1; //Getting the cost of 1 resource at a time
				amountAtIndex--;

				if (quantity == 0)
					return cost;
			}
			else {
				counter++; //Move to next slot
				insideIndex = false; //No longer inside current slot
			}
		} //End of inner while

	}//End of while
	return cost;

}

//Removes resources purchased by players during phase 3
void ResourceMarket::updateMarket(string resource, int quantity) {

	for (int i = 0; i <= 11; i++) {

		while (market[i]->getResourceQuantity(resource) != 0) {
			market[i]->removeOneUnit(resource);
			quantity--;
			if (quantity == 0)
				break;
		}
		if (quantity == 0)
			break;
	}

}

//void removeOneUnit(string resource); //Removes one unit of any resource at any index
void ResourceMarket::removeOneUnit(string resource) {

}

//Return total quantity of resource in market
int ResourceMarket::getMarketQuantity(string resource) {

	int amount_in_market = 0;

	for (int i = 0; i <= 11; i++) {
		amount_in_market += market[i]->getResourceQuantity(resource);
	}
	return amount_in_market;
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

void ResourceMarket::saveMarket() {

	ofstream output;

	//  Open existing file resourcemarket.txt or create a new file
	output.open("resourcemarket.txt");
	cout << "Saving ResourceMarket" << endl;

	// Loops through the ResourceMarket array and saves only the quantities to the .txt
	for (int i = 0; i <= 11; i++) {
		output << 
			market[i]->getResourceQuantity("Coal") << "  " <<
			market[i]->getResourceQuantity("Oil") << "  " <<
			market[i]->getResourceQuantity("Garbage") << "  " <<
			market[i]->getResourceQuantity("Uranium") << "  " << endl;
	}

	output.close();

	cout << "\nResourceMarket Saved!" << endl << endl;

}
void ResourceMarket::loadMarket() {

	int coal_amt,oil_amt,garbage_amt,uranium_amt,i=0,k = 10;
	

	// Opening "resourcemarket.txt"
	ifstream input("resourcemarket.txt");

	cout << "Loading ResourceMarket" << endl << "-------------------------" << endl;

	// Reads each int one by one in line (left to right) coal->oil->garbage->uranium...nextline
	while (input >> coal_amt >> oil_amt >> garbage_amt >> uranium_amt) {


		if (i < 8) {

			market[i]->edit("Coal", coal_amt, i + 1);
			market[i]->edit("Oil", oil_amt, i + 1);
			market[i]->edit("Garbage", garbage_amt, i + 1);
			market[i]->edit("Uranium", uranium_amt, i + 1);
		}
			
	
		// Handles prices 10,12,14,16
		if (i >= 8) {
			
			market[i]->edit("Coal", coal_amt, k);
			market[i]->edit("Oil", oil_amt, k);
			market[i]->edit("Garbage", garbage_amt, k);
			market[i]->edit("Uranium", uranium_amt, k);
			k = k + 2;
		}
			i++;

		/*
		// IGNORE:: checking if right amounts are implemented
			cout << "Coal" << coal_amt << endl;
			cout << "Oil" << oil_amt << endl;
			cout << "Garbage" << garbage_amt << endl;
			cout << "Uranium" << uranium_amt << endl;
			cout << i << endl;
			i++;
		*/
	}
}


void ResourceMarket::showInfo() {

	for (int i = 0; i <= 11; i++) {

		cout << "Slot[" << i << "]: " << "Coal, Oil, Garbage, Uranium" << endl << "Quantity: " <<
			market[i]->getResourceQuantity("Coal") << ",  " <<
			market[i]->getResourceQuantity("Oil") << ",  " <<
			market[i]->getResourceQuantity("Garbage") << ",  " <<
			market[i]->getResourceQuantity("Uranium") << "  " << endl << "Price: " << market[i]->getResourceCost("Uranium") << endl << endl;
	}

}

