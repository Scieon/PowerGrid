#pragma once
#include "AreaManager.h"

#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

using std::string;
using std::vector;

/*
Structures used to find shorest path
*/

struct neighbor {
	int target;
	double weight;
	neighbor(int arg_target, double arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

class Map
{
public:
	Map();
	Map(AreaManager * area);
	~Map();


	std::list<int> DijkstraGetShortestPathTo(
		int vertex, 
		const std::vector<int> &previous);

	void DijkstraComputePaths(int source,
		const adjacency_list_t &adjacency_list,
		std::vector<double> &min_distance,
		std::vector<int> &previous);

	void printMap();

	bool indexInGame(int index);

	vector<int> getPlayedIndicesVector();

	vector<bool> * getAreasPlayed();

	adjacency_list_t * getMap(); //returns map

	vector<int> * getAdjacentIndices(vector<int> * houses);

private:

	//Connected graph of map
	adjacency_list_t * map;

	AreaManager *area_manager;

	//Map methods
	void addEdge(int index1, int index2, double weight);

	int getArea(int index);

};




