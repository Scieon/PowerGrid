#include "Subject.h"

Subject::Subject() {
	observers = new list<Observer *>;
}

Subject::~Subject() {
	list<Observer *>::iterator i = observers->begin();

	//Delete all observers in list
	for (; i != observers->end(); ++i) {
		delete * i;
	}
	delete observers; //Deleting the list
}

void Subject::attach(Observer * observer) {
	observers->push_back(observer);
}

void Subject::detach(Observer * observer) {
	observers->remove(observer);
}

void Subject::notify() {
	list<Observer *>::iterator i = observers->begin();

	for (; i != observers->end(); ++i) {
		(*i)->update(); //TODO
		system("pause");
	}
}

