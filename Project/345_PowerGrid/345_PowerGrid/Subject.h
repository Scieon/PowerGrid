#pragma once
#include "Observer.h"
#include <vector>
#include <list>
#include <string>

using namespace std;

//Abstract Class
class Subject {
public:
	Subject();
	~Subject();
	virtual void attach(Observer * observer);
	virtual void detach(Observer * observer);
	virtual void notify();

protected:
	list<Observer *> * observers;


};