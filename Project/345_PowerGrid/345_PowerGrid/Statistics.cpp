#include "Statistics.h"

//Constructor attaching this observer onto subject
Statistics::Statistics(Board * board) {
	subject = board;
	subject->attach(this);
	type = "----------- Displaying Basic";
}

//Default Constructor
Statistics::Statistics() {
	type = "----------- Displaying Basic";
}

//Destructor freeing heap storage
Statistics::~Statistics() {
	delete subject;
}

string Statistics::getType() {
	
	return type;
}

void Statistics::setType(string type) {
	this->type = type;
}