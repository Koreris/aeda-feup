#include "Vehicle.h"

Vehicle::Vehicle()
{
	car_seats=0;
}

Vehicle::Vehicle(string o, string t, string b, string l_p, unsigned int c_s)
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

void Vehicle::setCarSeats(unsigned int c_s)
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

unsigned int Vehicle::getCarSeats() const
{
	return car_seats;
}

string Vehicle::toString()
{
	stringstream ss;

	ss << "owner:" << owner << "|type:" << type << "|brand:" << brand << "|Plate:" << license_plate << "|seats:" << car_seats;

	return ss.str();
}
