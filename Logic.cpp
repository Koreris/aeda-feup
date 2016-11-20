#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"

using namespace std;

Logic::Logic()
{}

/**
 * Returns the current date, provided by the Date class
 * @brief Returns the Library's current date and time
 * @return Date with the current date and time
 */
Date Logic::get_curDate() const
{
	return Date::curDate();
}

bool Logic::userLogin(string usr, string passw)
{
	return (usr == "test" && passw == "1234");
}

vector<Trip *> Logic::findDest(string dest)
{
	vector<Trip *> dests;
	return (dests);
	//returns true and
}

vector<Trip*>& Logic::getCurTrips ()
	{
		return cur_trips;
	}

void Logic::setCurTrips (vector<Trip*>& curTrips)
	{
		cur_trips = curTrips;
	}

vector<Place*>& Logic::getDelDestinations()
{
	return del_destinations;
}

void Logic::setDelDestinations (vector<Place*>& delDestinations)
{
	del_destinations = delDestinations;
}

vector<Person*>& Logic::getDelRegUsers ()
{
	return del_regUsers;
}

void Logic::setDelRegUsers (vector<Person*>& delRegUsers)
{
	del_regUsers = delRegUsers;
}

vector<Trip*>& Logic::getDelTrips ()
{
	return del_trips;
}

void Logic::setDelTrips (vector<Trip*>& delTrips)
{
	del_trips = delTrips;
}

vector<Place*>& Logic::getDestinations()
{
	return destinations;
}

void Logic::setDestinations (vector<Place*>& destinations)
{
	this->destinations = destinations;
}

vector<Person*>& Logic::getRegUsers ()
{
	return regUsers;
}

void Logic::setRegUsers (vector<Person*>& regUsers)
{
	this->regUsers = regUsers;
}










