#ifndef POWERPLANT_H
#define POWERPLANT_H
#include <string>
using std::string;

class Powerplant {

public:
	
	Powerplant();
	Powerplant(int min_bid, string resource_type, int resources_required, int num_cities_powered);
	~Powerplant();

	//Getters and Setters

	int getBid();
	void setBid(int bid);
	string getType();
	int getCitiesPowered();
	int getResourceReq();
	int getStorage();
	void showPlantInfo();
	bool operator<(const Powerplant&);

private:
	
	int min_bid = -1;
	string resource_type;

	int num_cities_powered; 
	int resources_required = 0; //Number of resources required
	int storage = 2* resources_required; //Number of resources stored in power plant.


};



#endif


