#include "Vehicle.h"

/**
 * @brief Vehicle default constructor
 */
Vehicle::Vehicle()
{
	car_seats=0;
}

/**
 * @brief Vehicle constructor
 * @param o owner's name
 * @param t vehicle's type
 * @param b vehicle's brand
 * @param b vehicle's license plate
 * @param c_s car seats of vehicle
 */
Vehicle::Vehicle(string o, string t, string b, string l_p, unsigned int c_s)
{
	owner=o;
	type=t;
	brand=b;
	license_plate=l_p;
	car_seats=c_s;
}

/**
 * @brief Vehicle default destructor
 */
Vehicle::~Vehicle()
{
}

/**
 * @brief Sets the vehicle's owner name
 * @param o string with the owner's name
 */
void Vehicle::setOwner(string o)
{
	owner=o;
}

/**
 * @brief Sets the vehicle's type
 * @param t string with the vehicle's type
 */
void Vehicle::setType(string t)
{
	type=t;
}

/**
 * @brief Sets the vehicle's brand
 * @param t string with the vehicle's brand
 */
void Vehicle::setBrand(string b)
{
	brand=b;
}

/**
 * @brief Sets the vehicle's license plate
 * @param l_p string with the vehicle's license_plate
 */
void Vehicle::setLicensePlate(string l_p)
{
	license_plate=l_p;
}

/**
 * @brief Sets the vehicle's seats.
 * @param c_s unsigned int with the vehicle's seats.
 */
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
