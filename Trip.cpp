#include "Trip.h"

Trip::Trip()
{
	distance=0;
	available_seats=0;
	smoking_allowed=false;
	start=Date();
	end=Date();
	route= vector<pair<Place*,int>>();
	travellers=vector<pair<Person*,vector<Place*>>>();
}

{
	vehicleOwner=VehicleOwner;
	vehicle = v;
	smoking_allowed=smoke;
	start = s;
	end = e;
	distance=0;
	route= vector<pair<Place*,int>>();
	travellers=vector<pair<Person*,vector<Place*>>>();
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
	start=e;
}

//getters

{
	return vehicleOwner;
}

{
	return vehicle;
}

unsigned int Trip::getAvailableSeats() const
{
	return available_seats;
}

float Trip::getDistance() const
{
	return distance;
}

vector<pair<Place *,int>> Trip::getRoute() const
{
	return route;
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

stringstream Trip::toString(){
	stringstream ss {};
	for(int i=0; i<route.size();i++)
	{
		if(i==route.size()-1)
			ss << route[i].first->toString();
		else ss << route[i].first->toString() << "->";
	}
	ss << "| Initial Date: " << start.str() << "| End Date: " << end.str();
	return ss;
}

