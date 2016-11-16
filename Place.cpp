#include "Place.h"

Place::Place()
{
}

Place::Place(string n, string coord)
{
	name=n;
	coordinates=coord;
}

Place::~Place()
{
}

void Place::setCoord(string coord)
{
	coordinates=coord;
}

void Place::setName(string n)
{
	name=n;
}

string Place::getName() const
{
	return name;
}

string Place::getCoordinates() const
{
	return coordinates;
}
