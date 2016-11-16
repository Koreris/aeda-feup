#include "Trip.h"

Trip::Trip()
{
	distance=0;
	available_seats=0;
	smoking_allowed=false;
	start=Date();
	end=Date();
}

Trip::Trip(unsigned int a_s, float d, bool smoke, Date s, Date e)
{
	available_seats=a_s;
	distance=d;
	smoking_allowed=smoke;
	start = s;
	end = e;
}

Trip::~Trip()
{
}

//setters
void Trip::setAvailableSeats(unsigned int a_s)
{
	available_seats=a_s;
}

void Trip::setDistance(float d)
{
	distance=d;
}

void Trip::setSmokingSign(bool s)
{
	smoking_allowed=s;
}

void Trip::setStart(Date s)
{
	start=s;
}

void Trip::setEnd(Date e)
{
	end=e;
}

//getters
unsigned int Trip::getAvailableSeats() const
{
	return available_seats;
}

float Trip::getDistance() const
{
	return distance;
}

vector<string> Trip::getRoute() const
{
	return route;
}

vector<Person *> Trip::getTravellers() const
{
	return travellers;
}

bool Trip::getSmokingSign() const
{
	return smoking_allowed;
}

Date Trip::getStart() const
{
	return start;
}

Date Trip::getEnd() const
{
	return end;
}

