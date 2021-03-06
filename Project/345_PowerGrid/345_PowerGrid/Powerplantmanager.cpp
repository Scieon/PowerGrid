#include "PowerplantManager.h"
#include "Powerplant.h"
#include <vector>
#include <algorithm> // std::random_shuffle
#include <ctime> // std::time()
#include <iostream>

using namespace std;

//Default constructor initializing all possible power plants
PowerplantManager::PowerplantManager() {

	Powerplant coal4(4, "Coal", 2, 1); //(int min_bid, string resource_type, int resources_required, int num_cities_powered);
	Powerplant coal8(8, "Coal", 3, 2);
	Powerplant coal10(10, "Coal", 2, 2);
	Powerplant coal15(15, "Coal", 2, 3);
	Powerplant coal20(20, "Coal", 3, 5);
	Powerplant coal25(25, "Coal", 2, 5);
	Powerplant coal31(31, "Coal", 3, 6);
	Powerplant coal36(36, "Coal", 3, 7);
	Powerplant coal42(42, "Coal", 2, 6);

	Powerplant oil3(3, "Oil", 2, 1);
	Powerplant oil7(7, "Oil", 3, 2);
	Powerplant oil9(9, "Oil", 1, 1);
	Powerplant oil16(16, "Oil", 2, 3);
	Powerplant oil26(26, "Oil", 2, 5);
	Powerplant oil32(32, "Oil", 3, 6);
	Powerplant oil35(35, "Oil", 1, 5);
	Powerplant oil40(40, "Oil", 2, 6);

	Powerplant hybrid5(5, "Hybrid", 2, 1);
	Powerplant hybrid12(12, "Hybrid", 2, 2);
	Powerplant hybrid21(21, "Hybrid", 2, 4);
	Powerplant hybrid29(29, "Hybrid", 1, 4);
	Powerplant hybrid46(46, "Hybrid", 3, 7);

	Powerplant garbage6(6, "Garbage", 1, 1);
	Powerplant garbage14(14, "Garbage", 2, 2);
	Powerplant garbage19(19, "Garbage", 2, 3);
	Powerplant garbage24(24, "Garbage", 2, 4);
	Powerplant garbage30(30, "Garbage", 3, 6);
	Powerplant garbage38(38, "Garbage", 3, 7);

	Powerplant uranium11(11, "Uranium", 1, 1);
	Powerplant uranium17(17, "Uranium", 1, 2);
	Powerplant uranium23(23, "Uranium", 1, 3);
	Powerplant uranium28(28, "Uranium", 1, 4);
	Powerplant uranium34(34, "Uranium", 1, 5);
	Powerplant uranium39(39, "Uranium", 1, 6);

	Powerplant eco13(13, "Eco", 0, 1);
	Powerplant eco18(18, "Eco", 0, 2);
	Powerplant eco22(22, "Eco", 0, 2);
	Powerplant eco27(27, "Eco", 0, 3);
	Powerplant eco33(33, "Eco", 0, 4);
	Powerplant eco37(37, "Eco", 0, 4);
	Powerplant eco44(44, "Eco", 0, 5);
	Powerplant eco50(50, "Eco", 0, 6);

	Powerplant step3(-1, "Step_3", -1, -1);


	powerplantsVector = new vector<Powerplant>();

	//Powerplant Start
	powerplantsVector->push_back(oil3);
	powerplantsVector->push_back(coal4);
	powerplantsVector->push_back(hybrid5);
	powerplantsVector->push_back(garbage6);
	powerplantsVector->push_back(oil7);
	powerplantsVector->push_back(coal8);
	powerplantsVector->push_back(oil9);
	powerplantsVector->push_back(coal10);
	powerplantsVector->push_back(eco13);

	//Powerplant deck
	powerplantsVector->push_back(coal15);
	powerplantsVector->push_back(coal20);
	powerplantsVector->push_back(coal25);
	powerplantsVector->push_back(coal31);
	powerplantsVector->push_back(coal36);
	powerplantsVector->push_back(coal42);

	powerplantsVector->push_back(oil16);
	powerplantsVector->push_back(oil26);
	powerplantsVector->push_back(oil32);
	powerplantsVector->push_back(oil35);
	powerplantsVector->push_back(oil40);

	powerplantsVector->push_back(hybrid12);
	powerplantsVector->push_back(hybrid21);
	powerplantsVector->push_back(hybrid29);
	powerplantsVector->push_back(hybrid46);

	powerplantsVector->push_back(garbage14);
	powerplantsVector->push_back(garbage19);
	powerplantsVector->push_back(garbage24);
	powerplantsVector->push_back(garbage30);
	powerplantsVector->push_back(garbage38);

	powerplantsVector->push_back(uranium11);
	powerplantsVector->push_back(uranium17);
	powerplantsVector->push_back(uranium23);
	powerplantsVector->push_back(uranium28);
	powerplantsVector->push_back(uranium34);
	powerplantsVector->push_back(uranium39);

	powerplantsVector->push_back(eco18);
	powerplantsVector->push_back(eco22);
	powerplantsVector->push_back(eco27);
	powerplantsVector->push_back(eco33);
	powerplantsVector->push_back(eco37);
	powerplantsVector->push_back(eco44);
	powerplantsVector->push_back(eco50);

	//Step 3 at the end
	powerplantsVector->push_back(step3);

	//Used to make random_shuffle random
	//See:https://stackoverflow.com/questions/13459953/random-shuffle-not-really-random
	std::srand(std::time(0));

	//Randomly shuffle the cards 
	//from index 9 (Powerplant 13) to end-1 (excluding step 3)
	random_shuffle(powerplantsVector->begin() + 9, powerplantsVector->end() - 1);
}

PowerplantManager::~PowerplantManager() {

}

//Print the powerplant market
void PowerplantManager::printMarket() {

	/*
	TODO:: Case where market is < 8 ppcards
	*/

	if (step3) {

		//print only the first 6 houses
		if (powerplantsVector->size() > 6) {
			for (int i = 0; i < 6; i++) {
				if (i == 0) {
					cout << endl;
					cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
					cout << "@@@@@  Actual Market  @@@@@" << endl;
					cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
					cout << endl;
				}
				(*powerplantsVector)[i].showPlantInfo();
			}
		}
		//print the rest if we have less than 6
		else {
			cout << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			cout << "@@@@@  Actual Market  @@@@@" << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			cout << endl;
			for (Powerplant pp : *powerplantsVector) {
				pp.showPlantInfo();
			}
		}
	}
	else {
		//in step1 and step2 we still have more than 8 houses
		for (int i = 0; i < 8; i++) {
			if (i == 0) {
				cout << endl;
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
				cout << "@@@@@  Actual Market  @@@@@" << endl;
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
				cout << endl;
			}
			if (i == 4) {
				cout << endl;
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
				cout << "@@@@@  Future Market  @@@@@" << endl;
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
				cout << endl;
			}

			(*powerplantsVector)[i].showPlantInfo();
		}
	}
	

}

/*
Returns index of powerplant in actual market using the bid
Returns -2 if the powerplant isn't in market (since -1 is used for Step 3 card)
*/
int PowerplantManager::findPowerplantIndexInActualMarket(int bid) {
	
	int ppVSize = powerplantsVector->size();
	int index = 0;

	if (ppVSize <= 4) {
		for (Powerplant pp : *powerplantsVector) {
			if (pp.getBid() == bid) {
				return index;
			}
			index++;
		}
		return -2; //powerplant not found
	}
	else {
		for (int i = 0; i < 4; i++) {
			if ((*powerplantsVector)[i].getBid() == bid) {
				return i;
			}
		}
		return -2; //powerplant not found
	}
	
}

int PowerplantManager::findPowerplant(int bid) {
	int index = 0;

	for (Powerplant pp : *powerplantsVector) {
		if (pp.getBid() == bid) {
			return index;
		}
		index++;
	}

	return -2; //Not real powerplant
}
//Checks if the powerplant is in the actual market
bool PowerplantManager::isPowerplantInActualMarket(int bid) {

	if (findPowerplantIndexInActualMarket(bid) == -2) {
		return false;
	}
	return true;
}


//Sorts the powerplantVector first 8 elements according to 
//their miniumum bid
void PowerplantManager::sortMarket() {

	int ppVSize = powerplantsVector->size();

	if (ppVSize <= 8) {
		std::sort(powerplantsVector->begin(), powerplantsVector->end());
	}
	//sort only the first 8 elements
	else {
		std::sort(powerplantsVector->begin(), powerplantsVector->begin() + 8);
	}
}

//Checks the Actual market to see if the player has enough electro
//To purchase one of the items
bool PowerplantManager::hasEnoughElektroForMarket(int elektro) {

	//checks only first powerplant since market is already sorted
	if ((*powerplantsVector)[0].getBid() <= elektro) { 
		return true;
	}
	return false;
}


//After the player makes a final buy, it will add the pwp to one of the 3 slots, and 
//remove it from the market
Powerplant* PowerplantManager::getAndRemoveSpecificPowerplant(int powerPlantBid) {
	Powerplant* pwpdummy = new Powerplant();
	int count = 0;
	for (Powerplant pp : *powerplantsVector) {
		if (powerPlantBid == pp.getBid()) {
			//can have better solution, but i didnt want to change the code everywhere else
			pwpdummy = new Powerplant(pp.getBid(),pp.getType(),pp.getResourceReq(),pp.getCitiesPowered());
			//call remove function
			break;
		}
		count++;
	}
	powerplantsVector->erase(powerplantsVector->begin() + count);
	sortMarket();
	
	//if step3 is found set the step3 card as the highest big
	if ((*powerplantsVector)[0].getBid() == -1) {
		cout << "Step 3 card found. Setting it to 999999 as the highest bid, and shuffling the draw pile" << endl;
		(*powerplantsVector)[0].setBid(999999); //set step3 card as the highest bid
		sortMarket(); //resort market
		random_shuffle(powerplantsVector->begin() + 8, powerplantsVector->end()); //shuffling the draw pile (cards after step3 card)
		step3trigger = true;
	}
	return pwpdummy;

}

//Returns the powerplantManager vector. Used to save file.
vector<Powerplant>* PowerplantManager::getPowerplantVector()
{
	return powerplantsVector;
}

//Sets the powerplant vector. Used to load file.
void PowerplantManager::setPowerplantVector(vector<Powerplant>* pp_vector)
{
	powerplantsVector = pp_vector;
}

//Returns type of powerplant
string PowerplantManager::getPlantType(int index) {

	return (*powerplantsVector)[index].getType();

}

//Returns resources required of powerplant
int PowerplantManager::getPlantReq(int index) {

	return (*powerplantsVector)[index].getResourceReq();

}

//Returns number of cities powered by the plant
int PowerplantManager::getCitiesPowered(int index) {

	return (*powerplantsVector)[index].getCitiesPowered();
}

bool PowerplantManager::getStep3Trigger() {
	return step3trigger;
}

void PowerplantManager::setStep3(bool value)
{
	step3 = value;
}

void PowerplantManager::setStep3Trigger(bool value)
{
	step3trigger = value;
}

void PowerplantManager::buildingPhaseReorder(int highestNumberOfHouses)
{
	if (step3) {
		//if we are in step3 then erase the first powerplant
		powerplantsVector->erase(powerplantsVector->begin());
		//get ppvector.size
		int ppVSize = powerplantsVector->size();

		if (ppVSize >= 6) {
			for (int i = 0; i < 6; i++) {
				if ((*powerplantsVector)[i].getBid() <= highestNumberOfHouses) {
					powerplantsVector->erase(powerplantsVector->begin() + i);
					sortMarket();
					i = 0; //reset i=0 so it rechecks if a smaller pp is found
					continue;
				}
			}
		}
		//else do nothing since the market will still be sorted and we will just remove the lowest powerplant
	}
	else {
		//in step1 or step2
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if ((*powerplantsVector)[i].getBid() == -1) {
				step3trigger = true;
				continue;
			}
			else if ((*powerplantsVector)[i].getBid() <= highestNumberOfHouses) {
				powerplantsVector->erase(powerplantsVector->begin() + i);
				sortMarket();
				i = 0; //reset i=0 so it rechecks if a smaller pp is found
				continue;
			}
		}

		if (step3trigger) {
			cout << "Step 3 card found in building phase. Deleting step3 card, lowest powerplant card and shuffling the drawing deck" << endl;
			powerplantsVector->erase(powerplantsVector->begin()); //delete the step3 card
			powerplantsVector->erase(powerplantsVector->begin() + 1); //delete the lowest powerplant
			random_shuffle(powerplantsVector->begin() + 6, powerplantsVector->end()); //shuffling the draw pile
		}

	}

	
}

void PowerplantManager::bureaucracyPhaseReorder()
{
	Powerplant highestplant( 
		(*powerplantsVector)[8].getBid(),
		(*powerplantsVector)[8].getType(), 
		(*powerplantsVector)[8].getResourceReq(), 
		(*powerplantsVector)[8].getCitiesPowered());
	powerplantsVector->erase(powerplantsVector->begin() + 8); //delete the highest powerplant
	powerplantsVector->push_back(highestplant);
	sortMarket();

	if ((*powerplantsVector)[0].getBid() == -1) {
		step3trigger = true;
		cout << "Step 3 card found in bureaucracy phase. Deleting step3 card, lowest powerplant card and shuffling the drawing deck" << endl;
		powerplantsVector->erase(powerplantsVector->begin()); //delete the step3 card
		powerplantsVector->erase(powerplantsVector->begin() + 1); //delete the lowest powerplant
		random_shuffle(powerplantsVector->begin() + 6, powerplantsVector->end()); //shuffling the draw pile
	}
}

void PowerplantManager::removeLowestPowerplant() {
	powerplantsVector->erase(powerplantsVector->begin());
}

int PowerplantManager::getPlantNumber(int index) {

	return (*powerplantsVector)[index].getBid();


}