#include "Trip.h"

Trip::Trip()
{
	distance=0;
	available_seats=0;
	smoking_allowed=false;
	start=Date();
	end=Date();
}

Trip::Trip(unsigned int a_s, float d, string f_p, string t_p, bool smoke, Date s, Date e)
{
	available_seats=a_s;
	distance=d;
	from_point=f_p;
	to_point=t_p;
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

void Trip::setFromPoint(string f_p)
{
	from_point=f_p;
}

void Trip::setToPoint(string t_p)
{
	to_point=t_p;
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

string Trip::getFromPoint() const
{
	return from_point;
}

string Trip::getToPoint() const
{
	return to_point;
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

