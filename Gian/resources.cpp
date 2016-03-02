#include "resources.h"
#include <string>
#include <iostream>
using namespace std;

// Default Constructor
Resources::Resources(){
    color = "NA";
    type = "NA";
    shape = "NA";
    cost = 0;
    quantity = 0;
}


// getters for resources

string Resources::get_color(){
    return color;
}

string Resources::get_shape(){
    return shape;
}

string Resources::get_type(){
    return type;
}

int Resources::get_cost(){
    return cost;
}

int Resources::get_quantity(){
    return quantity;
}

// setters for class Resources
void Resources::set_color(string input){
    color = input;
}

void Resources::set_shape(string input){
    shape = input;
}

void Resources::set_type(string input){
    type = input;
}

void Resources::set_cost(int k){
    cost = k;
}

void Resources::set_quantity(int k){
    quantity = k;
}

//Resource information method that returns type,cost,color,shape
void Resources::resource_info(){
    cout << endl << "Resource Characteristics" << endl
    << "---------------------------" << endl;
    cout << "Type: " << type << endl;
    cout << "Color: " << color << endl;
    cout << "Shape: " << shape << endl;
    cout << "Cost: " << cost << endl;
    cout << "---------------------------" << endl;
}

// Coal constructor
Coal::Coal(int cost,int quantity){
    color = "Brown";
    type = "Coal";
    shape = "Cube";
    this->cost = cost;
    this->quantity = quantity;
}

// Oil constructor
Oil::Oil(int cost,int quantity){
    color = "Black";
    type = "Oil";
    shape = "Cylinder";
    this->cost = cost;
    this->quantity = quantity;
}

// Garbage constructor
Garbage::Garbage(int cost,int quantity){
    color = "Yellow";
    type = "Garbage";
    shape = "Large Octagonal";
    this->cost = cost;
    this->quantity = quantity;
}

Uranium::Uranium(int cost,int quantity){
    color = "Red";
    type = "Uranium";
    shape = "Small Octagonal";
    this->cost = cost;
    this->quantity = quantity;
}

