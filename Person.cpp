#include "Person.h"

Person::Person()
{
	telephone_nr=000000000;
}

Person::Person(string n, unsigned long int t_nr)
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
