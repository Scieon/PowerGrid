#pragma once
#include <string>
using namespace std;

class Resources {
    
public :
    
    // getters and setters *set to virtual for better performance on inheritence*
    virtual string get_color();
    virtual string get_type();
    virtual string get_shape();
    virtual int get_cost();
    virtual int get_quantity();
    
    virtual void set_type(string input);
    virtual void set_shape(string input);
    virtual void set_color(string input);
    virtual void set_cost(int k);
    virtual void set_quantity(int k);
    virtual void resource_info();
    Resources();
  
protected :
    
    string type;
    string shape;
    string color;
    int cost;
    int quantity;
};

class Coal : public Resources{
    
public:
    
    Coal(int cost,int quantity);
  
};

class Oil : public Resources{
    
public:
    
    Oil(int cost,int quantity);
    
};

class Garbage : public Resources{
    
public:
    
   Garbage(int cost,int quantity);

  
};

class Uranium : public Resources{
    
public:
    
    Uranium(int cost,int quantity);
 
};



