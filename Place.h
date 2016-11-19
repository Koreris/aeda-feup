#ifndef PLACE_H_
#define PLACE_H_

#include "includes.h"

using namespace std;

class Place
{
private:
	string name;
	string coordinates;

public:
	Place();
	Place(string n, string coord);
	~Place();

	//setters
	void setName(string n);
	void setCoord(string coord);

	//getters
	string getName() const;
	string getCoordinates() const;
};

#endif //PLACE_H_
