#include "Trip.h"

Trip::Trip()
{
	vehicleOwner = "";
	vehicle = new Vehicle();
	distance=0;
	available_seats=0;
	smoking_allowed=false;
	start=Date();
	end=Date();
	route= vector< pair<Place*,int> >();
	travellers=vector< pair<Person*,vector<Place*> > >();
}

Trip::Trip(string VehicleOwner,Vehicle* v,bool smoke, Date s,Date e)
{
	vehicleOwner=VehicleOwner;
	vehicle = v;
	available_seats=v->getCarSeats()-1;
	smoking_allowed=smoke;
	start = s;
	end = e;
	distance=0;
	route= vector< pair<Place*,int> >();
	travellers=vector< pair<Person*,vector<Place*> > >();
}

Trip::~Trip()
{
}

//setters
void Trip::setAvailableSeats(unsigned int a_s)
{
	available_seats=a_s;
}

void Trip::setVehicle(Vehicle * v){
	vehicle=v;
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

string Trip::getDriver() const
{
	return vehicleOwner;
}

Vehicle* Trip::getVehicle() const
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

vector<pair<Place *,int> > Trip::getRoute() const
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

void Trip::addRoute(vector< pair<Place*,int> > rota)
{
	route=rota;
	setDistance(calculateDistance((*route.begin()).first,(*route.end()).first));
}

float Trip::calculateDistance(Place * begin, Place * end)
{
	  float distancex = (end->getCoords().first-begin->getCoords().first);
	  distancex*=distancex;
	  float distancey = (end->getCoords().second-begin->getCoords().second);
	  distancey*=distancey;
	  float calcdistance = sqrt(distancex - distancey);

	  return calcdistance;
}

	 /*
		Must be called if changeTravellerRoute or addTraveller or removeTraveller is called,
		goes through travellers vector and changes available
		seats for each place in route vector
	*/
	void Trip::recalculateRouteSeats()
	{

		for(signed int i=0;i<route.size();i++)
		{
			route[i].second=0;
		}
		for(signed int i=0;i<travellers.size();i++)
		{
			int beginning=findPlaceIndex(travellers[i].second[0]);
			int end=findPlaceIndex(travellers[i].second[travellers[i].second.size()-1]);
		}
	}

	int Trip::findPlaceIndex(Place * p)
	{
		for(int i=0;i<route.size();i++)
		{
			if(route[i].first==p)
				return i;
		}
		return -1;
	}

	//CRUD for travellers participating in trip
	void addTraveller(Person * t,vector<Place *>);
	void removeTraveller(Person * t,vector<Place *>);
	void updateTravellerRoute(Person *,vector<Place *>);

string Trip::toString(){
	stringstream ss;
	ss << "Driver: " << vehicleOwner  << "| Route: ";
	for(int i=0; i<route.size();i++)
	{
		if(i==route.size()-1)
			ss << route[i].first->toString();
		else ss << route[i].first->toString() << "->";
	}
	ss << "| Initial Date: " << start.str() << "| End Date: " << end.str();
	return ss.str();
}

