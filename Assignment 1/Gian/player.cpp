#include "player.h"
#include "resources.h"
#include "house.h"
#include <iostream>

// static counter for number of players
int Player::number_of_players = 0;

// add method that takes current value of elektro adds add_amount and returns total
int Player::add_elektro(int add_amount){
    elektro += add_amount;
    return elektro;
};

//getters
string Player::get_color(){
    return color;
};
string Player::get_company_name(){
    return company_name;
};

int Player::get_elektro(){
    return elektro;
};

//setters
void Player::set_color(int k){
    color = k;
};

void Player::set_elektro(int k){
    elektro = k;
};

void Player::set_company_name(string input){
    company_name = input;
};


// default Player constructor

// Player constructor
Player::Player(string company_name,string color){
    this->company_name = company_name;
    this->color = color;
    elektro = 50;
    
    holder = *new House(0,color);

    
    resources[0] = new Coal(1, 0);
    resources[1] = new Oil(3,0);
    resources[2] = new Garbage(8,0);
    resources[3] = new Uranium(12,0);
    number_of_players += 1;
};

// Player destructor
Player::~Player(){
    --number_of_players;
}

// Method couts number of players and current price of resources (based it off player 1 for now)
void Player::info_card(){
    cout <<endl << "Game Statistics " << endl
    <<  "---------------------------" << endl;
    cout << "Number of Players: " << number_of_players << endl;
    cout << "Resource Prices " << endl << "---------------------------" << endl;
    cout << "Coal: " << resources[0]->get_cost() << endl;
    cout << "Oil: "  << resources[1]->get_cost() << endl;
    cout << "Garbage: " << resources[2]->get_cost() << endl;
    cout << "Uranium: " << resources[3]->get_cost() << endl;
    cout << "---------------------------" << endl;
}

// Method that couts properties of a player
void Player::player_info(){
    cout << endl << "Player Statistics" << endl
    << "---------------------------" << endl;
    cout << "Company Name: " << company_name << endl;
    cout << "Player Color: " << color << endl;
    cout << "Amount of Elektro: " << elektro << endl;
    cout << "Number of Houses Owned: " << holder.get_houses() << endl;
   
    cout << "Quantity of Resources Owned" << endl
    << "---------------------------" << endl;
    cout << "Coal: " << resources[0]->get_quantity() << endl;
    cout << "Oil: " << resources[1]->get_quantity() << endl;
    cout << "Garbage: " << resources[2] ->get_quantity() << endl;
    cout << "Uranium: " << resources[3] ->get_quantity() << endl;
    cout << "---------------------------" << endl;
}






