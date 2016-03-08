#include "CityManager.h"
#include "City.h"
#include <string>

using namespace std;


CityManager::CityManager()
{
	array_city = new City[42]();

	addIndexNameArea(0, "Seattle", 0);
	addIndexNameArea(1, "Portland", 0);
	addIndexNameArea(2, "Boise", 0);
	addIndexNameArea(3, "Billings", 0);
	addIndexNameArea(4, "Cheyenne", 0);
	addIndexNameArea(5, "Denver", 0);
	addIndexNameArea(6, "Omaha", 0);
	addIndexNameArea(7, "San_Francisco", 1);
	addIndexNameArea(8, "Salt_Lake_City", 1);
	addIndexNameArea(9, "Las_Vegas", 1);
	addIndexNameArea(10, "Los_Angeles", 1);
	addIndexNameArea(11, "San_Diego", 1);
	addIndexNameArea(12, "Phoenix", 1);
	addIndexNameArea(13, "Santa_Fe", 1);
	addIndexNameArea(14, "Kansas_City", 2);
	addIndexNameArea(15, "Oklahoma_City", 2);
	addIndexNameArea(16, "Dallas", 2);
	addIndexNameArea(17, "Houston", 2);
	addIndexNameArea(18, "Memphis", 2);
	addIndexNameArea(19, "New_Orleans", 2);
	addIndexNameArea(20, "Birmingham", 2);
	addIndexNameArea(21, "Fargo", 3);
	addIndexNameArea(22, "Duluth", 3);
	addIndexNameArea(23, "Minneapolis", 3);
	addIndexNameArea(24, "Chicago", 3);
	addIndexNameArea(25, "St._Louis", 3);
	addIndexNameArea(26, "Cincinnati", 3);
	addIndexNameArea(27, "Knoxville", 3);
	addIndexNameArea(28, "Detroit", 4);
	addIndexNameArea(29, "Buffalo", 4);
	addIndexNameArea(30, "Pittsburgh", 4);
	addIndexNameArea(31, "Boston", 4);
	addIndexNameArea(32, "New_York", 4);
	addIndexNameArea(33, "Philadelphia", 4);
	addIndexNameArea(34, "Washington D.C.", 4);
	addIndexNameArea(35, "Norfolk", 5);
	addIndexNameArea(36, "Raleigh", 5);
	addIndexNameArea(37, "Atlanta", 5);
	addIndexNameArea(38, "Savannah", 5);
	addIndexNameArea(39, "Jacksonville", 5);
	addIndexNameArea(40, "Tampa", 5);
	addIndexNameArea(41, "Miami", 5);

}


CityManager::~CityManager()
{
}


string CityManager::getName(int index) {
	return (array_city)[index].getName();
}

int CityManager::getAreaIndex(int index) {
	return (array_city)[index].getAreaIndex().getIndex();
}


//Adds Index, Name and area to "index_cityName_area"
void CityManager::addIndexNameArea(int index, string name, int area) {

	City city(index, name, area);

	array_city[index] = city;
}