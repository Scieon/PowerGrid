#include "ResourceStats.h"
#include "BasicStatistics.h"
#include <iostream>
#include <fstream>
using namespace std;

ResourceStats::ResourceStats() {

}

ResourceStats::~ResourceStats() {
	delete decoratedStatistics;
}
ResourceStats::ResourceStats(Statistics * decoratedStats) : StatsDecorator(decoratedStats) {
	subject = decoratedStats->subject;
	subject->detach(decoratedStats);
	subject->attach(this);

	setType(decoratedStatistics->getType() + ", Resource"); //Setting statistics criteria
}

void ResourceStats::update() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);

	cout << getType() << " Statistics -----------\n\n";
	this->printStatistics();
}

void ResourceStats::printStatistics() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);

	ResourceMarket * market = subject->market;
	vector<Player*> players = subject->vector_player;

	decoratedStatistics->printStatistics();

	for (int i = 0; i < subject->getNumberOfPlayers(); i++) {
		cout << "Player " << players[i]->getColor() <<" has " << players[i]->getResource("Coal")*100  / market->getTotal("Coal") << "% of total Coal avalailable." << endl;
		cout << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Oil")*100 / market->getTotal("Oil") << "% of total Oil available." << endl;
		cout << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Garbage")*100 / market->getTotal("Garbage") << "% of total Garbage available." << endl;
		cout << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Uranium")*100 / market->getTotal("Uranium") << "% of total Uranium available." << endl;
		cout << endl;

		output << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Coal") * 100 / market->getTotal("Coal") << "% of total Coal avalailable." << endl;
		output << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Oil") * 100 / market->getTotal("Oil") << "% of total Oil available." << endl;
		output << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Garbage") * 100 / market->getTotal("Garbage") << "% of total Garbage available." << endl;
		output << "Player " << players[i]->getColor() << " has " << players[i]->getResource("Uranium") * 100 / market->getTotal("Uranium") << "% of total Uranium available." << endl;
		output << endl;
	}


	cout << endl;
	output << endl;
}