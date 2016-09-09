#pragma once
#include <string>
using namespace std;

class Powerplant {
    
public:
    
    // constructors and destructors
    Powerplant();
    Powerplant(int min_bid, int num_citites_powered, int resources_required, int storage, string resource_type);
    ~Powerplant();
    
    // getters and setters
    int get_bid() ;
    int get_cities_powered() ;
    int get_resource_required() ;
    int get_storage() ;
    void set_bid(int bid);
    string get_type() ;
    
    // information method 
    void powerplant_info();

    
    
private:
    
    int min_bid;
    int number_cities_powered;
    int resources_required;
    int storage;
    string resource_type;

};
