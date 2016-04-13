#include "ElektrosStats.h"
#include "BasicStatistics.h"
#include <iostream>
#include <fstream>
using namespace std;

ElektrosStats::ElektrosStats() {

}

ElektrosStats::~ElektrosStats() {
	delete decoratedStatistics;
}

ElektrosStats::ElektrosStats(Statistics * decoratedStatistics) : StatsDecorator(decoratedStatistics) {
	subject = decoratedStatistics->subject;
	subject->detach(decoratedStatistics);
	subject->attach(this);

	setType(decoratedStatistics->getType() + ", Elektros"); //Setting statistics criteria
}



void ElektrosStats::update() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);

	cout << getType() << " Statistics -----------\n\n";
	this->printStatistics();


}

//This method prints out total amount of elektros a player has.
void ElektrosStats::printStatistics() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);

	vector<Player*> players = subject->vector_player;
	decoratedStatistics->printStatistics();

	for (int i = 0; i < subject->getNumberOfPlayers(); i++) {	
		cout << "Player " << players[i]->getColor() << " has " << players[i]->getElektro() << " elektros." << endl;
		output << "Player " << players[i]->getColor() << " has " << players[i]->getElektro() << " elektros." << endl;
	}
	cout << endl;
	output << endl;

}

