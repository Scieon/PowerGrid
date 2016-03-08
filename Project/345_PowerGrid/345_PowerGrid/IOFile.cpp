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

void IOFile::savePlayer(Player &player1, Player &player2) {
	ofstream output;
	// Create/open a file
	output.open("player.txt");

	vector<House> vec_house1 = player1.getHouseManager()->getHouseVector();
	vector<Powerplant> vec_pp1 = *player1.getPowerplantsVector();
	
	cout << "Saving Player 1" <<endl;
	output << "Player1" << endl;
	output << "Elektro=" << player1.getElektro() << endl;
	output << "Color=" << player1.getColor() << endl;
	output << "Coal=" << player1.getResource("Coal") << endl;
	output << "Oil=" << player1.getResource("Oil") << endl;
	output << "Garbage=" << player1.getResource("Garbage") << endl;
	output << "Uranium=" << player1.getResource("Uranium") << endl;

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

	cout << "Player 1 saved" << endl;


	//////////Player 2//////////

	vector<House> vec_house2 = player2.getHouseManager()->getHouseVector();
	vector<Powerplant> vec_pp2 = *player2.getPowerplantsVector();

	cout << "Saving Player 2" << endl;
	output << "Player2" << endl;
	output << "Elektro=" << player2.getElektro() << endl;
	output << "Color=" << player2.getColor() << endl;
	output << "Coal=" << player2.getResource("Coal") << endl;
	output << "Oil=" << player2.getResource("Oil") << endl;
	output << "Garbage=" << player2.getResource("Garbage") << endl;
	output << "Uranium=" << player2.getResource("Uranium") << endl;

	output << "Player_Houses:" << endl;
	for (House house : vec_house2) {
		output << house.getIndex() << "," << house.getLocation() << endl;
	}
	output << "End_Player_Houses" << endl;

	output << "Player_Powerplants" << endl;
	for (Powerplant pp : vec_pp2) {
		output << "Bid=" << pp.getBid() <<
			" Type=" << pp.getType() <<
			" Resource_required=" << pp.getResourceReq() <<
			" Cities_powered=" << pp.getCitiesPowered() <<
			endl;
	}
	output << "End_Player_Powerplants" << endl;

	cout << "Player 2 saved" << endl;
	
	output.close();
}

void IOFile::loadPlayer(Player &player1, Player &player2) {
	
	ifstream input("player.txt");


	string line;
	int pos;

	
	input >> line; //Player1
	

	input >> line;
	pos = line.find("=");
	player1.setElektro(stoi(line.substr(pos+1))); //elektro
	
	input >> line;
	pos = line.find("=");
	player1.setColor(line.substr(pos + 1)); //Color

	input >> line;
	pos = line.find("=");
	player1.addResource("Coal",stoi(line.substr(pos + 1))); //coal

	input >> line;
	pos = line.find("=");
	player1.addResource("Oil",stoi(line.substr(pos + 1))); //oil

	input >> line;
	pos = line.find("=");
	player1.addResource("Garbage",stoi(line.substr(pos + 1))); //garbage

	input >> line;
	pos = line.find("=");
	player1.addResource("Uranium",stoi(line.substr(pos + 1))); //uranium

	input >> line; //Player_Houses:

	input >> line;

	while (line != "End_Player_Houses") {
		
		pos = line.find(",");
		int index = stoi(line.substr(0, pos)); //get index
		string location = line.substr(pos + 1); //get location

		House * house = new House(index, location);
		player1.getHouseManager()->addHouses(*house);
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
		
		player1.addPlant(new Powerplant(min_bid, type, resource_required, city_powered));

		input >> line;
	}

	input >> line; //Player2

	input >> line;
	pos = line.find("=");
	player2.setElektro(stoi(line.substr(pos + 1))); //elektro

	input >> line;
	pos = line.find("=");
	player2.setColor(line.substr(pos + 1)); //Color

	input >> line;
	pos = line.find("=");
	player2.addResource("Coal", stoi(line.substr(pos + 1))); //coal

	input >> line;
	pos = line.find("=");
	player2.addResource("Oil", stoi(line.substr(pos + 1))); //oil

	input >> line;
	pos = line.find("=");
	player2.addResource("Garbage", stoi(line.substr(pos + 1))); //garbage

	input >> line;
	pos = line.find("=");
	player2.addResource("Uranium", stoi(line.substr(pos + 1))); //uranium

	input >> line; //Player_Houses:

	input >> line;

	while (line != "End_Player_Houses") {

		pos = line.find(",");
		int index = stoi(line.substr(0, pos)); //get index
		string location = line.substr(pos + 1); //get location

		House * house = new House(index, location);
		player2.getHouseManager()->addHouses(*house);
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

		player2.addPlant(new Powerplant(min_bid, type, resource_required, city_powered));

		input >> line;
	}
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