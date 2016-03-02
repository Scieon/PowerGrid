#pragma once
#include <string>
using namespace std;

class House {
    
public:
    
    // getters and setters
    int get_houses();
    void set_houses(int k);
    void set_color(string input);
    int add_house(int k);
    string get_color();
    
    // default constructor + constructor
    House(int houses,string color);
    House();

    
private:
    
    int number_of_houses;
    string house_color;
};
