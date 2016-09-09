#ifndef OIL_H
#define OIL_H
#include "Resource.h"

class Oil : public Resource {
public:

	Oil();
	Oil(int quantity);
	~Oil();
	string getType() const;

private:

	string type = "Oil";

};

#endif