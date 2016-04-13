#pragma once
#include "StatsDecorator.h"

class ResourceStats : public StatsDecorator {

public:
	ResourceStats();
	~ResourceStats();
	ResourceStats(Statistics * decoratedStatistics);

	//Implementing Abstract Methods
	void update();
	void printStatistics();
};