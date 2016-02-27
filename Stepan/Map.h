#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <tuple>

using std::string;
using std::tuple;
using std::vector;


/*
	Structures used to find shorest path
*/
typedef int vertex_t;
typedef double weight_t;

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;



/*
	Map class
*/
class Map
{
public:
	Map();
	~Map();

	//City index, cityName, Area ; Indices are found in "PowerGridUsMap_nums.jpg"
	static tuple<int, string, int> * index_cityName_area; 

	//Connected graph of map
	static adjacency_list_t * map; 

	//Player's houses location (holds names)
	static vector<vector<string> > * player_houses;

	/*
		Index_cityName_area methods
	*/
	string getName(int index);
	int getArea(int index);

	/*
		Map-graph methods
	*/
	std::list<vertex_t> DijkstraGetShortestPathTo(
		vertex_t vertex, 
		const std::vector<vertex_t> &previous);

	void DijkstraComputePaths(vertex_t source,
		const adjacency_list_t &adjacency_list,
		std::vector<weight_t> &min_distance,
		std::vector<vertex_t> &previous);

	/*
		Player houses Methods
	*/
	static void setPlayerHouse(int index, string name);
	static void loadPlayerHouses(vector<vector<string> > set);


private:

	//Index_cityName_area methods
	void addIndexNameArea(int index, string name, int area);

	//Map methods
	void addEdge(int index1, int index2, double weight);
	
};


