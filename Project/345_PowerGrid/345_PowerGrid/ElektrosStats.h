#pragma once
#include "StatsDecorator.h"

//Concrete Decorator Class
class ElektrosStats : public StatsDecorator {

public:
	ElektrosStats();
	~ElektrosStats();
	ElektrosStats(Statistics * decoratedStatistics);

	//Implementing Abstract Methods
	void update();
	void printStatistics();


};