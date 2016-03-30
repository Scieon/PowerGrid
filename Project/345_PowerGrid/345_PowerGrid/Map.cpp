#include "Map.h"
#include "Area.h"
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
#include <tuple>

using std::get;

typedef std::vector<std::vector<neighbor> > adjacency_list_t;
const double max_weight = std::numeric_limits<double>::infinity();

//HardCoded values of Map
Map::Map() {

}

Map::Map(AreaManager *area)
{

	area_manager = area;
	//Connected graph of map
	map = new adjacency_list_t(42);

	
	addEdge(0, 1, 3);
	addEdge(0, 2, 12);
	addEdge(0, 3, 9);
	addEdge(1, 2, 13);
	addEdge(1, 7, 24);
	addEdge(2, 7, 23);
	addEdge(2, 8, 8);
	addEdge(2, 4, 24);
	addEdge(2, 3, 12);
	addEdge(3, 4, 9);
	addEdge(3, 21, 17);
	addEdge(3, 23, 18);
	addEdge(4, 5, 0);
	addEdge(4, 6, 14);
	addEdge(4, 23, 18);
	addEdge(6, 23, 8);
	addEdge(6, 14, 5);
	addEdge(6, 24, 13);
	addEdge(5, 8, 21);
	addEdge(5, 14, 16);
	addEdge(5, 13, 13);
	addEdge(7, 8, 27);
	addEdge(7, 9, 14);
	addEdge(7, 10, 9);
	addEdge(8, 9, 18);
	addEdge(8, 13, 28);
	addEdge(9, 10, 9);
	addEdge(9, 11, 9);
	addEdge(9, 12, 15);
	addEdge(9, 13, 27);
	addEdge(10, 11, 3);
	addEdge(11, 12, 14);
	addEdge(12, 13, 18);
	addEdge(13, 14, 16);
	addEdge(13, 15, 15);
	addEdge(13, 16, 16);
	addEdge(13, 17, 21);
	addEdge(14, 15, 8);
	addEdge(14, 18, 12);
	addEdge(14, 25, 6);
	addEdge(14, 24, 8);
	addEdge(15, 16, 3);
	addEdge(15, 18, 14);
	addEdge(16, 17, 5);
	addEdge(16, 19, 12);
	addEdge(16, 18, 12);
	addEdge(17, 19, 8);
	addEdge(18, 25, 7);
	addEdge(18, 20, 6);
	addEdge(18, 19, 7);
	addEdge(19, 20, 11);
	addEdge(19, 39, 16);
	addEdge(20, 37, 3);
	addEdge(20, 39, 9);
	addEdge(21, 22, 6);
	addEdge(21, 23, 6);
	addEdge(22, 23, 5);
	addEdge(22, 24, 12);
	addEdge(22, 28, 15);
	addEdge(23, 24, 8);
	addEdge(24, 25, 10);
	addEdge(24, 26, 7);
	addEdge(24, 28, 7);
	addEdge(25, 26, 12);
	addEdge(25, 37, 12);
	addEdge(26, 27, 6);
	addEdge(26, 36, 15);
	addEdge(26, 30, 7);
	addEdge(26, 28, 4);
	addEdge(27, 37, 5);
	addEdge(28, 29, 7);
	addEdge(28, 30, 6);
	addEdge(29, 30, 7);
	addEdge(29, 32, 8);
	addEdge(30, 34, 6);
	addEdge(30, 36, 7);
	addEdge(31, 32, 3);
	addEdge(32, 33, 0);
	addEdge(33, 34, 3);
	addEdge(34, 35, 5);
	addEdge(35, 36, 3);
	addEdge(36, 37, 7);
	addEdge(36, 38, 7);
	addEdge(37, 38, 7);
	addEdge(38, 39, 0);
	addEdge(39, 40, 4);
	addEdge(40, 41, 4);
	
}


Map::~Map()
{

}


// USA Map Initialization of areas played; see "PowerGridUsMap_nums.jpg"
void Map::addEdge(int vertex1, int vertex2, double weight) {

	int area1 = getArea(vertex1);
	int area2 = getArea(vertex2);

	vector<bool> * area_is_played = area_manager->getAreaPlayed();

	if ((*area_is_played)[area1] 
		&& (*area_is_played)[area2]) {
		(*map)[vertex1].push_back(neighbor(vertex2, weight));
		(*map)[vertex2].push_back(neighbor(vertex1, weight));
	}
	else {
		//don't add vertices
	}
	
}

//returns area
int Map::getArea(int index)
{
	//check vertex1 area
	if (index < 7) {
		return 0;
	}
	else if (index < 14) {
		return 1;
	}
	else if (index < 21) {
		return 2;
	}
	else if (index < 28) {
		return 3;
	}
	else if (index < 35) {
		return 4;
	}
	return 5;

}





//Shortest length from source to all other vertices
//Output in vector min_distance
void Map::DijkstraComputePaths(int source,
	const adjacency_list_t &adjacency_list,
	std::vector<double> &min_distance,
	std::vector<int> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<double, int> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		double dist = vertex_queue.begin()->first;
		int u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
		neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			int v = neighbor_iter->target;
			double weight = neighbor_iter->weight;
			double distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));

			}

		}
	}
}

//Shortest path (s->v2->v3->...->d) from source vertex to destination
//Retruns path as a list of indices of vertices
std::list<int> Map::DijkstraGetShortestPathTo(
	int vertex, const std::vector<int> &previous)
{
	std::list<int> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}

//prints map
void Map::printMap()
{
	int i = 0;
	for (vector<neighbor> city : *map) {
		if (city.size() != 0) {
			cout << "Index: " << i <<  endl;
		}
		i++;
	}
}

//checks if the size of the vertex is zero to see 
bool Map::indexInGame(int index)
{
	return ((*map)[index].size() != 0);
}

//returns the indices played in the game
vector<int> Map::getPlayedIndicesVector()
{
	vector<int> indices = vector<int>();

	int i = 0;
	for (vector<neighbor> city : *map) {
		if (city.size() != 0) {
			indices.push_back(i);
		}
		i++;
	}

	return indices;
}

//returns an the area_manager
vector<bool> * Map::getAreasPlayed()
{
	return area_manager->getAreaPlayed();
}

//returns the adjacency list (the hard-coded map)
adjacency_list_t * Map::getMap() {
	return map;
}


/*
	Returns the adjacent indices to the houses owned
	Does not include the index of the houses the player already owns
*/
vector<int>* Map::getAdjacentIndices(vector<int>* houses)
{
	vector<int> * adjacentIndices = new vector<int>();

	for (int houseIndex : *houses) {
		for (neighbor adjacents : (*map)[houseIndex]) {
			std::vector<int>::iterator position = std::find(adjacentIndices->begin(), adjacentIndices->end(), adjacents.target);
			//If the adjacentIndicies vector does not contain the city index, then add it
			if (position == adjacentIndices->end())
			{
				// Element not in vector
				adjacentIndices->push_back(adjacents.target);
			}
		}
	}
	
	//remove indices of the houses the player already owns
	for (int houseIndex : *houses) {
		
		std::vector<int>::iterator position = std::find(adjacentIndices->begin(), adjacentIndices->end(), houseIndex);
		//If the adjacentIndicies vector contains the house, then remove it
		if (position != adjacentIndices->end())
		{
			// Element in vector.
			adjacentIndices->erase(position);
		}

	}

	return adjacentIndices;
}
