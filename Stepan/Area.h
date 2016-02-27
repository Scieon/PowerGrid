#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Area
{
public:
	Area();
	~Area();

	static bool * area_is_played;
	static bool areAdjacent(vector<int> &colors);
	
	static void setGameAreas(vector<int> &colors);

	

private: 
	static const string PURPLE; // 0
	static const string BLUE; // 1
	static const string RED; // 2
	static const string YELLOW; // 3
	static const string GREEN; // 4
	static const string BROWN; // 5

	int nb_of_players;

	
};