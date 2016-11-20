#ifndef PLACE_H_
#define PLACE_H_

#include "includes.h"

using namespace std;

class Place
{
private:
	string name;
	pair<int,int> coordinates;

public:
	Place();
	Place(string n,pair<int,int> coord);
	~Place();

	//setters
	void setName(string n);

	//getters
	string getName() const;
	pair<int,int> getCoords() const;

	stringstream toString();
};

#endif //PLACE_H_
