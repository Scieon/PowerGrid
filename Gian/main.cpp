// Gian Matteo Colucci (27404859)
// COMP_345_A1
/** purpose: creates 2 players (p1,p2) and displays properties of p1 and p2. Creates an object of type Coal,Oil,Uranium and Garbage and displays their properties. Creates 3 demo powerplant cards and display their properties
 **/
#include "player.h"
#include "house.h"
#include "resources.h"
#include "powerplant.h"
#include <iostream>
#include <string>

int main() {
   
    Player p1 ("Richard Inc","Red");
    Player p2 ("James Company", "Blue");
    
    p1.info_card();
    p1.player_info();
   
    //changing quanity of resources for demo purposes
    p1.resources[0]->set_quantity(3);
    p1.resources[1]->set_quantity(12);
    p1.resources[2]->set_quantity(11);
    
    p1.player_info();
    
    p2.player_info();
    
    
    
    Coal c1 (1,2);
    c1.resource_info();
    
    Oil o1 (3,1);
    o1.resource_info();
    
    Uranium u1 (12, 1);
    u1.resource_info();
    
    Garbage g1 (8,1);
    g1.resource_info();
    
    Powerplant demo1(13, 1, 0, 0, "eco");
    Powerplant demo2(5, 1, 2, 4, "hybrid(oil and/or coal)");
    Powerplant demo3(3, 1, 2, 4, "oil");
    
    demo1.powerplant_info();
    demo2.powerplant_info();
    demo3.powerplant_info();
    
   
    return 0;
}