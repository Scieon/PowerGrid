#include <iostream>
#include <string>
#include "Resource.h";

using namespace std;

//Default constructor
Resource::Resource(){
	uranium = 0;
	oil = 0;
	garbage = 0;
	coal = 0;
}
//Constructor initializes resources 
Resource::Resource(int uranium, int oil, int garbage, int coal){
	this->uranium = uranium;
	this->oil = oil;
	this->garbage = garbage;
	this->coal = coal;
}

//Destructor
Resource::~Resource(){

}

//Mutator function for setting the amount of uranium bought by a player
void Resource::setUranium(int uranium){
	this->uranium = uranium;
}

//Mutator function for setting the amount of oil bought by a player
void Resource::setOil(int oil){
	this->oil = oil;
}

//Mutator function for setting the amount of garbage bought by a player
void Resource::setGarbage(int garbage){
	this->garbage = garbage;
}

//Mutator function for setting the amount of coal bought by a player
void Resource::setCoal(int coal){
	this->coal = coal;
}

//Accessor function to get the amount of uranium bought by a player
int Resource::getUranium(){
	return uranium;
}

//Accessor function to get the amount of garbage bought by a player
int Resource::getGarbage(){
	return garbage;
}

//Accessor function to get the amount of oil bought by a player
int Resource::getOil(){
	return oil;
}

//Accessor function to get the amount of coal bought by a player
int Resource::getCoal(){
	return coal;
}



