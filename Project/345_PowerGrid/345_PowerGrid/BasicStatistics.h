#pragma once

#include "Statistics.h"
#include "Board.h"

//Concrete Component Class
class BasicStatistics : public Statistics {

public:
	BasicStatistics();
	BasicStatistics(Board * board);
	~BasicStatistics();

	//Implementing Abstract methods
	void update();
	void printStatistics();

	
};