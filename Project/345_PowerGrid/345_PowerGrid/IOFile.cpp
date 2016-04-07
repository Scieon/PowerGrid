#include "IOFile.h"
#include "Player.h"
#include "MapOfPlayersCity.h"
#include "Map.h"
#include "AreaManager.h"
#include "Area.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::string;
using std::stoi;
using std::vector;
using std::find;


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

bool IOFile::verifyMapCorrectness(MapOfPlayersCity *map)
{
	vector<int> game_indices = map->getMap()->getPlayedIndicesVector();
	vector<vector<string> > * player_houses = map->getPlayerHousesVector();

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



//saves player_houses to map.txt
void IOFile::saveMap(MapOfPlayersCity *map) {

	vector<vector<string> > * player_houses = map->getPlayerHousesVector();

	ofstream output;
	// Create/open a file
	output.open("map.txt");
	cout << "Saving map..." << endl;

	//Saves player houses
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

void IOFile::saveAreas(MapOfPlayersCity *map) {

	ofstream output;
	// Create/open a file
	output.open("area.txt");

	output << "Areas" << endl;
	//Save map areas
	vector<bool> values(*(map->getMap()->getAreasPlayed())); //shallow copy
	int i = 0;//counter
	for (bool val : values) {
		if (val) {
			output << i << endl;
		}
		i++;
	}

	output << endl;
	output.close();
}

//load areas
vector<Area> * IOFile::loadAreas()
{
	ifstream input("area.txt");;
	string line;
	input >> line; //Areas
	input >> line;

	int i1 = stoi(line); //area1
	input >> line;
	int i2 = stoi(line); //area2
	input >> line;
	int i3 =  stoi(line); //area3

	Area * a1 = new Area(i1);
	Area * a2 = new Area(i2);
	Area * a3 = new Area(i3);

	//Used for areamanager constructor
	vector<Area> * areas = new vector<Area>(); 
	areas->push_back(*a1);
	areas->push_back(*a2);
	areas->push_back(*a3);

	input.close();

	return areas;
	
}

//save powerplants
void IOFile::savePowerplants(PowerplantManager * pp_manager)
{
	ofstream output;
	// Create/open a file
	output.open("powerplant.txt");

	output << "Powerplants" << endl;
	vector<Powerplant> * ppVector = pp_manager->getPowerplantVector();

	for (Powerplant pp : *ppVector) {
		output << "Bid=" << pp.getBid() <<
			" Type=" << pp.getType() <<
			" Resource_required=" << pp.getResourceReq() <<
			" Cities_powered=" << pp.getCitiesPowered() <<
			endl;
	}
	output.close();
}

void IOFile::loadPowerplants(PowerplantManager * pp_manager)
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

	pp_manager->setPowerplantVector(pp_vector);

	input.close();
}

void IOFile::saveNbPlayerAndTurnCounter(int nb_players, int turn)
{
	ofstream output;
	// Create/open a file
	output.open("nbPlayerAndTurn.txt");

	output << "NbOfPlayers=" << nb_players << endl;
	output << "TurnCount=" << turn << endl;

	output.close();
}

void IOFile::loadNbPlayersAndTurnCoutner(int & nb_players, int & turn)
{
	ifstream input;
	// Create/open a file
	input.open("nbPlayerAndTurn.txt");

	string line;
	int pos; 

	input >> line; //NbOfPlayers
	pos = line.find("=");
	nb_players = stoi(line.substr(pos + 1));

	input >> line;

	pos = line.find("="); //TurnCount
	turn = stoi(line.substr(pos + 1));

	input.close();
}
