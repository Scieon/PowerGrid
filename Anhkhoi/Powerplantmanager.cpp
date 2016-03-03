#include "PowerplantManager.h"

//Defautl constructor initializing all possible power plants
PowerplantManager::PowerplantManager() {


	Powerplant * coal4 = new Powerplant(4, "Coal", 2, 1);
	Powerplant * coal8 = new Powerplant(8, "Coal", 3, 2);
	Powerplant * coal10 = new Powerplant(10, "Coal", 2, 2);
	Powerplant * coal15 = new Powerplant(15, "Coal", 2, 3);
	Powerplant * coal20 = new Powerplant(20, "Coal", 3, 5);
	Powerplant * coal25 = new Powerplant(25, "Coal", 2, 5);
	Powerplant * coal31  = new Powerplant(31, "Coal", 3, 6);
	Powerplant * coal36  = new Powerplant(36, "Coal", 3, 7);
	Powerplant * coal42  = new Powerplant(42, "Coal", 2, 6);

	Powerplant * oil3  = new Powerplant(3, "Oil", 2, 1);
	Powerplant * oil7  = new Powerplant(7, "Oil", 3, 2);
	Powerplant * oil9  = new Powerplant(9, "Oil", 1, 1);
	Powerplant * oil16  = new Powerplant(16, "Oil", 2, 3);
	Powerplant * oil26  = new Powerplant(26, "Oil", 2, 5);
	Powerplant * oil32  = new Powerplant(32, "Oil", 3, 6);
	Powerplant * oil35  = new Powerplant(35, "Oil", 1, 5);
	Powerplant * oil40  = new Powerplant(40, "Oil", 2, 6);

	Powerplant * hybrid5  = new Powerplant(5, "Hybrid", 2, 1);
	Powerplant * hybrid12  = new Powerplant(12, "Hybrid", 2, 2);
	Powerplant * hybrid21  = new Powerplant(21, "Hybrid", 2, 4);
	Powerplant * hybrid29  = new Powerplant(29, "Hybrid", 1, 4);
	Powerplant * hybrid46  = new Powerplant(46, "Hybrid", 3, 7);

	Powerplant * garbage6   = new Powerplant(6, "Garbage", 1, 1);
	Powerplant * garbage14  = new Powerplant(14, "Garbage", 2, 2);
	Powerplant * garbage19  = new Powerplant(19, "Garbage", 2, 3);
	Powerplant * garbage24  = new Powerplant(24, "Garbage", 2, 4);
	Powerplant * garbage30  = new Powerplant(30, "Garbage", 3, 6);
	Powerplant * garbage38  = new Powerplant(38, "Garbage", 3, 7);

	Powerplant * uranium11  = new Powerplant(11, "Uranium", 1, 1);
	Powerplant * uranium17  = new Powerplant(17, "Uranium", 1, 2);
	Powerplant * uranium23  = new Powerplant(23, "Uranium", 1, 3);
	Powerplant * uranium28  = new Powerplant(28, "Uranium", 1, 4);
	Powerplant * uranium34  = new Powerplant(34, "Uranium", 1, 5);
	Powerplant * uranium39  = new Powerplant(39, "Uranium", 1, 6);

	Powerplant * eco13   = new Powerplant(13, "Eco", 0, 1);
	Powerplant * eco18   = new Powerplant(18, "Eco", 0, 2);
	Powerplant * eco22   = new Powerplant(22, "Eco", 0, 2);
	Powerplant * eco27   = new Powerplant(27, "Eco", 0, 3);
	Powerplant * eco33   = new Powerplant(33, "Eco", 0, 4);
	Powerplant * eco37   = new Powerplant(37, "Eco", 0, 4);
	Powerplant * eco44   = new Powerplant(44, "Eco", 0, 5);
	Powerplant * eco50   = new Powerplant(50, "Eco", 0, 6);


}

PowerplantManager::~PowerplantManager() {

}