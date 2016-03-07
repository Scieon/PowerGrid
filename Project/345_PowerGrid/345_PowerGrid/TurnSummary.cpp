#include <iostream>
#include <algorithm>
#include <string>

#include "TurnSummary.h"
#include "PowerPlant.h"
#include "Resource.h"
#include "PowerPlantManager.h"
#include "Map.h"
#include "MapOfPlayersCity.h"

using namespace std;

//Default constructor
TurnSummary::TurnSummary() {
	turnCounter = 0; //keep track of who is going first
	nbOfPlayer = 0; //how many people are playing in this game. for now we will have 2 only.
	market = new ResourceMarket();
}

//Constructor
TurnSummary::TurnSummary(std::vector<Player*> vector_player, Map *map) {

	market = new ResourceMarket(); //Should load from save

	turnCounter = 1;
	this->vector_player = vector_player;
	nbOfPlayer = vector_player.size();
	powerplants_Vector = new PowerplantManager();
	this->map = map;
	mapOfPlayersCity = new MapOfPlayersCity();
}

//Destructor
TurnSummary::~TurnSummary() {

}

//Getter and Setter
void TurnSummary::setTurnCounter(int turnCounter) {
	this->turnCounter = turnCounter;
}

int TurnSummary::getTurnCounter() {
	return turnCounter;
}

/* Step1 - Determine turn order. The first time, it will be randomized. Then after the first time, it will always be comparing
who has the most number of houses in the network. If two players are tied, then choose the player with the largest number of power plant. */
void TurnSummary::turnOrder() {
	//Enters this step in the first round because it will randomize who gets to play first.
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FIRST STEP TO DETERMINE THE TURN ORDER" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;

	if (turnCounter == 1)
	{
		random_shuffle(vector_player.begin(), vector_player.end());
	}
	else
	{   //After first round, it will always go through this one to determine the order
		//This is where you will need to check each player's who has the highest amount of bought houses. If two players have the same number of houses then 
		//the turn order will be determined by the highest power plant number

		/*
		int player1HouseCount = vector_player.at(0)->getHouseManager()->getHouseCount();
		int player2HouseCount = vector_player.at(1)->getHouseManager()->getHouseCount();

		if (player1HouseCount1 < player2HouseCount){
			reverse(vector_player.begin(), vector_player.end());
		}
		else if (player1HouseCount == player2HouseCount){

			int player1HighestPlant = vector_player.at(0)->getPowerPlantManager()->determineHighestCost();
			int player2HighestPlant = vector_player.at(1)->getPowerPlantManager()->determineHighestCost();

			if (player1HighestPlant < player2HighestPlant){
				reverse(vector_player.begin(), vector_player.end());
			}
			else {
				//Already correct order
			}
		}
		else
			cout << "We are keeping the order" << endl;
		cout << "The player with the biggest most houses will start. If tied, biggest powerplant will go. " << endl;

		*/
	}
}

/*Step2 - Print to the first player and ask him to buy a powerplant, then ask the other players. On the first round, everyone will have to buy
 a power plant. Later on, we will implement the auction. */
void TurnSummary::buyPowerPlant() {
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS SECOND STEP THE BUYING OF POWER PLANTS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	//Need to choose from first four power plants, LET'S ASSUME THE PLAYER WILL CHOOSE 2 DIFFERENT POWER PLANT FOR NOW.



	Player* p = vector_player[0]; //first player bids

	cout << "Player with color " << p->getColor() << " can bid first " << endl;

	powerplants_Vector->printMarket();
	cout << endl;
	cout << "Player " << p->getColor() << endl;
	cout << "You currently have " << p->getElektro() << " electros" << endl;
	cout << "Please enter the minimum bid of the Power Plant you want to in from the Actual Market" << endl;
	cout << "Power Plant minimum bid: " << endl;

	int plantBid;
	cin >> plantBid;

	bool checkPP = powerplants_Vector->isPowerplantInActualMarket(plantBid);
	bool checkElectro = powerplants_Vector->hasEnoughElectroForMarket(p->getElektro());

	while (!checkPP || !checkElectro) {
		if (!checkPP) {
			cout << endl;
			cout << "This powerplant is not in the Actual Market" << endl;
		}
		else if (!checkElectro) {
			cout << endl;
			cout << "You do not have enough electros for this Power Plant" << endl;
		}
		cout << "You currently have " << p->getElektro() << " electros" << endl;
		cout << "Please enter the minimum bid of the Power Plant you want to buy in the Actual Market" << endl;
		cout << "Power Plant minimum bid: " << endl;
		cin >> plantBid;
		checkPP = powerplants_Vector->isPowerplantInActualMarket(plantBid);
		checkElectro = powerplants_Vector->hasEnoughElectroForMarket(plantBid);
	}



	//Print Powerplant

	string answer;
	int playerBid;

	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@ Starting Auction @@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	while (true) {

		p = getNextPlayer(*p);
		cout << endl;

		if (p->getElektro() <= plantBid) {
			cout << "Player " << p->getColor() << endl;
			cout << "You do not have enough electros to bid" << endl;
			break;
		}

		cout << "It's your turn Player " << p->getColor() << endl;
		cout << "You currently have " << p->getElektro() << " electros" << endl;
		cout << "The current bid is " << plantBid << endl;
		cout << "Do you want to bid on power plant? Type 'y' for yes" << endl;
		cin >> answer;

		if (answer == "y") {
			cout << "Please enter the amount you want to bid: " << endl;
			cin >> playerBid;

			bool bidTooLow = playerBid < plantBid;
			bool notEnoughElectro = playerBid > p->getElektro();

			while (bidTooLow || notEnoughElectro) {
				if (bidTooLow) {
					cout << endl;
					cout << "Your bid is too low" << endl;
				}
				else if (notEnoughElectro) {
					cout << endl;
					cout << "Your bid is too high" << endl;
				}

				cout << "Please enter the amount you want to bid: " << endl;
				cin >> playerBid;
				bidTooLow = playerBid < plantBid;
				notEnoughElectro = playerBid > p->getElektro();
			}
			plantBid = playerBid;
			//Reloop
		}
		else {
			break;
		}
	}

	//remove electro from player
	//set powerplant to player
	//Remove powerplant from market
	//Reorder whole market
	//Sort market

	//get second player bid (p=getNextPlayer(*p))
	//get his powerplant

	//remove electro from player
	//set powerplant to player
	//Remove powerplant from market
	//Reorder whole market
	//Sort market



	/*

	for (Player* p : vector_player)
	{

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
			//p->getPowerPlantManager()->addPowerPlant(p1);
			p->setElektro(p->getElektro() - 3);
			cout << "Here is how much you have after buying " <<p->getElektro() << "$" << endl;
		}
		else if (plantChoice == 2){
			//p->getPowerPlantManager()->addPowerPlant(p2);
			p->setElektro(p->getElektro() - 4);
			cout << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
		}
		else if (plantChoice == 3){
			//p->getPowerPlantManager()->addPowerPlant(p3);
			p->setElektro(p->getElektro() - 5);
			cout << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
		}
		else if (plantChoice == 4){
			//p->getPowerPlantManager()->addPowerPlant(p4);
			p->setElektro(p->getElektro() - 6);
			cout << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
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
	*/
}

/* Step 3 - Buy raw material. In this part, the last player will begin. In other words, it's the reverse order of buying power plant who starts. */
void TurnSummary::buyRawMaterial() {
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS THIRD STEP TO BUY RAW MATERIALS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	string materialChoice;
	int qty;
	reverse(vector_player.begin(), vector_player.end());

	for (Player* p : vector_player) {
		cout << "Since we are starting with the last player to buy the raw material. Here is the STARTING PLAYER with the color: " << p->getColor() << endl << endl;

		while (true) {
			cout << endl <<"Player " << p->getColor() << " turn, please choose what you want to buy(coal, oil, uranium, or garbage). When you're done type done. " << endl;
			cin >> materialChoice;

			if (materialChoice == "coal") {
				cout << "How many coal would you like buy: ";
				cin >> qty;

				//Validating if market has enough resources (Note: getMarketCost calls getMarketQuantity)
				if (market->getMarketCost("Coal", qty) == -1) {
					cout << "CONTINUE" << endl;
					system("pause");
					continue;
				}

				//Validating if player can store or purchase the quantity of resources
				if (p->validateResourcePurchase(market->getMarketCost("Coal", qty), qty, "Coal")) {
					cout << "Cost was: " << market->getMarketCost("Coal", qty) << " elektros." << endl;
					cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
					cout << "Current coal in possession: " << p->getResource("Coal") << endl;
				}

			}
			else if (materialChoice == "oil") {
				cout << "How many oil would you like to buy? ";
				cin >> qty;
				//p->getResources()->setOil(qty + p->getResources()->getOil());
				p->addResource("Oil", qty);

				p->setElektro(p->getElektro() - (3 * qty));
				cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
			}
			else if (materialChoice == "uranium") {
				cout << "How many uranium would you like to buy? ";
				cin >> qty;
				//p->getResources()->setUranium(qty + p->getResources()->getUranium());
				p->addResource("Uranium", qty);
				p->setElektro(p->getElektro() - (12 * qty));
				cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
			}
			else if (materialChoice == "garbage") {
				cout << "How many garbage would you like to buy? ";
				cin >> qty;
				//p->getResources()->setGarbage(qty + p->getResources()->getGarbage());
				p->addResource("Garbage", qty);
				p->setElektro(p->getElektro() - (6 * qty));
				cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
			}
			else if (materialChoice == "done") {
				break;
			}
		}
	}
}

/* Step 4 - Building houses. Can choose which city one would like to build in. We would have to implement the cost it takes to get from one city to the next. */
void TurnSummary::building() {
	string buildOption;
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FOURTH STEP TO BUILD HOUSES" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	for (Player* p : vector_player) {
		cout << "*****************************************************************" << endl;
		cout << endl << "Would PLAYER " << p->getColor() << " like to build houses? yes or no. At the first round, you can only build houses on cities costing 10. The LAST PLAYER will begin again. " << endl;
		cin >> buildOption;

		int houseCount = p->getHouseManager()->getHouseCount();
		//if player has no houses yet
		if (houseCount == 0) {
			cout << "You can build in these Cities:" << endl;

		}

		while (true) {
			//First few rounds will only let you buy for 10. Have to implement exception that after buying that city, it is no longer available. For now, we will leave it as it is.
			if (buildOption == "yes") {
				string houseChoice;
				cout << "Would " << p->getColor() << " like to buy a house at Duisburg, Essen, D�Eseldorf, or Dortmunt?" << endl;
				cin >> houseChoice;
				p->setElektro(p->getElektro() - 10);
				//p->getHouseManager()->addHouses(h1);
			}
			else if (buildOption == "no") {
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
void TurnSummary::bureaucracy() {
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FIFTH STEP THE BUREAUCRACY" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	int nbHousePower;
	int paymentTable[21] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };
	reverse(vector_player.begin(), vector_player.end());
	for (Player* p : vector_player) {
		//player gets the money depending on how many houses they have powered. Even if they don't power any houses, they will automatically get 10 elektro.
		//Not going to power every single house they have bought, but in this case we will leave it as it is. They should be able to choose how many houses 
		//they are going to power based on their resources.
		cout << "*****************************************************************" << endl;
		cout << "How many houses would PLAYER " << p->getColor() << " like to power?" << endl;
		cout << "PLAYER " << p->getColor() << " has " << p->getHouseManager()->getHouseCount() << " houses." << endl;
		cin >> nbHousePower;

		//The number of houses that the player chooses to power must be less than or equal to the amount of houses they bought.
		if (nbHousePower <= (p->getHouseManager()->getHouseCount())) {
			p->setElektro(p->getElektro() + (paymentTable[nbHousePower]));
		}
		else {
			while (nbHousePower > (p->getHouseManager()->getHouseCount())) {
				cout << "Please insert the appropriate number of houses PLAYER " << p->getColor() << " wish to power.";
				cout << "How many houses would PLAYER " << p->getColor() << " like to power?";
				cin >> nbHousePower;
			}
			p->setElektro(p->getElektro() + (paymentTable[nbHousePower]));
		}
	}
	turnCounter++; //the first round going through this will be different then afterwards it will become the same
}

//Returns next player
Player * TurnSummary::getNextPlayer(Player & p) {
	if (&p == &*vector_player[0]) {
		return vector_player[1];
	}
	return vector_player[0];

}






