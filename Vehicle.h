#include "includes.h"


class Vehicle
{
private:
	string owner;
	string type;
	string brand;
	string license_plate;

public:
	Vehicle();
	~Vehicle();

	void setOwner(string o);
	void setType(string t);
	void setBrand(string b);
	void setLicensePlate(string l_p);

	string getOwner() const;
	string getType() const;
	string getBrand() const;
	string getLicensePlate() const;
};
