#pragma once
#include "Observer.h"
#include "Board.h"

//Abstract Component Class
class Statistics : public Observer {

public:
	Statistics(Board * board);
	Statistics();
	virtual ~Statistics();

	virtual void printStatistics() = 0; 
	virtual string getType();
	virtual void setType(string type);

public:
	string type; //Type is the statistics criteria
	Board * subject;

};