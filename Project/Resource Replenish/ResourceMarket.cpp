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
	market[1]->edit("Garbage",0, 2);
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

void ResourceMarket::refill(int step, int players) {


	switch (players) {

	case 2:
		if (step == 1) {
			int emptyCoal = this->findEmpty("Coal");
			int emptyOil = this->findEmpty("Oil");
			int emptyGarbage = this->findEmpty("Garbage");
			int emptyUranium = this->findEmpty("Uranium");


			market[emptyCoal]->edit("Coal", 3, emptyCoal + 1); //Condition if emptyCoal != 1
			market[emptyUranium]->edit("Uranium", 1, emptyUranium + 1);
		}

		if (step == 2) {
			//Do refill right to left
		}

		if (step == 3) {
			int emptyCoal = this->findEmpty("Coal");
			int emptyOil = this->findEmpty("Oil");
			int emptyGarbage = this->findEmpty("Garbage");
			int emptyUranium = this->findEmpty("Uranium");

			market[emptyCoal]->edit("Coal", 3, emptyCoal + 1);
		}

		else if (step != 1 && step != 2 && step != 3){
			cout << "Error not step 1,2,3" << endl;
			system("pause");
		}

		break;
		//For final build
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


//Destructor
ResourceMarket::~ResourceMarket() {


}

//Enter resource i.e, Coal,Oil,Garbage,Uranium to see market info
void ResourceMarket::showInfo(string resource) {
	
	for (int i = 0; i <= 11; i++) {
		cout << "Slot[" <<i+1<<"]: "<< resource << endl << "Quantity: " << market[i]->getResourceQuantity(resource) << endl << "Price: " << market[i]->getResourceCost(resource) << endl << endl;
		
	}

}

