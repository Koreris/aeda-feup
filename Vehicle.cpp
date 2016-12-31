#include "Vehicle.h"
#include "VehicleWrapper.h"

/**
 * @brief Vehicle default constructor
 */
Vehicle::Vehicle()
{
	car_seats=0;
	year=1886;
}

/**
 * @brief Vehicle constructor
 * @param o owner's name
 * @param t vehicle's type
 * @param b vehicle's brand
 * @param m vehicle's model
 * @param y vehicle's year
 * @param b vehicle's license plate
 * @param c_s car seats of vehicle
 */
Vehicle::Vehicle(string o, string t, string b, string m, unsigned short int y, string l_p, unsigned int c_s)
{
	owner=o;
	type=t;
	brand=b;
	model=m;
	year=y;
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
 * @brief Sets the vehicle's model
 * @param t string with the vehicle's model
 */
void Vehicle::setModel(string m)
{
	model=m;
}

/**
 * @brief Sets the vehicle's year
 * @param t unsigned short int with the vehicle's year
 */
void Vehicle::setYear(unsigned short int y)
{
	year=y;
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

/**
 * @brief Returns the name of the owner
 * @return string with the owner's name
 */
string Vehicle::getOwner() const
{
	return owner;
}

/**
 * @brief Returns the type of the vehicle
 * @return string with the vehicle's type
 */
string Vehicle::getType() const
{
	return type;
}

/**
 * @brief Returns the vehicle's brand
 * @return string with the vehicle's brand
 */
string Vehicle::getBrand() const
{
	return brand;
}

/**
 * @brief Returns the vehicle's model
 * @return string with the vehicle's model
 */
string Vehicle::getModel() const
{
	return model;
}

/**
 * @brief Returns the vehicle's year
 * @return unsigned short int with the vehicle's year
 */
unsigned short int Vehicle::getYear() const
{
	return year;
}

/**
 * @brief Returns the vehicle's license plate
 * @return string with the license plate
 */
string Vehicle::getLicensePlate() const
{
	return license_plate;
}

/**
 * @brief Returns the number of car seats
 * @return unsigned int with the number of car seats
 */
unsigned int Vehicle::getCarSeats() const
{
	return car_seats;
}

/**
 * @brief Writes all the information about a vehicle to a string
 * @return string with the vehicle's information
 */
string Vehicle::toString()
{
	stringstream ss;

	ss << "Owner: " << owner << " |Type: " << type << " |Brand: " << brand << " |Model: " << model << " |Year: " << year << " |License Plate: " << license_plate << " |seats: " << car_seats;

	return ss.str();
}

bool Vehicle::operator<(const Vehicle& vc1)
	{
		if (this->getBrand() == vc1.getBrand())
		{
			if (this->getModel() == vc1.getModel())
			{
				return this->getYear() < vc1.getYear();
			}
			else
			{
				return this->getModel() == vc1.getModel();
			}
		}
		else
		{
			return this->getBrand() < vc1.getBrand();
		}
	}

bool Vehicle::operator== (const Vehicle &vc1) const
{
	return (this->owner==vc1.getOwner() &&
					this->type==vc1.getType() &&
					this->getBrand()==vc1.getBrand() &&
					this->model == vc1.getModel() &&
					this->year == vc1.getYear() &&
					this->license_plate == vc1.getLicensePlate() &&
					this->car_seats == vc1.getCarSeats());
}
