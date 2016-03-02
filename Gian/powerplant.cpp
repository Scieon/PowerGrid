#include <iostream>
#include "powerplant.h"
using namespace std;

// constructor
Powerplant::Powerplant() {
    min_bid = 0;
    number_cities_powered = 0;
    resources_required = 0;
    storage = 2 * resources_required; //storage is always twice as much as resources_required
    resource_type = "NA";
}

// destructor
Powerplant::~Powerplant() {
    
}

// constructor with variables min_bid,number_cities_powered,resources_required,sotrage and resource_type
Powerplant::Powerplant(int min_bid, int number_cities_powered, int resources_required, int storage, string resource_type) {
    
    this->min_bid = min_bid;
    this->resource_type = resource_type;
    this->resources_required = resources_required;
    this->number_cities_powered = number_cities_powered;
    this->storage = 2 * resources_required;
}

// method that returns all information about a powerplant card
void Powerplant::powerplant_info(){
    cout << endl << "Powerplant Information" << endl;
    cout << "---------------------------" << endl;
    cout << "Minimum Bid: " << min_bid << endl;
    cout << "Number of Cities it Powers: " << number_cities_powered <<endl;
    cout << "Resources Required: " << resources_required << endl;
    cout << "Storage Capacity: " << storage << endl;
    cout << "Resource Type: " << resource_type << endl;
}

// getters and setters
int Powerplant::get_bid() {
    return min_bid;
}

void Powerplant::set_bid(int bid) {
    min_bid = bid;
}

string Powerplant::get_type() {
    return resource_type;
}

int Powerplant::get_cities_powered() {
    return number_cities_powered;
}

int Powerplant::get_resource_required() {
    return resources_required;
}

int Powerplant::get_storage() {
    return storage;
}