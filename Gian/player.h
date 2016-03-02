#pragma once
#include <string>
#include "resources.h"
#include "house.h"
using namespace std;

class Player {
    
public:
  
    // getters and setters
    string get_company_name();
    string get_color();
    int get_elektro();
    int add_elektro(int k);
    void set_color(int k);
    void set_elektro(int k);
    void set_company_name(string input);
    
    // info methods
    void info_card();
    void player_info();
    
    // holder object of type house
    House holder;
    
    // default constructor/destructor
    Player();
    ~Player();
    
    // player constructor
    Player(string company_name,string color);
    
    // array of type resources
    Resources *resources[4];
    
private:
    
    static int number_of_players;
    string color;
    string company_name;
    int elektro;
    
};


    
    
    
