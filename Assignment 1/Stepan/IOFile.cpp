#include "IOFile.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>


using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::string;
using std::stoi;



IOFile::IOFile()
{
}


IOFile::~IOFile()
{
}

void IOFile::savePlayer(Player & player1, Player &player2) {
	ofstream output;
	// Create/open a file
	output.open("player.txt");
	
	cout << "Saving Player 1" <<endl;
	
	output << "Player1" << endl;
	output << "Name=" << player1.getName() << endl;
	output << "Electro=" << player1.getElectro() << endl;
	output << "NumberOfHouses=" << player1.getNumberOfHouses() << endl;
	output << "Color=" << player1.getColor() << endl;
	output << "Coal=" << player1.getCoal() << endl;
	output << "Oil=" << player1.getOil() << endl;
	output << "Garbage=" << player1.getGarbage() << endl;
	output << "Uranium=" << player1.getUranium() << endl;

	cout << "Player 1 saved" << endl;


	cout << "Saving Player 2" << endl;
	output << endl;
	output << "Player2" << endl;
	output << "Name=" << player2.getName() << endl;
	output << "Electro=" << player2.getElectro() << endl;
	output << "NumberOfHouses=" << player2.getNumberOfHouses() << endl;
	output << "Color=" << player2.getColor() << endl;
	output << "Coal=" << player2.getCoal() << endl;
	output << "Oil=" << player2.getOil() << endl;
	output << "Garbage=" << player2.getGarbage() << endl;
	output << "Uranium=" << player2.getUranium() << endl;

	cout << "Player 2 saved" << endl;

	output.close();
}

void IOFile::loadPlayer(Player &player1, Player &player2) {
	
	ifstream input("player.txt");


	string skip;
	int pos;

	
	input >> skip; //Player1
	
	input >> skip;
	pos = skip.find("=");
	player1.setName(skip.substr(pos+1)); //name

	input >> skip;
	pos = skip.find("=");
	player1.setElectro(stoi(skip.substr(pos+1))); //electro
	
	input >> skip;
	pos = skip.find("=");
	player1.setNumberOfHouses(stoi(skip.substr(pos + 1))); //number_of_houses

	input >> skip;
	pos = skip.find("=");
	player1.setColor(skip.substr(pos + 1)); //Color

	input >> skip;
	pos = skip.find("=");
	player1.setCoal(stoi(skip.substr(pos + 1))); //coal

	input >> skip;
	pos = skip.find("=");
	player1.setOil(stoi(skip.substr(pos + 1))); //oil

	input >> skip;
	pos = skip.find("=");
	player1.setGarbage(stoi(skip.substr(pos + 1))); //garbage

	input >> skip;
	pos = skip.find("=");
	player1.setUranium(stoi(skip.substr(pos + 1))); //uranium

	input >> skip; //Player2

	input >> skip;
	pos = skip.find("=");
	player2.setName(skip.substr(pos + 1)); //name

	input >> skip;
	pos = skip.find("=");
	player2.setElectro(stoi(skip.substr(pos + 1))); //electro

	input >> skip;
	pos = skip.find("=");
	player2.setNumberOfHouses(stoi(skip.substr(pos + 1))); //number_of_houses

	input >> skip;
	pos = skip.find("=");
	player2.setColor(skip.substr(pos + 1)); //Color

	input >> skip;
	pos = skip.find("=");
	player2.setCoal(stoi(skip.substr(pos + 1))); //coal

	input >> skip;
	pos = skip.find("=");
	player2.setOil(stoi(skip.substr(pos + 1))); //oil

	input >> skip;
	pos = skip.find("=");
	player2.setGarbage(stoi(skip.substr(pos + 1))); //garbage

	input >> skip;
	pos = skip.find("=");
	player2.setUranium(stoi(skip.substr(pos + 1))); //uranium

	input.close();
}


//saves player_houses to map.txt
void IOFile::saveMap() {
	ofstream output;
	// Create/open a file
	output.open("map.txt");
	cout << "Saving map..." << endl;
	for (unsigned int i = 0; i < Map::player_houses->size(); i++) {
		if ((*Map::player_houses)[i].size() == 0) {
			output << i << endl;
		}
		else if ((*Map::player_houses)[i].size() == 1) {
			output << i << "," << (*Map::player_houses)[i][0] << endl;
		}
		else if ((*Map::player_houses)[i].size() == 2) {
			output << i << "," << (*Map::player_houses)[i][0] << "," << (*Map::player_houses)[i][1] << endl;
		}
		else{}
	}


	cout << "Map saved..." << endl;
	output.close();
}

void IOFile::loadMap() {

	ifstream input("map.txt");

	vector<vector<string> > * loadMap = new vector<vector<string> >(42);

	string skip;
	int first, end;
	int index;

	//Fills up loadMap vector from map.txt
	while (!input.eof()) {
		
		input >> skip;
		first = skip.find_first_of(",");
		end = skip.find_last_of(",");

		//no player
		if (first == -1) {
			//comma not found, do nothing
		}

		//only 1 player in city
		else if (first == end) {
			index = stoi(skip.substr(0, first));

			(*loadMap)[index].push_back(skip.substr(first + 1));
		}
		//2 players
		else if(first != end) {
			index = stoi(skip.substr(0, first));

			(*loadMap)[index].push_back(skip.substr(first + 1, (end - first -1)));
			(*loadMap)[index].push_back(skip.substr(end + 1));
		}
	}


	//Loads file into map
	Map::loadPlayerHouses(*loadMap);

	delete loadMap;
	loadMap = NULL;

	input.close();
}