#pragma once
#include "Statistics.h"


//Decorator Class
class StatsDecorator : public Statistics {

public:
	StatsDecorator();
	StatsDecorator(Statistics * decoratedStatistics);//Wrap Statistics object inside an object of one of the decorated statistic classes
	virtual ~StatsDecorator();


protected:
	Statistics * decoratedStatistics;
	
};