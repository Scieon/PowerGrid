#include "BasicStatistics.h"
#include <string>
#include <fstream>

//Default Constructor
BasicStatistics::BasicStatistics() {}

//Constructor attaching this observer onto subject by calling super constructor
BasicStatistics::BasicStatistics(Board * board) : Statistics(board) {

}

BasicStatistics::~BasicStatistics() {

}

//Update method called when observers are to be notified
void BasicStatistics::update() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);
	cout << getType() << " Statistics -----------\n\n";
	this->printStatistics();
}

//Displays real time game statistics only showing basic information
void BasicStatistics::printStatistics() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);

	//Board Attributes
	vector<Player*> players = subject->vector_player;
	PowerplantManager * powerplants = subject->powerplants_Vector;
	ResourceMarket * market = subject->market;

	//Looping through the amount of players displaying respective statistics on each player
	for (int i = 0; i < subject->getNumberOfPlayers(); i++) {
 
		cout << "Player " << players[i]->getColor() << " has " << players[i]->getHouseManager()->getHouseCount() << " number of house(s)." << endl;
		output << "Player " << players[i]->getColor() << " has " << players[i]->getHouseManager()->getHouseCount() << " number of house(s)." << endl;
		int total = players[i]->getResource("Coal") + players[i]->getResource("Garbage") + players[i]->getResource("Oil") + players[i]->getResource("Uranium");
		cout << "Player " << players[i]->getColor() << " has a total of " << total << " resources." << endl << endl;
		output << "Player " << players[i]->getColor() << " has a total of " << total << " resources." << endl << endl;
	}

	//Displaying number of the market (actual & future)
	for (int j = 0; j < 8; j++) {
		if (j < 4) {
			cout << "Powerplant number " << powerplants->getPlantNumber(j) << " is currently in Actual Market." << endl;
			output << "Powerplant number " << powerplants->getPlantNumber(j) << " is currently in Actual Market." << endl;
		}

		//Future Market
		else if (j >= 4) {
			cout << "Powerplant number " << powerplants->getPlantNumber(j) << " is currently in Future Market." << endl;
			output << "Powerplant number " << powerplants->getPlantNumber(j) << " is currently in Future Market." << endl;
		}

	}
	cout << endl;
	output << endl;

	//Displaying remaining resources in market
	cout<< "Remaining Coal in Market: " << market->getTotal("Coal") << endl
		<< "Remaining Oil in Market: " << market->getTotal("Oil") << endl
		<< "Remaining Garbage in Market: " << market->getTotal("Garbage") << endl
		<< "Remaining Uranium in Market: " << market->getTotal("Uranium") << endl;

	output << "Remaining Coal in Market: " << market->getTotal("Coal") << endl
		<< "Remaining Oil in Market: " << market->getTotal("Oil") << endl
		<< "Remaining Garbage in Market: " << market->getTotal("Garbage") << endl
		<< "Remaining Uranium in Market: " << market->getTotal("Uranium") << endl;

	cout << endl;
	output << endl;

}


