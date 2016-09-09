#include "Player.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;



Player::Player(string name, string color)
{	
	this->name = name;
	electro = 50;
	nb_of_houses = 0;
	this->color = color;

	coal = 0;
	oil = 0;
	garbage = 0;
	uranium = 0;
}


Player::~Player()
{
}

string Player::getColor() {
	return color;
}

string Player::getName()
{
	return name;
}

int Player::getElectro()
{
	return this->electro;
}

int Player::getNumberOfHouses()
{
	return this->nb_of_houses;
}

int Player::getCoal()
{
	return coal;
}

int Player::getOil()
{
	return oil;
}

int Player::getGarbage()
{
	return garbage;
}

int Player::getUranium()
{
	return uranium;
}

void Player::setName(string set)
{
	name = set;
}

void Player::setElectro(int set)
{
	electro = set;
}

void Player::setNumberOfHouses(int set)
{
	nb_of_houses = set;
}

void Player::setColor(string set)
{
	color = set;
}

void Player::setCoal(int set)
{
	coal = set;
}

void Player::setOil(int set)
{
	oil = set;
}

void Player::setGarbage(int set)
{
	garbage = set;
}

void Player::setUranium(int set)
{
	uranium = set;
}

void Player::addElectro(int add)
{
	electro += add;
}

void Player::removeElectro(int remove)
{
	electro -= remove;
}

void Player::addNumberOfHouses(int add)
{
	nb_of_houses += add;
}

void Player::addCoal(int add)
{
	coal += add;
}

void Player::addOil(int add)
{
	oil += add;
}

void Player::addGarbage(int add)
{
	garbage += add;
}

void Player::addUranium(int add)
{
	uranium += add;
}

void Player::removeCoal(int remove)
{
	coal -= remove;
}

void Player::removeOil(int remove)
{
	oil -= remove;
}

void Player::removeGarbage(int remove)
{
	garbage -= remove;
}

void Player::removeUranium(int remove)
{
	uranium -= remove;
}

void Player::print() {
	cout << "Name: " << name << endl <<
		"Electro: " << electro << endl <<
		"Nb_of_houses: " << nb_of_houses << endl <<
		"Color: " << color << endl <<
		"Coal: " << coal << endl <<
		"Oil: " << oil << endl <<
		"Garbage: " << garbage << endl <<
		"Uranium: " << uranium << endl;
}
