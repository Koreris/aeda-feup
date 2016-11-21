#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "includes.h"

using namespace std;


class Vehicle
{
private:
	string owner;
	string type;
	string brand;
	string license_plate;
	unsigned int car_seats;

public:
	Vehicle();
	Vehicle(string o, string t, string b, string l_p, unsigned int c_s);
	~Vehicle();

	void setOwner(string o);
	void setType(string t);
	void setBrand(string b);
	void setLicensePlate(string l_p);
	void setCarSeats(unsigned int c_s);

	string getOwner() const;
	string getType() const;
	string getBrand() const;
	string getLicensePlate() const;
	unsigned int getCarSeats() const;

	string toString();
};

#endif
