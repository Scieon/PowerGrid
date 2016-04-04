#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>

#include "Board.h"
#include "PowerPlant.h"
#include "Resource.h"
#include "PowerPlantManager.h"
#include "Map.h"
#include "MapOfPlayersCity.h"
#include "IOFile.h"


using namespace std;

//Default constructor
Board::Board() {
	turnCounter = 1; //keep track round number
	nbOfPlayer = 0; //how many people are playing in this game. for now we will have 2 only.
	market = new ResourceMarket();
	step2 = false;
	step3 = false;
}

//Constructor
Board::Board(std::vector<Player*> vector_player, Map *map) {

	market = new ResourceMarket(); //Should load from save

	turnCounter = 1;
	this->vector_player = vector_player;
	nbOfPlayer = vector_player.size();
	powerplants_Vector = new PowerplantManager();
	mapOfPlayersCity = new MapOfPlayersCity(map);
	step2 = false;
	step3 = false;
}

//Destructor
Board::~Board() {

}

//Getter and Setter
void Board::setTurnCounter(int turnCounter) {
	this->turnCounter = turnCounter;
}

int Board::getTurnCounter() {
	return turnCounter;
}

/* Step1 - Determine turn order. The first time, it will be randomized. Then after the first time, it will always be comparing
who has the most number of houses in the network. If two players are tied, then choose the player with the largest number of power plant. */
void Board::turnOrder() {
	//Enters this step in the first round because it will randomize who gets to play first.
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FIRST STEP TO DETERMINE THE TURN ORDER" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << endl;

	houseScoringTrack(); //showing the number of houses on the scoring track

	if (turnCounter == 1)
	{
		random_shuffle(vector_player.begin(), vector_player.end());
	}
	else
	{   //After first round, it will always go through this one to determine the order
		//This is where you will need to check each player's who has the highest amount of bought houses. If two players have the same number of houses then 
		//the turn order will be determined by the highest power plant number


		int player1HouseCount = vector_player.at(0)->getHouseManager()->getHouseCount();
		int player2HouseCount = vector_player.at(1)->getHouseManager()->getHouseCount();

		if (player1HouseCount < player2HouseCount) {
			reverse(vector_player.begin(), vector_player.end());
		}
		else if (player1HouseCount == player2HouseCount) {

			int player1HighestPlant = (vector_player)[0]->getHighestMinBid();
			int player2HighestPlant = vector_player.at(1)->getHighestMinBid();

			if (player1HighestPlant < player2HighestPlant) {
				reverse(vector_player.begin(), vector_player.end());
			}
			else {
				//Already correct order
			}
		}
		else
			cout << "We are keeping the order" << endl;
		cout << "The player with the most houses will start. If tied, biggest powerplant number will go. " << endl;


	}
}

/*Step2 - Print to the first player and ask him to buy a powerplant, then ask the other players. On the first round, everyone will have to buy
 a power plant. Later on, we will implement the auction. */
void Board::buyPowerPlant() {

	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS SECOND STEP THE BUYING OF POWER PLANTS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;

	Player* p = vector_player[0];//first player bids

	bool playerAlreadyBought = false;
	while (true) {


		cout << "Player with color " << p->getColor() << " can bid first " << endl;

		powerplants_Vector->printMarket();

		cout << endl;
		cout << "Player " << p->getColor() << endl;
		cout << "You currently have " << p->getElektro() << " elektros" << endl;
		cout << "Please enter the minimum bid of the Power Plant you want from the Actual Market" << endl;
		cout << "Power Plant minimum bid: " << endl;

		int plantBid;
		cin >> plantBid;

		bool checkPP = powerplants_Vector->isPowerplantInActualMarket(plantBid);
		bool checkElektro = powerplants_Vector->hasEnoughElektroForMarket(p->getElektro());

		while (!checkPP || !checkElektro) {
			if (!checkPP) {
				cout << endl;
				cout << "--ERROR-- This powerplant is not in the Actual Market --ERROR--" << endl << endl;
			}
			else if (!checkElektro) {
				cout << endl;
				cout << "--ERROR-- You do not have enough elektros for this Power Plant --ERROR--" << endl;
			}
			cout << "You currently have " << p->getElektro() << " elektros" << endl;
			cout << "Please enter the minimum bid of the Power Plant you want to buy in the Actual Market" << endl;
			cout << "Power Plant minimum bid: " << endl;
			cin >> plantBid;
			checkPP = powerplants_Vector->isPowerplantInActualMarket(plantBid);
			checkElektro = powerplants_Vector->hasEnoughElektroForMarket(plantBid);
		}

		//Checks if the other player already bought a powerplant -- just works for 1 round. If yes, then there is no need for an auction.
		//The player with no powerplant will automatically buy the lowest plantBid without the other player interfering
		if (getNextPlayer(*p)->getPowerplantsVector()->size() == 1 && playerAlreadyBought) {
			p->addPlant(powerplants_Vector->getAndRemoveSpecificPowerplant(plantBid));
			p->setElektro(p->getElektro() - plantBid);
			cout << "\nPlayer " << p->getColor() << " has " << p->getElektro() << "." << endl << endl;
			break;
			//If both players bought a powerplant on the first round then break from the first while (stop buying powerplant)
			if (p->getPowerplantsVector()->size() == 1) {
				break;
			}
		}

		if (playerAlreadyBought) {
			break;
		}
		int powerPlantBid = plantBid; //to know the actual minimum bid
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
				cout << "You do not have enough elektros to bid" << endl;
				break;
			}

			cout << "It's your turn Player " << p->getColor() << endl;
			cout << "You currently have " << p->getElektro() << " elektros" << endl;
			cout << "The current bid is " << plantBid << endl;
			cout << "Do you want to bid on power plant? Type 'y' for yes or 'n' for no" << endl;
			cin >> answer;

			if (answer == "y") {
				cout << "Please enter the amount you want to bid: " << endl;
				cin >> playerBid;

				bool bidTooLow = playerBid <= plantBid;
				bool notEnoughElektro = playerBid > p->getElektro();

				while (bidTooLow || notEnoughElektro) {
					if (bidTooLow) {
						cout << endl;
						cout << "Your bid is too low" << endl;
					}
					else if (notEnoughElektro) {
						cout << endl;
						cout << "Your bid is too high" << endl;
					}

					cout << "Please enter the amount you want to bid: " << endl;
					cin >> playerBid;
					bidTooLow = playerBid < plantBid;
					notEnoughElektro = playerBid > p->getElektro();
				}
				plantBid = playerBid;
				//Reloop
			}

			//If they they don't want to auction anymore then the next player will end up buying the powerplant
			else if (answer == "n") {
				p = getNextPlayer(*p);
				p->setElektro(p->getElektro() - plantBid);
				cout << "Player " << p->getColor() << " has " << p->getElektro() << "." << endl;
				p->addPlant(powerplants_Vector->getAndRemoveSpecificPowerplant(powerPlantBid));// adds into next person's powerplant possession
				playerAlreadyBought = true;
				p = getNextPlayer(*p);
				break;
			}
		}
	}

	//First round will tell if there is an order change depending who bought the highest power plant
	if (turnCounter == 1) {
		if (vector_player[0]->getHighestMinBid() < vector_player[1]->getHighestMinBid()) {
			reverse(vector_player.begin(), vector_player.end());
			cout << "The first player for next round (meaning the last player with lowest powerplant number) will be, PLAYER " << vector_player[1]->getColor() << endl;
		}

	}
}

/* Step 3 - Buy raw material. In this part, the last player will begin. In other words, it's the reverse order of buying power plant who starts. */
void Board::buyRawMaterial() {

	cout << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS THIRD STEP TO BUY RAW MATERIALS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;

	string materialChoice;
	int qty;
	reverse(vector_player.begin(), vector_player.end());

	for (Player* p : vector_player) {
		cout << "Since we are starting with the last player to buy the raw material. Here is the STARTING PLAYER with the color: " << p->getColor() << endl << endl;
		while (true) {
			cout << endl << "Player " << p->getColor() << " turn, please choose what you want to buy: " << endl << "(coal, oil, uranium, or garbage)" << " When finished please type done. " << endl;
			cout << "Enter 1 to see current resource market." << endl
				<< "Enter 2 to see powerplants owned." << endl
				<< "Enter 3 to see resources owned." << endl;
			cout << "Choice: ";
			cin >> materialChoice; cout << endl;

			if (materialChoice == "1") {
				market->showInfo();
				system("pause");
				continue;
			}

			if (materialChoice == "2") {
				p->showPlants();
				system("pause");
				continue;
			}

			if (materialChoice == "3") {
				p->showInfo();
				system("pause");
				continue;
			}

			if (materialChoice == "coal" || materialChoice == "Coal") {
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
					market->updateMarket("Coal", qty);
				}

			}
			else if (materialChoice == "oil" || materialChoice == "Oil") {

				cout << "How many oil would you like buy: ";
				cin >> qty;

				//Validating if market has enough resources (Note: getMarketCost calls getMarketQuantity)
				if (market->getMarketCost("Oil", qty) == -1) {
					continue;
				}

				//Validating if player can store or purchase the quantity of resources
				if (p->validateResourcePurchase(market->getMarketCost("Oil", qty), qty, "Oil")) {
					cout << "Cost was: " << market->getMarketCost("Oil", qty) << " elektros." << endl;
					cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
					cout << "Current oil in possession: " << p->getResource("Oil") << endl;
					market->updateMarket("Oil", qty);
				}

			}
			else if (materialChoice == "uranium" || materialChoice == "Uranium") {

				cout << "How many uranium would you like buy: ";
				cin >> qty;

				//Validating if market has enough resources (Note: getMarketCost calls getMarketQuantity)
				if (market->getMarketCost("Uranium", qty) == -1) {
					continue;
				}

				//Validating if player can store or purchase the quantity of resources
				if (p->validateResourcePurchase(market->getMarketCost("Uranium", qty), qty, "Uranium")) {
					cout << "Cost was: " << market->getMarketCost("Uranium", qty) << " elektros." << endl;
					cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
					cout << "Current uranium in possession: " << p->getResource("Uranium") << endl;
					market->updateMarket("Uranium", qty);
				}
			}

			else if (materialChoice == "garbage" || materialChoice == "Garbage") {

				cout << "How many garbage would you like buy: ";
				cin >> qty;

				//Validating if market has enough resources (Note: getMarketCost calls getMarketQuantity)
				if (market->getMarketCost("Garbage", qty) == -1) {
					continue;
				}

				//Validating if player can store or purchase the quantity of resources
				if (p->validateResourcePurchase(market->getMarketCost("Garbage", qty), qty, "Garbage")) {
					cout << "Cost was: " << market->getMarketCost("Garbage", qty) << " elektros." << endl;
					cout << endl << "Here is how much you have after buying " << p->getElektro() << "$" << endl;
					cout << "Current garbage in possession: " << p->getResource("Garbage") << endl;
					market->updateMarket("Garbage", qty);
				}
			}
			else if (materialChoice == "done") {
				break;
			}
		}
	}
}

/* Step 4 - Building houses. Can choose which city one would like to build in. We would have to implement the cost it takes to get from one city to the next. */
void Board::building() {
	string buildOption;
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FOURTH STEP TO BUILD HOUSES" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;


	/*
	TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
	EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
	TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


	mapOfPlayersCity->setStep2(true);
	mapOfPlayersCity->setStep3(true);

	vector_player[0]->subtractMoney(-200);
	vector_player[1]->subtractMoney(-200);
	*/

	for (Player* p : vector_player) {

		cout << "*****************************************************************" << endl;
		cout << endl;
		/*
		if (turnCounter == 1) {
			cout << "Since this first round, you can only build houses on cities costing 10. The LAST PLAYER will begin again. " << endl;
		}
		*/
		cout << endl << "Map presentation: " << endl;
		mapOfPlayersCity->printPlayersCity();

		cout << "Player " << p->getColor() << " it's your turn. Would you like to build a house?." << endl;
		cout << "Type 'y' for yes or 'n' for no." << endl;
		cin >> buildOption;

		while (true) {

			if (buildOption == "y" || buildOption == "Y") {

				int houseCount = p->getHouseManager()->getHouseCount();

				//if player does not have enough electro to purchase 1 house of 10 elektro
				if (!p->hasEnoughtElektroFor(10)) {
					cout << "Player " << p->getColor() << " You do not have enough elektro to place a house" << endl;
					break;
				}

				//if player has no houses yet
				if (houseCount == 0) {
					cout << "You can build in these Cities:" << endl;

					//print free locations
					mapOfPlayersCity->printAvailableIndices();

					cout << "You currently have " << p->getElektro() << " elektro" << endl;

					int index = pleaseChooseIndexToBuildIn();

					House house(index, mapOfPlayersCity->getIndexName(index));

					p->getHouseManager()->addHouses(house);
					mapOfPlayersCity->setPlayerHouse(index, p->getColor());
					p->subtractMoney(10);
					cout << endl << "Map presentation: " << endl;
					mapOfPlayersCity->printPlayersCity();
					cout << endl << "Purchase completed" << endl;
					cout << "You now have " << p->getElektro() << " elektro" << endl;
					cout << "Player " << p->getColor() << " would you like to build a house?." << endl;
					cout << "Type 'y' for yes or 'n' for no." << endl;
					cin >> buildOption;
				}
				else
				{

					pair<vector<double>, vector<list<int> > > costAndPath = mapOfPlayersCity->getAvailableIndicesCost(p->getHouseManager()->getHouseIndices(), p->getElektro());
					vector<double> costVector = costAndPath.first;
					vector<list<int> > pathVector = costAndPath.second;

					//If there is no free city to put a house in
					if (costAndPath == pair<vector<double>, vector<list<int> > >()) {
						cout << "Player " << p->getColor() << "There is no city in that map that is free to play." << endl;
						break;
					}

					else {
						cout << endl << "You currently have " << p->getElektro() << " elektro" << endl;
						cout << "These are the houses you can purchase: " << endl;

						//print indices
						mapOfPlayersCity->printAvailableIndicesCost(p->getHouseManager()->getHouseIndices(), p->getElektro());

						//Get input from player and get the position of the index in the vector
						pair<int, int> indexPositionPair = pleaseChooseIndexToBuildIn(pathVector);
						int playerIndex = indexPositionPair.first;
						int indexPosition = indexPositionPair.second;

						cout << "You are purchasing the house at Index " + playerIndex << endl;


						//Go from the shortest path and build houses that the player 
						//does not currently own and have an empty space
						for (int index : pathVector[indexPosition]) {

							//if the player does not currently own the house and the city is free to build then build house
							if (mapOfPlayersCity->playerOwnsHouseAndCityHasEmptySpace(p->getHouseManager()->getHouseIndices(), index)) {

								House house(index, mapOfPlayersCity->getIndexName(index)); //create house
								p->getHouseManager()->addHouses(house); //add house to player
								mapOfPlayersCity->setPlayerHouse(index, p->getColor()); //add house in map
								cout << "House index " << index << " name: " << mapOfPlayersCity->getIndexName(index) << " purchased" << endl;
							}

						}

						//Get cost of purchase of the index the player wants to purchase
						int costOfPurchase = (int)costVector[indexPosition];
						p->subtractMoney(costOfPurchase); //substract elektro

						cout << endl << "Map presentation: " << endl;
						mapOfPlayersCity->printPlayersCity();
						cout << endl << "Purchase completed" << endl;
						cout << "You now have " << p->getElektro() << " elektro" << endl;
						cout << "Player " << p->getColor() << " would you like to build a house?." << endl;
						cout << "Type 'y' for yes or 'n' for no." << endl;
						cin >> buildOption;
					}

				}
			}
			if (buildOption == "y" || buildOption == "Y") {
				continue;
			}
			else if (buildOption == "n" || buildOption == "N") {
				break;
			}
		}
	}

	//Get each player house size and activate step2 if conditions are met
}

void Board::strategies()
{

	//PART 1 START

	Player * pAI = vector_player[2]; //AI player?


	//returns all the adjacent indices that the player pAI has (no duplicates, no houses the AI currently owns, only adjacent indices to all houses)
	vector<int> pAIAllAdjacentIndices = mapOfPlayersCity->getMap()->getAdjacentIndices(pAI->getHouseManager()->getHouseIndices());


	vector<string> playerNames;

	for (int index : pAIAllAdjacentIndices) {
		//if there is at least 1 player in that location
		if (mapOfPlayersCity->getHouseCount(index) > 1) {
			playerNames = mapOfPlayersCity->getPlayerNames(index);
			break;
		}
	}

	//TODO
	if (true) {
		//get the player with the least # of houses (from get player.getHousemanager.getHouseCount) 
		//depending on the names in playerNames.
		//if there is only 1 name then find which player has this name and get him
	}

	//suppose player0 has less houses
	Player * p0 = vector_player[0];

	//get all adjacent indices that p0 has
	vector<int> p0AllAdjacentIndices = mapOfPlayersCity->getMap()->getAdjacentIndices(p0->getHouseManager()->getHouseIndices());

	//Go into every house the AI owns, and see if they have common houses with the player
	//if they do then remove it
	//At the end, p0AllAdjacentIndices will own all the potential houses we can build in
	//which is all the adjacent indices of p0 minus the indices that the AI already owns
	for (int AIHouse : pAIAllAdjacentIndices) {
		std::vector<int>::iterator position = std::find(p0AllAdjacentIndices.begin(), p0AllAdjacentIndices.end(), AIHouse);
		//if they own the same house then erase that house
		if (position != p0AllAdjacentIndices.end()) {
			p0AllAdjacentIndices.erase(position);
		}
	}

	//From all the potential locations to place a house
	//Check is there is space to put a house in there
	//If there is space then add a house there
	for (int HouseIndex : p0AllAdjacentIndices) {
		//if there is space then add house
		if (mapOfPlayersCity->isCityFree(HouseIndex)) {
			House house(HouseIndex, mapOfPlayersCity->getIndexName(HouseIndex)); //create house
			pAI->getHouseManager()->addHouses(house); //add house to AI
			mapOfPlayersCity->setPlayerHouse(HouseIndex, pAI->getColor()); //add house in map
		}
	}


	//Recap of what we did:
	//1.We got all the Adjacent incides from the AI
	//2.We went to through each AIAdjacentIncides and found 1 player we are adjacent to
	//3.We check through each of his adjacent indices and removed the common houses that we had with the AI
	//4.We added house for the AI surrounding p0

	//END PART 1

	//PART 2 START

	Player * pAI2 = vector_player[2]; //AI player?

	int indexToBuy = -1; //contains the index to buy a house in
	vector<int> pAIHouseIndices = *(pAI2->getHouseManager()->getHouseIndices()); //player house vertices

	//This loop checks every the hard coded adjacent indices to see if AI has all of the 
	//adjacent indices, but not the index that is adjacent to them all
	int mapsize = 42;
	for (int i = 0; i < mapsize; i++) {
		vector<int> adjacentIndices = mapOfPlayersCity->getMap()->getAdjacentIndices(i); //hard coded adjacent indices to index i
		bool notFound = false; //used if 1 adjacent vertex is not found, to skip to the next index

		//if the player already own a house at index i, then skip
		if (mapOfPlayersCity->ownsHouse(pAI2->getColor(), i)) {
			continue;
		}

		//This loop checks if the player owns all the adjacent indices to an index
		//it stops when if the player does not own one of adjacent indices
		for (int index : adjacentIndices) {
			//find index in the houses
			std::vector<int>::iterator position = std::find(pAIHouseIndices.begin(), pAIHouseIndices.end(), index);
			if (position == pAIHouseIndices.end()) {
				notFound == true;
				break;
			}
		}
		//one of them was not found, then go to the next index in the map
		if (notFound) {
			continue; //goto next index in the map
		}
		else {
			//index was found
			indexToBuy = i;
			break; //get out of loop to buy house
		}
	}

	if (indexToBuy == -1) {
		cout << "THERE IS NO INDEX THAT IS ADJACENT TO ALL OF THE OTHER INDICES" << endl;
	}
	else {
		double shorestPathCost = 99999; //set to very big value

		//get the shorest path from all the owned house indices to the index to buy to
		for (int houseIndex : pAIHouseIndices) {
			//get cost of path to buy to index
			double costToIndex = mapOfPlayersCity->getMap()->getCostTo(indexToBuy);

			//if we find a lower cost, then change the cost
			if (costToIndex < shorestPathCost) {
				shorestPathCost = costToIndex;
			}
		}


		//Add house section
		pAI2->subtractMoney((int)shorestPathCost + mapOfPlayersCity->costToBuildHouse(indexToBuy)); //substract shortest path cost + house cost
		House house(indexToBuy, mapOfPlayersCity->getIndexName(indexToBuy)); //create house
		p0->getHouseManager()->addHouses(house); //add house to player
		mapOfPlayersCity->setPlayerHouse(indexToBuy, pAI2->getColor()); //add house in map
	}

	//END OF PART 2


	//PART 3 START

	Player * pAI3 = vector_player[2]; //AI player?
	//RANDOMLY CHOOSE IF THE AI IS GOING TO BUY OR NOT
	srand(time(NULL)); //initialize the random number generator to so it is truly random. Source: http://www.cplusplus.com/forum/beginner/26611/
	int start = rand() % 2; //generates a random number between 0 and 1, 50% chance to start
	bool enoughMoney = true;

	if (start == 0) {
		cout << "The AI will try to replay" << endl;
	}
	else {
		cout << "The AI will not play" << endl;
	}

	//if start == 0, then play, else don't play
	while (enoughMoney && start == 0) {

		pair<vector<double>, vector<list<int> > > costAndPath = mapOfPlayersCity->getAvailableIndicesCost(pAI3->getHouseManager()->getHouseIndices(), pAI3->getElektro());
		vector<double> costVector = costAndPath.first;
		vector<list<int> > pathVector = costAndPath.second;

		//If there is no free city to put a house in
		if (costAndPath == pair<vector<double>, vector<list<int> > >()) {
			cout << "Player " << pAI3->getColor() << "There is no city in that map that is free to play." << endl;
			enoughMoney = false;
			break;
		}

		else {
			cout << endl << "You currently have " << pAI3->getElektro() << " elektro" << endl;
			cout << "These are the houses you can purchase: " << endl;

			//print indices
			mapOfPlayersCity->printAvailableIndicesCost(pAI3->getHouseManager()->getHouseIndices(), pAI3->getElektro());

			//I DID THE RANDOMLY GENERATED INDEX
			//Get input from the AI
			int RandIndex = rand() % costVector.size(); //generates a random number between 0 and size of available indices

			cout << "You are purchasing the house at Index " << RandIndex << endl;


			//Go from the shortest path and build houses that the player 
			//does not currently own and have an empty space
			for (int index : pathVector[RandIndex]) {

				//if the player does not currently own the house and the city is free to build then build house
				if (mapOfPlayersCity->playerOwnsHouseAndCityHasEmptySpace(pAI3->getHouseManager()->getHouseIndices(), index)) {

					House house(index, mapOfPlayersCity->getIndexName(index)); //create house
					pAI3->getHouseManager()->addHouses(house); //add house to player
					mapOfPlayersCity->setPlayerHouse(index, pAI3->getColor()); //add house in map
					cout << "House index " << index << " name: " << mapOfPlayersCity->getIndexName(index) << " purchased" << endl;
				}

			}

			//Get cost of purchase of the index the player wants to purchase
			int costOfPurchase = (int)costVector[RandIndex];
			pAI3->subtractMoney(costOfPurchase); //substract elektro

			cout << endl << "Map presentation: " << endl;
			mapOfPlayersCity->printPlayersCity();
			cout << endl << "Purchase completed" << endl;
			cout << "You now have " << pAI3->getElektro() << " elektro" << endl;

			start = rand() % 2; //generates a random number between 0 and 1, 50% chance to start
			cout << "The AI will try to replay" << endl;
		}
	}

	//END OF PART 3

}



/* Step 5 - Bureaucracy. Use bought resources to power electricity to how many houses. Those resources go back in the market.
  Depending on how many houses they've powered, they will generate a certain amount of money.
  We are at phase 1 until someone builds the 7th house. Then phase 2 ends when phase 3 card is drawn. Also, during phase 1 and 2, we must place the
  highest power plant under the stack. On the other hand, in phase 3, we will move the lowest power plant under the stack.*/
void Board::bureaucracy() {
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


void Board::resourcePurchase(string materialType) {

}

//Returns next player
Player * Board::getNextPlayer(Player & p) {
	if (&p == &*vector_player[0]) {
		return vector_player[1];
	}
	return vector_player[0];

}

void Board::loadGame()
{
	IOFile::loadMap(mapOfPlayersCity);
	IOFile::loadPowerplants(powerplants_Vector);
	IOFile::loadNbPlayersAndTurnCoutner(nbOfPlayer, turnCounter);
	market->loadMarket();
}

void Board::saveGame()
{
	IOFile::saveAreas(mapOfPlayersCity);
	IOFile::saveMap(mapOfPlayersCity);
	IOFile::saveNbPlayerAndTurnCounter(nbOfPlayer, turnCounter);
	IOFile::savePlayer(*vector_player[0], *vector_player[1]);
	IOFile::savePowerplants(powerplants_Vector);
	market->saveMarket();
}

void Board::incrementTurnCounter() {
	turnCounter++;
}

bool Board::checkMapCorrectness() {

	bool mapCorrect = IOFile::verifyMapCorrectness(mapOfPlayersCity);
	if (mapCorrect) {
		return true;
	}
	return false;
}


//Keeps track of the number of houses each player has (the scoring track on top of the board game)
void Board::houseScoringTrack() {
	for (Player* p : vector_player) {
		cout << "PLAYER " << p->getColor() << " has " << p->getHouseManager()->getHouseCount() << " number of house(s)." << endl << endl;
	}
}


//Prompt asking you to choose the index you want to build in. Used in building phase
pair<int, int> Board::pleaseChooseIndexToBuildIn(vector<list<int> > vectorListOfPaths) {

	pair<int, int> indexPositionPair;
	int index;
	int positionOfIndex;

	cout << endl << "Please choose an Index you want to build in" << endl;
	cout << "Index: ";
	cin >> index;

	//check if user put anything other than integer
	while (std::cin.fail()) {
		cout << "Invalid input. Please enter an integer: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> index;
	}

	//Gets all the possible destination indices from the vectorlist
	vector<int> destinationIndices;
	for (list<int> listPath : vectorListOfPaths) {
		destinationIndices.push_back(listPath.back());
	}

	//Gets the index the player wants to build (checks if the index is valid also)
	while (true) {
		std::vector<int>::iterator position = std::find(destinationIndices.begin(), destinationIndices.end(), index);
		//If the vector does not contain the city index, then ask player to enter an index again
		if (position == destinationIndices.end())
		{
			// Element not in vector
			cout << "Invalid integer.. Please enter a valid index: ";
			cin >> index;
			continue;
		}
		//The index is valid
		else {
			positionOfIndex = position - destinationIndices.begin(); //index of the iterator

			indexPositionPair.first = index; //set map index
			indexPositionPair.second = positionOfIndex; //set position or the index in the vectorList
			break;
		}
	}

	return indexPositionPair;
}

//Prompt asking you to choose the index you want to build in. Used in building phase
int Board::pleaseChooseIndexToBuildIn() {
	cout << endl << "Please choose an Index you want to build in" << endl;
	cout << "Index: ";
	int index;
	cin >> index;

	//check if user put anything other than integer
	while (std::cin.fail()) {
		cout << "Invalid input. Please enter an integer: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> index;
	}

	//Check if the index is available before inserting
	while (!mapOfPlayersCity->isIndexAvailable(index)) {
		cout << "Invalid integer.. Please enter a valid index: ";
		cin >> index;
	}

	return index;
}