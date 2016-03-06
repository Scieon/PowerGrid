#include "Resource.h"
#include <string>
#include <iostream>
using namespace std;

// Default Constructor
Resource::Resource(){
    color = "NA";
    type = "NA";
    shape = "NA";
    cost = 0;
    quantity = 0;
}


// getters for resources

string Resource::get_color(){
    return color;
}

string Resource::get_shape(){
    return shape;
}

string Resource::get_type(){
    return type;
}

int Resource::get_cost(){
    return cost;
}

int Resource::get_quantity(){
    return quantity;
}

// setters for class Resource
void Resource::set_color(string input){
    color = input;
}

void Resource::set_shape(string input){
    shape = input;
}

void Resource::set_type(string input){
    type = input;
}

void Resource::set_cost(int k){
    cost = k;
}

void Resource::set_quantity(int k){
    quantity = k;
}

//Resource information method that returns type,cost,color,shape
void Resource::resource_info(){
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


