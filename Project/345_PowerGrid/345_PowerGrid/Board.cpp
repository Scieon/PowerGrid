#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>

#include "Board.h"
#include "PowerPlant.h"
#include "Resource.h"
#include "PowerPlantManager.h"
#include "Map.h"
#include "MapOfPlayersCity.h"


using namespace std;

//Default constructor
Board::Board() {
	turnCounter = 1; //keep track round number
	nbOfPlayer = 0; //how many people are playing in this game. for now we will have 2 only.
	market = new ResourceMarket();
	powerplants_Vector = new PowerplantManager();
	mapOfPlayersCity = new MapOfPlayersCity();
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


		/*
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
		*/

		cout << "The player with the most houses will start. If tied, biggest powerplant number will go. " << endl;
		void reorderPlayersHighestNumHouses();

	}
}

/*Step2 - Print to the first player and ask him to buy a powerplant, then ask the other players. On the first round, everyone will have to buy
 a power plant. Later on, we will implement the auction. */
void Board::buyPowerPlant() {

	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS SECOND STEP THE BUYING OF POWER PLANTS" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;


	int winnerOfAuction; 
	int intialPlantValue; //Keeping plant minimum bid to search for it 

	//Reseting the statuses of every player at begining of phase 2
	for (int i = 0; i < getNumberOfPlayers(); i++) {
		vector_player[i]->hasAuction = false;
		vector_player[i]->hasBought = false;
	}

	//Giving every player a chance to buy a powerplant
	for (int i = 0; i < getNumberOfPlayers(); i++) {

		//Helper variables to validate that player can purchase powerplant
		bool checkPP = false; 
		bool checkElektro = false;

		int tracker = i; //Counter for players that still want to auction
		int plantBid; //Players bid on given plant
		Player * p = vector_player[i]; //Player currently auctioning

		//Resetting auctioning statuses
		for (int i = 0; i < getNumberOfPlayers(); i++) {
			vector_player[i]->hasAuction = false; //Maybe delete this line
			vector_player[i]->hasAuction = vector_player[i]->hasBought;
		}

		//Skip player that has bought
		if (vector_player[i]->hasBought == true) {
			cout << vector_player[i]->getColor() << " has already bought a powerplant." << endl;
			p->hasAuction = true;
			continue;
		}

		//Fail-safe band-aid fix 
		if (i > 0) {
			if (vector_player[i - 1]->hasBought == true)
				tracker--;
		}

		cout << "Player with color " << p->getColor() << " can bid first " << endl;
		powerplants_Vector->printMarket();
		cout << "\nPlayer " << p->getColor() << endl;

		string decisionToPurchase = "";

		//If its not the first turn give the player an option to decline buying plants
		if (turnCounter > 1) {
			while (decisionToPurchase != "y" && decisionToPurchase != "n") {
				cout << "Do you wish to buy any powerplants (y/n): ";
				cin >> decisionToPurchase; cout << endl;
			}

			if (decisionToPurchase == "n") {
				cout << "Player " << p->getColor() << " has decided not to buy a power plant." << endl;
				system("pause");
				p->hasBought = true;
				continue;
			}
		}
	

		//Player selects a powerplant to buy
		while (checkPP == false || checkElektro == false) {

			cout << "You currently have " << p->getElektro() << " elektros" << endl;
			cout << "Please enter the minimum bid of the Power Plant you want from the Actual Market" << endl;
			cout << "Power Plant minimum bid: " << endl;

			cin >> plantBid;

			intialPlantValue = plantBid;
	
			checkPP = powerplants_Vector->isPowerplantInActualMarket(plantBid);
			checkElektro = p->getElektro() > plantBid;

			if (checkPP == false) {
				cout << endl;
				cout << "--ERROR-- This powerplant is not in the Actual Market --ERROR--" << endl << endl;
			}
			else if (checkElektro == false) {
				cout << endl;
				cout << "--ERROR-- You do not have enough elektros for this Power Plant --ERROR--" << endl;
			}

		}

	
		//Everyone after current player still auctioning
		while (tracker != getNumberOfPlayers()) {
			int nbPlayerAuctioned = getNumberOfPlayersThatHaveAucitoned();

			if (tracker == getNumberOfPlayers() - 1
				|| getNumberOfPlayers() - nbPlayerAuctioned == 1) {
				int winnerIndex = 0;

				//Independent for loop searching for winner of auction
				for (int k = 0; k < getNumberOfPlayers(); k++) {
					if (vector_player[k]->hasAuction == false)
						winnerOfAuction = winnerIndex;
					winnerIndex++;
				}
				break;
			}
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			cout << "@@@@ Starting Auction @@@@" << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

			string answer;
			int playerBid;

			p = getNextPlayer(*p);
			while (p->hasAuction == true) {
			//	cout << "Player " << p->getColor() << " has given up auctioning" << endl; system("pause");
				p = getNextPlayer(*p);
			}
			cout << endl;
	
			if (p->getElektro() < plantBid) {
				cout << "Player " << p->getColor() << endl;
				cout << "You do not have enough elektros to bid" << endl;
				tracker++;
				p->hasAuction = true;
				continue;
			}

			//At this point the player has been validated to auction
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

				//Forfeit right to auction if wrong input. 
				if (bidTooLow) {
					cout << endl;
					cout << "Your bid is too low" << endl;
					p->hasAuction = true;
					tracker++;
				}
				else if (notEnoughElektro) {
					cout << endl;
					cout << "Your bid is too high" << endl;
					p->hasAuction = true;
					tracker++;
				}

				if (bidTooLow == false && notEnoughElektro == false) {
					//Player has entered valid bid.
					plantBid = playerBid;
					cout << "Bid has changed too: " << plantBid << endl; cout << endl;
				}

			}//End if yes

			if (answer == "n") {
				tracker++;
				p->hasAuction = true;
			}

		} //end while auction

		//At this point tracker should be 2 i.e., everyone has taken a chance at auctioning
		cout << "Player " << vector_player[winnerOfAuction]->getColor() << " has won powerplant " << intialPlantValue << endl;
		vector_player[winnerOfAuction]->hasBought = true;
		vector_player[winnerOfAuction]->addPlant(powerplants_Vector->getAndRemoveSpecificPowerplant(intialPlantValue));
		vector_player[winnerOfAuction]->subtractMoney(plantBid);
		system("pause");

	} //end for 


	//Anyone who lost in the auction but may still want to buy
	for (int i = 0; i < getNumberOfPlayers(); i++) {

		Player * p = vector_player[i];
		string choice;
		int plantBid;
		string decisionToPurchase = "";
		bool checkPP = false;
		bool checkElektro = false;


		if (p->hasBought == false) {

			if (turnCounter > 1) {
				cout << "Player with color " << p->getColor() << " do you still wish to buy a plant? (y/n) " << endl;
				cin >> choice;

				if (choice == "n")
					break;

				else if (choice == "y") {

					powerplants_Vector->printMarket();
					cout << "Select a plant to buy from the market: " << endl;
					cin >> plantBid;


					if (powerplants_Vector->isPowerplantInActualMarket(plantBid) == false) {
						cout << endl;
						cout << "--ERROR-- This powerplant is not in the Actual Market --ERROR--" << endl << endl;
						break;
					}
					else if (p->getElektro()>plantBid == false) {
						cout << endl;
						cout << "--ERROR-- You do not have enough elektros for this Power Plant --ERROR--" << endl;
						break;
					}
					cout << "You have bought plant " << plantBid << endl;
					p->addPlant(powerplants_Vector->getAndRemoveSpecificPowerplant(plantBid));
					p->subtractMoney(plantBid);
					system("pause");
				}
			}

			 if (turnCounter == 1) {
		
				 while (checkPP == false || checkElektro == false) {
					 powerplants_Vector->printMarket();
					 cout << "Since this is the first turn, player " << p->getColor() << " must buy a plant." << endl;
					 cout << "Select a plant to buy from the market: " << endl;
					 cin >> plantBid;

					 checkPP = powerplants_Vector->isPowerplantInActualMarket(plantBid);
					 checkElektro = p->getElektro() > plantBid;

					 if (checkPP == false) {
						 cout << endl;
						 cout << "--ERROR-- This powerplant is not in the Actual Market --ERROR--" << endl << endl;
						 system("pause");
					 }
					 else if (checkElektro == false) {
						 cout << endl;
						 cout << "--ERROR-- You do not have enough elektros for this Power Plant --ERROR--" << endl;
						 system("pause");
					 }
				 }

				 cout << "You have bought plant " << plantBid << endl;
				 p->addPlant(powerplants_Vector->getAndRemoveSpecificPowerplant(plantBid));
				 p->subtractMoney(plantBid);
				 system("pause");
			} //end of turn 1
		
		}

	}


	//if step3 card has been found
	if (powerplants_Vector->getStep3Trigger()) {
		cout << "Step 3 has started" << endl;
		powerplants_Vector->getAndRemoveSpecificPowerplant(999999);
		setStep3();
		powerplants_Vector->setStep3Trigger(false);//to avoid conflict if it stays true
	}

	//First round will tell if there is an order change depending who bought the highest power plant
	if (turnCounter == 1) {
		reOrderHighestPlayerPwp();
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

					p->subtractMoney(mapOfPlayersCity->costToBuildHouse(index)); //remove money depending on the cost to build the house
					p->getHouseManager()->addHouses(house);
					mapOfPlayersCity->setPlayerHouse(index, p->getColor());
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

	//Reorder the market according to the highest number of houses
	//activate step3 if conditions are met
	powerplants_Vector->buildingPhaseReorder(getHighestNumHousesOfPlayers());

	//Set step2 if we are not in step2 or in step3 already, and we have more than 7 houses
	if (!step2 && !step3 && getHighestNumHousesOfPlayers() >= 7 ) {
		setStep2();
	}

	//if step3 has been triggered then set step3 to all and put the trigger back to false
	if (powerplants_Vector->getStep3Trigger()) {
		cout << "Step 3 has started..." << endl;
		setStep3();
		powerplants_Vector->setStep3Trigger(false);//to avoid conflict if it stays true
	}

	if (getHighestNumHousesOfPlayers() >= 17) {
		endGameTriggered = true;
		cout << "End game has been triggered! At least 1 player has 17 houses or more" << endl;
	}

}

/* Step 5 - Bureaucracy. Use bought resources to power electricity to how many houses. Those resources go back in the market.
  Depending on how many houses they've powered, they will generate a certain amount of money.
  We are at phase 1 until someone builds the 7th house. Then phase 2 ends when phase 3 card is drawn. Also, during phase 1 and 2, we must place the
  highest power plant under the stack. On the other hand, in phase 3, we will move the lowest power plant under the stack.*/
void Board::bureaucracy() {
	cout << " ///////////////////////////////////////////////////////" << endl;
	cout << " THIS IS FIFTH STEP THE BUREAUCRACY" << endl;
	cout << " ///////////////////////////////////////////////////////" << endl;

	string decisionToPower;

	reverse(vector_player.begin(), vector_player.end());
	for (Player* p : vector_player) {

		int poweredPlants[3] = { -1,-1,-1 }; //No powered plants initially
		//player gets the money depending on how many houses they have powered. Even if they don't power any houses, they will automatically get 10 elektro.
		//Not going to power every single house they have bought, but in this case we will leave it as it is. They should be able to choose how many houses 
		//they are going to power based on their resources.
		cout << "*****************************************************************" << endl;
		cout << "PLAYER " << p->getColor() << " has " << p->getHouseManager()->getHouseCount() << " houses." << endl;
		cout << "Please note you can only power as many cities as you own. Any exceeding that will be wasted resources." << endl;
		cout << "Do you wish to power any cities(Yes/No): ";
		cin >> decisionToPower; cout << endl;


		//Player chooses to power cities
		if (decisionToPower == "Yes" || decisionToPower == "yes" || decisionToPower == "YES" || decisionToPower == "y") {
			int choice = -1;
			int nbCitiesPowered = 0;

			//If player has no houses than they just get 10 elektros
			if (p->getNumberHouses() == 0) {
				choice = 0;
				cout << "No cities to supply power to!" << endl;
			}

			while (choice != 0) {
				p->showInfo();
				p->showPlantsToPower();
				cout << "Please select a plant to power (Enter 0 if finished): "; //Need to have something if no plants shown immediately break
				cin >> choice;
				cout << endl;

				if (p->validatePlantPossession(choice) == true) {

					//Checking for unique plants
					for (int i = 0; i <= 2; i++) {
						if (poweredPlants[i] == -1) {
							poweredPlants[i] = choice;

							p->powerCity(choice);
							nbCitiesPowered += p->getPowerplantPower(choice);

							cout << "You have powered " << nbCitiesPowered << " cities so far." << endl << endl;
							break;
						}
						else if (poweredPlants[i] == choice) {
							cout << "You have already powered that plant!" << endl << endl;
							break;
						}
					}//End of for
				}///End of if

				else if (choice != 0) {
					cout << "Invalid choice" << endl << endl;
				}
				system("pause");
			}

			if (nbCitiesPowered > p->getNumberHouses()) {
				cout << "You can only power as many cities as you own." << endl;
				nbCitiesPowered = p->getNumberHouses();
			}
			p->getPaid(nbCitiesPowered);
		}
		//Player chooses to power no cities
		else {
			p->getPaid(10);
		}
	}

	system("pause");
	//Replenish Resource Market according to step
	if (step2 == true)
		market->refill(2, getNumberOfPlayers());

	else if (step3 == true)
		market->refill(3, getNumberOfPlayers());

	else if (step2 == false && step3 == false)
		market->refill(1, getNumberOfPlayers());
	else {
		cout << "Error what step are we in??";
		system("pause");
		system("EXIT");
	}

	//Place the highest numbered powerplant at the end of the list
	if (!step3) {
		powerplants_Vector->bureaucracyPhaseReorder();
		if (powerplants_Vector->getStep3Trigger()) {
			cout << "Step 3 has started..." << endl;
			setStep3();
			powerplants_Vector->setStep3Trigger(false);//to avoid conflict if it stays true
		}
	}
	//step 3 remove the lowest powerplant
	else {
		powerplants_Vector->removeLowestPowerplant();
	}

	turnCounter++; //the first round going through this will be different then afterwards it will become the same
}

int Board::getNumberOfPlayers() {
	return nbOfPlayer;
}

int Board::getNumberOfPlayersThatHaveAucitoned() {
	int i = 0;
	for (Player* p : vector_player) {
		if (p->hasAuction) {
			i++;
		}
	}
	return i;
}

//Returns next player
Player * Board::getNextPlayer(Player & p) {
	if (&p == &*vector_player[0]) {
		return vector_player[1];
	}
	if (getNumberOfPlayers() == 3) {
		if (&p == &*vector_player[1]) {
			return vector_player[2];
		}
	}
	return vector_player[0];

}

void Board::loadGame()
{
	loadMap();
	loadPowerplants();
	loadNbPlayersAndTurnCoutner();
	loadPlayer();
	market->loadMarket();
}

void Board::saveGame()
{
	saveMap();
	saveNbPlayerAndTurnCounter();
	savePlayer();
	savePowerplants();
	market->saveMarket();
}

void Board::incrementTurnCounter() {
	turnCounter++;
}

bool Board::checkMapCorrectness() {

	vector<int> game_indices = mapOfPlayersCity->getMap()->getPlayedIndicesVector();
	vector<vector<string> > * player_houses = mapOfPlayersCity->getPlayerHousesVector();

	vector<int> * indicesNotInGame = new vector<int>();

	//finds the indices that we are not playing and stores it in indicesNotInGame
	for (unsigned int i = 0; i < player_houses->size(); i++) {

		bool integerIsInGameIndices = find(game_indices.begin(), game_indices.end(), i) != game_indices.end();

		if (integerIsInGameIndices) {
			continue; //present
		}
		else {
			indicesNotInGame->push_back(i); //not present
		}
	}


	//If there is a player in an location where we are not playing
	for (int index : *indicesNotInGame) {
		if ((*player_houses)[index].size() != 0) {
			delete indicesNotInGame;
			indicesNotInGame = NULL;
			return false;
			//Map is not correct, there is player in index not in game
		}
	}

	delete indicesNotInGame;
	indicesNotInGame = NULL;
	return true;
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

// Selection sort function that re-orders the players with the highest number of houses
void Board::reorderPlayersHighestNumHouses() {
	int indexOfNextHighest = 0; //default
	int index = 0; //default
	indexOfHighest(vector_player, index);
	for (Player* p : vector_player) {
		indexOfNextHighest = indexOfHighest(vector_player, index);
		swapValues(*vector_player[index], *vector_player[indexOfNextHighest]);
		index++;
	}

	for (Player* p : vector_player) {
		cout << "PLAYER " << p->getColor() << " has " << p->getHouseManager()->getHouseCount() << " number of house(s)." << endl;
	}
}



// Follows the reorderPlayersHighestNumHouses() to find the highest index
int Board::indexOfHighest(vector<Player*> vector, int startIndex) {
	int maxHouse = vector[startIndex]->getHouseManager()->getHouseCount();
	int maxPowerplant = vector[startIndex]->getHighestMinBid();
	int indexOfMax = startIndex;

	for (int index = startIndex + 1; index < vector.size(); index++) {

		if (vector[index]->getHouseManager()->getHouseCount() > maxHouse) {
			maxHouse = vector[index]->getHouseManager()->getHouseCount();
			indexOfMax = index;
		}

		else if (vector[index]->getHouseManager()->getHouseCount() == maxHouse) {

			if (vector[index]->getHighestMinBid() > maxPowerplant) {
				maxPowerplant = vector[index]->getHighestMinBid();
				indexOfMax = index;
			}
		}
	}
	return indexOfMax;
}

// Follows the reorderPlayersHighestNumHouses() to swap the players in the proper order
void Board::swapValues(Player& p1, Player& p2) {
	Player temp;
	temp = p1;
	p1 = p2;
	p2 = temp;
}

//Sets step3 to true to all classes that need it
void Board::setStep3() {
	step3 = true;
	mapOfPlayersCity->setStep3(true);
	powerplants_Vector->setStep3(true);
}

void Board::setStep2()
{
	step2 = true;
	mapOfPlayersCity->setStep2(true);
}

//returns highest number of houses of a player
int Board::getHighestNumHousesOfPlayers()
{
	int maxHouse = -1;

	for (Player* player : vector_player) {
		int houseCount = player->getNumberHouses();

		if (houseCount > maxHouse) {
			maxHouse = houseCount;
		}
	}

	return maxHouse;

}

void Board::savePlayer() {
	ofstream output;
	// Create/open a file
	output.open("player.txt");

	//counter
	int i = 1;
	for (Player* p : vector_player) {
		vector<House> vec_house1 = p->getHouseManager()->getHouseVector();
		vector<Powerplant> vec_pp1 = *p->getPowerplantsVector();

		cout << "Saving Player " << i << endl;
		output << "Player1" << endl;
		output << "Elektro=" << p->getElektro() << endl;
		output << "Color=" << p->getColor() << endl;
		output << "Coal=" << p->getResource("Coal") << endl;
		output << "Oil=" << p->getResource("Oil") << endl;
		output << "Garbage=" << p->getResource("Garbage") << endl;
		output << "Uranium=" << p->getResource("Uranium") << endl;

		output << "Player_Houses:" << endl;
		for (House house : vec_house1) {
			output << house.getIndex() << "," << house.getLocation() << endl;
		}
		output << "End_Player_Houses" << endl;

		output << "Player_Powerplants" << endl;
		for (Powerplant pp : vec_pp1) {
			output << "Bid=" << pp.getBid() <<
				" Type=" << pp.getType() <<
				" Resource_required=" << pp.getResourceReq() <<
				" Cities_powered=" << pp.getCitiesPowered() <<
				endl;
		}
		output << "End_Player_Powerplants" << endl;

		cout << "Player " << i << " saved" << endl;
	}

	output.close();
}

void Board::loadPlayer() {

	ifstream input("player.txt");

	string line;
	int pos;

	vector_player = vector<Player*>(); //create 3 new players
	Player * p1 = new Player("not important");
	Player * p2 = new Player("not important");
	Player * p3 = new Player("not important");

	vector_player.push_back(p1);
	vector_player.push_back(p2);
	vector_player.push_back(p3);

	for (Player* p : vector_player) {
	
		input >> line; //Player#


		input >> line;
		pos = line.find("=");
		p->setElektro(stoi(line.substr(pos + 1))); //elektro

		input >> line;
		pos = line.find("=");
		p->setColor(line.substr(pos + 1)); //Color

		input >> line;
		pos = line.find("=");
		p->addResource("Coal", stoi(line.substr(pos + 1))); //coal

		input >> line;
		pos = line.find("=");
		p->addResource("Oil", stoi(line.substr(pos + 1))); //oil

		input >> line;
		pos = line.find("=");
		p->addResource("Garbage", stoi(line.substr(pos + 1))); //garbage

		input >> line;
		pos = line.find("=");
		p->addResource("Uranium", stoi(line.substr(pos + 1))); //uranium

		input >> line; //Player_Houses:

		input >> line;

		while (line != "End_Player_Houses") {

			pos = line.find(",");
			int index = stoi(line.substr(0, pos)); //get index
			string location = line.substr(pos + 1); //get location

			House * house = new House(index, location);
			p->getHouseManager()->addHouses(*house);
			input >> line;
		}
		input >> line; //End_Player_Houses
		input >> line; //Player_Powerplants

		while (line != "End_Player_Powerplants") {

			int min_bid;
			string type;
			int resource_required;
			int city_powered;

			pos = line.find("=");
			min_bid = stoi(line.substr(pos + 1));

			input >> line;

			pos = line.find("=");
			type = line.substr(pos + 1);

			input >> line;

			pos = line.find("=");
			resource_required = stoi(line.substr(pos + 1));

			input >> line;

			pos = line.find("=");
			city_powered = stoi(line.substr(pos + 1));

			p->addPlant(new Powerplant(min_bid, type, resource_required, city_powered));

			input >> line;
			
		}
	
	}

	input.close();
}

//saves the areas and the Map
void Board::saveMap() {

	//save areas
	ofstream outputAreas;
	// Create/open a file
	outputAreas.open("area.txt");

	outputAreas << "Areas" << endl;
	//Save map areas
	vector<bool> values(*(mapOfPlayersCity->getMap()->getAreasPlayed())); //shallow copy
	int i = 0;//counter
	for (bool val : values) {
		if (val) {
			outputAreas << i << endl;
		}
		i++;
	}

	outputAreas << endl;
	outputAreas.close();

	//
	//save map part
	//
	vector<vector<string> > * player_houses = mapOfPlayersCity->getPlayerHousesVector();

	ofstream outputMap;
	// Create/open a file
	outputMap.open("map.txt");
	cout << "Saving map..." << endl;

	//Saves player houses
	for (unsigned int i = 0; i < player_houses->size(); i++) {
		if ((*player_houses)[i].size() == 0) {
			outputMap << i << endl;
		}
		else if ((*player_houses)[i].size() == 1) {
			outputMap << i << "," << (*player_houses)[i][0] << endl;
		}
		else if ((*player_houses)[i].size() == 2) {
			outputMap << i << "," << (*player_houses)[i][0] << "," << (*player_houses)[i][1] << endl;
		}
		else if ((*player_houses)[i].size() == 3) {
			outputMap << i << "," << (*player_houses)[i][0] << "," << (*player_houses)[i][1] << "," << (*player_houses)[i][2] << endl;
		}
	}


	cout << "Map saved..." << endl;
	outputMap.close();
}

void Board::loadMap() {

	ifstream inputAreas("area.txt");;
	string line;
	inputAreas >> line; //Areas
	inputAreas >> line;

	int i1 = stoi(line); //area1
	inputAreas >> line;
	int i2 = stoi(line); //area2
	inputAreas >> line;
	int i3 = stoi(line); //area3

	Area * a1 = new Area(i1);
	Area * a2 = new Area(i2);
	Area * a3 = new Area(i3);

	//Used for areamanager constructor
	vector<Area> * areas = new vector<Area>();
	areas->push_back(*a1);
	areas->push_back(*a2);
	areas->push_back(*a3);

	inputAreas.close();

	AreaManager * area_manager = new AreaManager(); //do not delete
	area_manager->setGameAreas(*areas); //load areas
	Map *gameMap = new Map(area_manager); //load map

	mapOfPlayersCity = new MapOfPlayersCity(gameMap); //load the areas into the map

	//
	//Load map section
	//
	ifstream inputMap("map.txt");

	vector<vector<string> > * loadMap = new vector<vector<string> >(42);

	string skip;

	//Fills up loadMap vector from map.txt
	while (!inputMap.eof()) {

		inputMap >> skip;

		//splits the string with the delimiter ','
		vector<string> internal;
		stringstream ss(skip); // Turn the string into a stream.
		string tok;
		//put string into vector
		while (getline(ss, tok, ',')) {
			internal.push_back(tok);
		}

		//get the index
		int index = stoi(internal[0]);

		//no player
		if (internal.size() == 1) {

		}
		//1 player
		else if (internal.size() == 2) {

			(*loadMap)[index].push_back(internal[1]);
		}
		//2 player
		else if (internal.size() == 3) {

			(*loadMap)[index].push_back(internal[1]);
			(*loadMap)[index].push_back(internal[2]);
		}
		//3 player
		else if (internal.size() == 4) {

			(*loadMap)[index].push_back(internal[1]);
			(*loadMap)[index].push_back(internal[2]);
			(*loadMap)[index].push_back(internal[3]);
		}
	}


	//Loads the players into map 
	mapOfPlayersCity->loadPlayerHouses(*loadMap); 

	delete loadMap;
	loadMap = NULL;

	inputMap.close();
}


void Board::savePowerplants()
{
	ofstream output;
	// Create/open a file
	output.open("powerplant.txt");

	output << "Powerplants" << endl;
	vector<Powerplant> * ppVector = powerplants_Vector->getPowerplantVector();

	for (Powerplant pp : *ppVector) {
		output << "Bid=" << pp.getBid() <<
			" Type=" << pp.getType() <<
			" Resource_required=" << pp.getResourceReq() <<
			" Cities_powered=" << pp.getCitiesPowered() <<
			endl;
	}
	output.close();
}

void Board::loadPowerplants()
{
	ifstream input;
	// Create/open a file
	input.open("powerplant.txt");

	vector<Powerplant> * pp_vector = new vector<Powerplant>();
	int pos; //position
	string line;

	input >> line; //powerplants
	input >> line;
	while (!input.eof()) {

		int min_bid;
		string type;
		int resource_required;
		int city_powered;

		pos = line.find("=");
		min_bid = stoi(line.substr(pos + 1));

		input >> line;

		pos = line.find("=");
		type = line.substr(pos + 1);

		input >> line;

		pos = line.find("=");
		resource_required = stoi(line.substr(pos + 1));

		input >> line;

		pos = line.find("=");
		city_powered = stoi(line.substr(pos + 1));

		pp_vector->push_back(*new Powerplant(min_bid, type, resource_required, city_powered));

		input >> line;
	}

	powerplants_Vector->setPowerplantVector(pp_vector);

	input.close();
}


void Board::saveNbPlayerAndTurnCounter()
{
	ofstream output;
	// Create/open a file
	output.open("nbPlayerAndTurn.txt");

	output << "NbOfPlayers=" << nbOfPlayer << endl;
	output << "TurnCount=" << turnCounter << endl;

	output.close();
}

void Board::loadNbPlayersAndTurnCoutner()
{
	ifstream input;
	// Create/open a file
	input.open("nbPlayerAndTurn.txt");

	string line;
	int pos;

	input >> line; //NbOfPlayers
	pos = line.find("=");
	nbOfPlayer = stoi(line.substr(pos + 1));

	input >> line;

	pos = line.find("="); //TurnCount
	turnCounter = stoi(line.substr(pos + 1));

	input.close();
}

// Selection sort function that re-orders the players with the highest number of houses
void Board::reOrderHighestPlayerPwp() {
	int indexOfNextHighest = 0; //default
	int index = 0; //default
	indexOfHighest(vector_player, index);
	for (Player* p : vector_player) {
		indexOfNextHighest = indexOfHighest(vector_player, index);
		swapValues(*vector_player[index], *vector_player[indexOfNextHighest]);
		index++;
	}

	for (Player* p : vector_player) {
		cout << "PLAYER " << p->getColor() << " has " << p->getHighestMinBid() << " as their highest powerplant." << endl;
	}
}

// Find the highest index of powerplant
int Board::indexOfHighestPwp(vector<Player*> vector, int startIndex) {
	int maxPowerplant = vector[startIndex]->getHighestMinBid();
	int indexOfMax = startIndex;

	for (int index = startIndex + 1; index < vector.size(); index++) {

		if (vector[index]->getHighestMinBid() > maxPowerplant) {
			maxPowerplant = vector[index]->getHighestMinBid();
			indexOfMax = index;
		}
	}
	return indexOfMax;
}