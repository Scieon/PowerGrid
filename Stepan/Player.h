#pragma once

//#include "Powerplant.h"
#include <string>
using std::string;

class Player
{
public:
	Player(string name,string color);
	~Player();

	//Accessor methods
	string getName();
	int getElectro();
	int getNumberOfHouses();
	string getColor();
	int getCoal();
	int getOil();
	int getGarbage();
	int getUranium();

	//Mutator methods
	void setName(string set);
	void setElectro(int set);
	void setNumberOfHouses(int set);
	void setColor(string set);
	void setCoal(int set);
	void setOil(int set);
	void setGarbage(int set);
	void setUranium(int set);
	

	//Add.remove ressources
	void addElectro(int);
	void addNumberOfHouses(int);
	void addCoal(int);
	void addOil(int);
	void addGarbage(int);
	void addUranium(int);

	void removeElectro(int);
	void removeCoal(int);
	void removeOil(int);
	void removeGarbage(int);
	void removeUranium(int);

	void print(); //prints out player info to console

private:
	string name;
	int electro;
	int nb_of_houses;
	string color;
	
	int coal;
	int oil;
	int garbage;
	int uranium;
	
};

