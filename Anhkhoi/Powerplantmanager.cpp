#include "PowerplantManager.h"

//Defautl constructor initializing all possible power plants
PowerplantManager::PowerplantManager() {


	Powerplant coal4 (4, "Coal", 2, 1);
	Powerplant coal8 (8, "Coal", 3, 2);
	Powerplant coal10 (10, "Coal", 2, 2);
	Powerplant coal15 (15, "Coal", 2, 3);
	Powerplant coal20 (20, "Coal", 3, 5);
	Powerplant coal25 (25, "Coal", 2, 5);
	Powerplant coal31  (31, "Coal", 3, 6);
	Powerplant coal36  (36, "Coal", 3, 7);
	Powerplant coal42  (42, "Coal", 2, 6);

	Powerplant oil3  (3, "Oil", 2, 1);
	Powerplant oil7  (7, "Oil", 3, 2);
	Powerplant oil9  (9, "Oil", 1, 1);
	Powerplant oil16  (16, "Oil", 2, 3);
	Powerplant oil26  (26, "Oil", 2, 5);
	Powerplant oil32  (32, "Oil", 3, 6);
	Powerplant oil35  (35, "Oil", 1, 5);
	Powerplant oil40  (40, "Oil", 2, 6);

	Powerplant hybrid5  (5, "Hybrid", 2, 1);
	Powerplant hybrid12  (12, "Hybrid", 2, 2);
	Powerplant hybrid21  (21, "Hybrid", 2, 4);
	Powerplant hybrid29  (29, "Hybrid", 1, 4);
	Powerplant hybrid46  (46, "Hybrid", 3, 7);

	Powerplant garbage6   (6, "Garbage", 1, 1);
	Powerplant garbage14  (14, "Garbage", 2, 2);
	Powerplant garbage19  (19, "Garbage", 2, 3);
	Powerplant garbage24  (24, "Garbage", 2, 4);
	Powerplant garbage30  (30, "Garbage", 3, 6);
	Powerplant garbage38  (38, "Garbage", 3, 7);

	Powerplant uranium11  (11, "Uranium", 1, 1);
	Powerplant uranium17  (17, "Uranium", 1, 2);
	Powerplant uranium23  (23, "Uranium", 1, 3);
	Powerplant uranium28  (28, "Uranium", 1, 4);
	Powerplant uranium34  (34, "Uranium", 1, 5);
	Powerplant uranium39  (39, "Uranium", 1, 6);

	Powerplant eco13   (13, "Eco", 0, 1);
	Powerplant eco18   (18, "Eco", 0, 2);
	Powerplant eco22   (22, "Eco", 0, 2);
	Powerplant eco27   (27, "Eco", 0, 3);
	Powerplant eco33   (33, "Eco", 0, 4);
	Powerplant eco37   (37, "Eco", 0, 4);
	Powerplant eco44   (44, "Eco", 0, 5);
	Powerplant eco50   (50, "Eco", 0, 6);


}

PowerplantManager::~PowerplantManager() {

}