#include "IOFile.h"
#include "Player.h"
#include "MapOfPlayersCity.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::string;
using std::stoi;
using std::vector;


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

	vector<House> vec_house = player1.getHouseManager()->getHouseVector();

	
	cout << "Saving Player 1" <<endl;
	
	output << "Player1" << endl;
	output << "Elektro=" << player1.getElektro() << endl;
	output << "NumberOfHouses=" << player1.getHouseManager()->getHouseCount() << endl;
	output << "Color=" << player1.getColor() << endl;
	output << "Coal=" << player1.getCoal() << endl;
	output << "Oil=" << player1.getOil() << endl;
	output << "Garbage=" << player1.getGarbage() << endl;
	output << "Uranium=" << player1.getUranium() << endl;
	output << "Player_Houses:" << endl;
	for (House house : vec_house) {
		output << house.getIndex() << "," << house.getLocation() << endl;
	}



	cout << "Player 1 saved" << endl;


	cout << "Saving Player 2" << endl;
	output << endl;
	output << "Player2" << endl;
	output << "Elektro=" << player2.getElektro() << endl;
	output << "NumberOfHouses=" << player2.getHouseManager()->getHouseCount() << endl;
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
	player1.setElektro(stoi(skip.substr(pos+1))); //electro
	
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
void IOFile::saveMap(MapOfPlayersCity *map) {

	vector<vector<string> > * player_houses = map->getPlayerHousesVector();

	ofstream output;
	// Create/open a file
	output.open("map.txt");
	cout << "Saving map..." << endl;
	for (unsigned int i = 0; i < player_houses->size(); i++) {
		if ((*player_houses)[i].size() == 0) {
			output << i << endl;
		}
		else if ((*player_houses)[i].size() == 1) {
			output << i << "," << (*player_houses)[i][0] << endl;
		}
		else if ((*player_houses)[i].size() == 2) {
			output << i << "," << (*player_houses)[i][0] << "," << (*player_houses)[i][1] << endl;
		}
		else{}
	}


	cout << "Map saved..." << endl;
	output.close();
}

void IOFile::loadMap(MapOfPlayersCity *map) {

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
	map->loadPlayerHouses(*loadMap);

	delete loadMap;
	loadMap = NULL;

	input.close();
}