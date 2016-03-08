#pragma once
#include "AreaManager.h"
#include "CityManager.h"

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
typedef int vertex_t;
typedef double weight_t;

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

class Map
{
public:
	Map();
	Map(AreaManager * area, CityManager * city);
	~Map();


	std::list<vertex_t> DijkstraGetShortestPathTo(
		vertex_t vertex, 
		const std::vector<vertex_t> &previous);

	void DijkstraComputePaths(vertex_t source,
		const adjacency_list_t &adjacency_list,
		std::vector<weight_t> &min_distance,
		std::vector<vertex_t> &previous);

	void printMap();

	bool isIndexInGame(int index);

	vector<int>* getPlayedIndicesVector();

private:

	//Connected graph of map
	adjacency_list_t * map;

	AreaManager *area_manager;
	CityManager *city_manager;

	//Map methods
	void addEdge(int index1, int index2, double weight);

};




