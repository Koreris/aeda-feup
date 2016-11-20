#include "Place.h"

Place::Place()
{
}

Place::Place(string n,pair<int,int> coords)
{
	name=n;
	coordinates=coords;
}

Place::~Place()
{
}


void Place::setName(string n)
{
	name=n;
}

string Place::getName() const
{
	return name;
}

pair<int,int> Place::getCoords() const
{
	return coordinates;
}

string Place::toString(){
	stringstream ss;
	ss << name <<"(" << coordinates.first << "," << coordinates.second << ")";
	return ss.str();
}
