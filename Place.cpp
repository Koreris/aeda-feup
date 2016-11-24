#include "Place.h"

/**
 * @brief Place default constructor
 */
Place::Place()
{
}

/**
 * @brief Place constructor
 * @param n name of the place
 * @param coord place's coordinates
 */
Place::Place(string n,pair<int,int> coords)
{
	name=n;
	coordinates=coords;
}

/**
 * @brief Place destructor
 */
Place::~Place()
{
}

/**
 * @brief Sets the place's name
 * @param n string with the place's name
 */
void Place::setName(string n)
{
	name=n;
}

/**
 * @brief Sets the place's coordinates
 * @param int x coordinate in x axis
 * @param int y coordinate in y axis
 */
void Place::setCoords(int x,int y)
{
	coordinates=pair<int,int>(x,y);
}

/**
 * @brief Returns the name of the place
 * @return string with the place's name
 */
string Place::getName() const
{
	return name;
}

/**
 * @brief Returns the place's coordinates
 * @return pair<int,int> with the place's coordinates
 */
pair<int,int> Place::getCoords() const
{
	return coordinates;
}

/**
 * @brief Writes all the information about a place to a string
 * @return string with the place's information
 */
string Place::toString()
{
	stringstream ss;
	ss << name <<"(" << coordinates.first << "," << coordinates.second << ")";
	return ss.str();
}
