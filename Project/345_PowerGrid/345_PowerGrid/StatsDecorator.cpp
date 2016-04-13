#include "StatsDecorator.h"
#include <iostream>

using namespace std;

StatsDecorator::StatsDecorator() {

}


//Wrapping statisics object inside one of the decorated classes
StatsDecorator::StatsDecorator(Statistics * stats){
	
	this->decoratedStatistics = stats;

}

StatsDecorator::~StatsDecorator() {

	delete decoratedStatistics;
}
