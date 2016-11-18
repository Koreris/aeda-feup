#include "Person.h"

Person::Person()
{
	telephone_nr=000000000;
}

Person::Person(string n, unsigned long t_nr)
{
	name=n;
	telephone_nr=t_nr;
}

//setters
void Person::setName(string n)
{
	name=n;
}

void Person::setTelNr(unsigned long t_nr)
{
	telephone_nr=t_nr;
}

//getters
string Person::getName() const
{
	return name;
}

unsigned long Person::getTelNr() const
{
	return telephone_nr;
}

//RegPerson
//setters

void RegPerson::setUsern(string usrn)
{
	username=usrn;
}

void RegPerson::setPassw(string pw)
{
	password=pw;
}

void RegPerson::setVehicle(bool b)
{
	hasVehicle=b;
}

void RegPerson::setBilling(float f)
{
	billing=f;
}

//getters

string RegPerson::getUsern() const
{
	return username;
}

string RegPerson::getPassw() const
{
	return password;
}

bool RegPerson::getHasVehicle() const
{
	return hasVehicle;
}

float RegPerson::getBilling() const
{
	return billing;
}
