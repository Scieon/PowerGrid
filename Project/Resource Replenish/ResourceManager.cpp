#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	
	coal = new Coal();
	oil = new Oil();
	garbage = new Garbage();
	uranium = new Uranium();

}

void ResourceManager::edit(string type, int quantity, int cost) {

	if (type == "Coal") {
		coal->setCost(cost);
		coal->setQuantity(quantity);
	}

	if (type == "Oil") {
		oil->setCost(cost);
		oil->setQuantity(quantity);
	}

	if (type == "Garbage") {
		garbage->setCost(cost);
		garbage->setQuantity(quantity);
	}

	if (type == "Uranium") {
		uranium->setCost(cost);
		uranium->setQuantity(quantity);
	}

}

void ResourceManager::initialize(string type, int cost) {
	if (type == "Coal")
		;
}

int ResourceManager::getResourceQuantity(string resource) {
	if (resource == "Coal") {
		return coal->getQuantity();
	}

	if (resource == "Oil") {
		return oil->getQuantity();
	}

	if (resource == "Garbage") {
		return garbage->getQuantity();
	}

	if (resource == "Uranium") {
		return uranium->getQuantity();
	}

	else return -1;
}

int ResourceManager::getResourceCost(string resource) {

	if (resource == "Coal") {
		return coal->getCost();
	}

	if (resource == "Oil") {
		return oil->getCost();
	}

	if (resource == "Garbage") {
		return garbage->getCost();
	}

	if (resource == "Uranium") {
		return uranium->getCost();
	}

	else return -1;

}

ResourceManager::~ResourceManager() {
	delete coal;
	delete oil;
	delete garbage;
	delete uranium;
}