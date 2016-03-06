#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Area
{
public:
	Area();
	Area(int index);
	~Area();


	string getColor();
	int getIndex();

	void setColor(string color);
	void setIndex(int index);

	bool operator<(const Area area) const;

	

private: 
	string color;
	int index;

	static const string PURPLE; // 0
	static const string BLUE; // 1
	static const string RED; // 2
	static const string YELLOW; // 3
	static const string GREEN; // 4
	static const string BROWN; // 5

	

	
};