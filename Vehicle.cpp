#include "Vehicle.h"

Vehicle::Vehicle()
{
	car_seats=0;
}

{
	owner=o;
	type=t;
	brand=b;
	license_plate=l_p;
	car_seats=c_s;
}

Vehicle::~Vehicle()
{
}

//setters
void Vehicle::setOwner(string o)
{
	owner=o;
}

void Vehicle::setType(string t)
{
	type=t;
}

void Vehicle::setBrand(string b)
{
	brand=b;
}

void Vehicle::setLicensePlate(string l_p)
{
	license_plate=l_p;
}

{
	car_seats=c_s;
}

//getters
string Vehicle::getOwner() const
{
	return owner;
}

string Vehicle::getType() const
{
	return type;
}

string Vehicle::getBrand() const
{
	return brand;
}

string Vehicle::getLicensePlate() const
{
	return license_plate;
}

{
	return car_seats;
}
