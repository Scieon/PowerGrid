#include <iostream>
#include <algorithm>
#include <string>

#include "TurnSummary.h"
#include "PowerPlant.h"
#include "Resource.h"
#include "PowerPlantManager.h"

using namespace std;

//Default constructor
TurnSummary::TurnSummary(){
	turnCounter = 0; //keep track of who is going first
	nbOfPlayer = 0; //how many people are playing in this game. for now we will have 2 only.
}

//Constructor
TurnSummary::TurnSummary(std::vector<Player*> vector_player){
	turnCounter = 1;
	this->vector_player = vector_player;
	nbOfPlayer = vector_player.size();
}

//Destructor
TurnSummary::~TurnSummary(){

}

//Getter and Setter
void TurnSummary::setTurnCounter(int turnCounter){
	this->turnCounter = turnCounter;
}

int TurnSummary::getTurnCounter(){
	return turnCounter;
}

/* Step1 - Determine turn order. The first time, it will be randomized. Then after the first time, it will always be comparing 
who has the most number of houses in the network. If two players are tied, then choose the player with the largest number of power plant. */
void TurnSummary::turnOrder(){
	//Enters this step in the first round because it will randomize who gets to play first.
	if (turnCounter == 1)
	{
		cout << " ///////////////////////////////////////////////////////" << endl;
		cout << " THIS IS FIRST STEP TO DETERMINE THE TURN ORDER" << endl;
		cout << " ///////////////////////////////////////////////////////" << endl;

		random_shuffle(vector_player.begin(), vector_player.end());
		int position = 1;
		for (Player* p : vector_player)
		{
			p->setTurnOrder(position);
			cout << "Here is the P" << position << " with the color: " << p->getColor() << endl;
			position++;
		}
	}
	else
	{   //After first round, it will always go through this one to determine the order
		cout << " ///////////////////////////////////////////////////////" << endl;
		cout << " THIS IS FIRST STEP TO DETERMINE THE TURN ORDER" << endl;
		cout << " ///////////////////////////////////////////////////////" << endl;

		//This is where you will need to check each player's who has the highest amount of bought houses. If two players have the same number of houses then 
		//the turn order will be determined by the highest power plant number 

		if (vector_player.at(0)->getHouseManager()->getHouseCount() < vector_player.at(1)->getHouseManager()->getHouseCount()){
			reverse(vector_player.begin(), vector_player.end());
		}
		else if (vector_player.at(0)->getHouseManager()->getHouseCount() == vector_player.at(1)->getHouseManager()->getHouseCount()){
			if (vector_player.at(0)->getPowerPlantManager()->determineHighestCost() < vector_player.at(1)->getPowerPlantManager()->determineHighestCost()){
				reverse(vector_player.begin(), vector_player.end());
			}
		}
		else
			cout << "We are keeping the order" << endl;
		cout << "The player with the biggest most houses will start. If tied, biggest powerplant will go. " << endl;
	}
}

/*Step2 - Print to the first player and ask him to buy a powerplant, then ask the other players. On the first round, everyone will have to buy 
 a power plant. Later on, we will implement the auction. */
void TurnSummary::buyPowerPlant(){
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS SECOND STEP THE BUYING OF POWER PLANTS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	//Need to choose from first four power plants, LET'S ASSUME THE PLAYER WILL CHOOSE 2 DIFFERENT POWER PLANT FOR NOW.
	int counter = 1;
	for (Player* p : vector_player)
	{
		cout << "Here is the player who is starting to buy it, " << p->getColor() << endl;
		PowerPlant p1 = PowerPlant(3, "coal", 1);
		PowerPlant p2 = PowerPlant(4, "oil", 1);
		PowerPlant p3 = PowerPlant(5,"coal", 1);
		PowerPlant p4 = PowerPlant(6, "oil", 1);

		cout << "Player " << p->getColor() << " turn, please press from 1 to 4 to choose your powerplants" << endl;

		p1.printPowerPlantSummary();
		p2.printPowerPlantSummary();
		p3.printPowerPlantSummary();
		p4.printPowerPlantSummary();

		//condition here that will add p to x depending on what the person cin to the powerplant manager of the person 
		int plantChoice;
		cout << "Press 1 to 4 to buy a powerplant, if you do not want any press 0, but the first round you have to buy" << endl;
		cin >> plantChoice;
		if (turnCounter == 1){
			while (plantChoice>4)
				{
					cout << "Sorry for the first turn you have to buy a power plant. Choose power plant 1, 2, 3, or 4." << endl;
					cin >> plantChoice;
				}
		}
		//add powerplant to player powerplant manager
		if (plantChoice == 1){
			p->getPowerPlantManager()->addPowerPlant(p1);
			p->setMoney(p->getMoney() - 3);
			cout << "Here is how much you have after buying " <<p->getMoney() << "$" << endl;
		}
		else if (plantChoice == 2){
			p->getPowerPlantManager()->addPowerPlant(p2);
			p->setMoney(p->getMoney() - 4);
			cout << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
		}
		else if (plantChoice == 3){
			p->getPowerPlantManager()->addPowerPlant(p3);
			p->setMoney(p->getMoney() - 5);
			cout << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
		}
		else if (plantChoice == 4){
			p->getPowerPlantManager()->addPowerPlant(p4);
			p->setMoney(p->getMoney() - 6);
			cout << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
		}
		
	}
// first round will tell if there is an order change depending who bought the highest power plant
	if (turnCounter == 1){
		//powerPlantCost[counter] = p->getPowerPlantManager().determineHighestCost();
		//counter++;
		if (vector_player.at(0)->getPowerPlantManager()->determineHighestCost() < vector_player.at(1)->getPowerPlantManager()->determineHighestCost()){
			reverse(vector_player.begin(), vector_player.end());
		}
	}
}

/* Step 3 - Buy raw material. In this part, the last player will begin. In other words, it's the reverse order of buying power plant who starts. */
void TurnSummary::buyRawMaterial(){
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS THIRD STEP TO BUY RAW MATERIALS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	string materialChoice;
	int qty;
	reverse(vector_player.begin(), vector_player.end());

	for (Player* p : vector_player){
		cout << "Since we are starting with the last player to buy the raw material. Here is the STARTING PLAYER with the color: " << p->getColor() << endl <<endl;

		while (true){
			cout << "Player " << p->getColor() << " turn, please choose what you want to buy(coal, oil, uranium, or garbage). When you're done type done. " << endl;
			cin >> materialChoice;

			//have to add each in player, and need to add max of 2 items only
			//They must choose how many of the raw material that they would like to buy. It will calculate the cost to their money too.
			if (materialChoice == "coal"){
				cout << "How many coal would you like buy? ";
				cin >> qty;
				p->getResources()->setCoal(qty + p->getResources()->getCoal());
				p->setMoney(p->getMoney() - (3 * qty));
				cout << endl << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
				cout <<" HERE IS THE COAL " <<p->getResources()->getCoal() << endl;
			}
			else if (materialChoice == "oil"){
				cout << "How many oil would you like to buy? ";
				cin >> qty;
				p->getResources()->setOil(qty + p->getResources()->getOil());
				p->setMoney(p->getMoney() - (3 * qty));
				cout << endl << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
			}
			else if (materialChoice == "uranium"){
				cout << "How many uranium would you like to buy? ";
				cin >> qty;
				p->getResources()->setUranium(qty + p->getResources()->getUranium());
				p->setMoney(p->getMoney() - (12 * qty));
				cout << endl << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
			}
			else if (materialChoice == "garbage"){
				cout << "How many garbage would you like to buy? ";
				cin >> qty;
				p->getResources()->setGarbage(qty + p->getResources()->getGarbage());
				p->setMoney(p->getMoney() - (6 * qty));
				cout << endl << "Here is how much you have after buying " << p->getMoney() << "$" << endl;
			}
			else if (materialChoice == "done"){
				break;
			}
		}
	}
}

/* Step 4 - Building houses. Can choose which city one would like to build in. We would have to implement the cost it takes to get from one city to the next. */
void TurnSummary::building(){
	string buildOption;
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FOURTH STEP TO BUILD HOUSES" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	for (Player* p : vector_player){
		cout << "*****************************************************************" << endl;
		cout << endl << "Would PLAYER " <<p->getColor() << " like to build houses? yes or no. At the first round, you can only build houses on cities costing 10. The LAST PLAYER will begin again. " << endl;
		cin >> buildOption;
		House h1 = House("Duisburg");
		House h2 = House("Essen");
		House h3 = House("Düsseldorf");
		House h4 = House("Dortmunt");

		while (true){
			//First few rounds will only let you buy for 10. Have to implement exception that after buying that city, it is no longer available. For now, we will leave it as it is.
			if (buildOption == "yes"){
				string houseChoice;
				cout << "Would " <<p->getColor() << " like to buy a house at Duisburg, Essen, Düsseldorf, or Dortmunt?" << endl;
				cin >> houseChoice;
				p->setMoney(p->getMoney() - 10);
				p->getHouseManager()->addHouses(h1);
			}
			else if (buildOption == "no"){
				break;
			}
			cout << "Would " << p->getColor() << " like to build again? yes or no" << endl;
			cin >> buildOption;
		}
	}
	
}

/* Step 5 - Bureaucracy. Use bought resources to power electricity to how many houses. Those resources go back in the market.
  Depending on how many houses they've powered, they will generate a certain amount of money. 
  We are at phase 1 until someone builds the 7th house. Then phase 2 ends when phase 3 card is drawn. Also, during phase 1 and 2, we must place the
  highest power plant under the stack. On the other hand, in phase 3, we will move the lowest power plant under the stack.*/
void TurnSummary::bureaucracy(){
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FIFTH STEP THE BUREAUCRACY" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	int nbHousePower;
	int paymentTable[21] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };
	reverse(vector_player.begin(), vector_player.end());
	for (Player* p : vector_player){
		//player gets the money depending on how many houses they have powered. Even if they don't power any houses, they will automatically get 10 elektro.
		//Not going to power every single house they have bought, but in this case we will leave it as it is. They should be able to choose how many houses 
		//they are going to power based on their resources.
		cout << "*****************************************************************" << endl;
		cout << "How many houses would PLAYER " << p->getColor() << " like to power?" << endl;
		cout << "PLAYER " << p->getColor() << " has " << p->getHouseManager()->getHouseCount() << " houses." << endl;
		cin >> nbHousePower;

		//The number of houses that the player chooses to power must be less than or equal to the amount of houses they bought.
		if (nbHousePower <= (p->getHouseManager()->getHouseCount())){
			p->setMoney(p->getMoney() + (paymentTable[nbHousePower]));
		}
		else{
			while (nbHousePower > (p->getHouseManager()->getHouseCount())){
				cout << "Please insert the appropriate number of houses PLAYER " <<p->getColor() << " wish to power.";
				cout << "How many houses would PLAYER " <<p->getColor() << " like to power?";
				cin >> nbHousePower;
			}
			p->setMoney(p->getMoney() + (paymentTable[nbHousePower]));
		}
	}
	turnCounter++; //the first round going through this will be different then afterwards it will become the same
}









