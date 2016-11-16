#pragma once
#include "includes.h"

class Person
{
private:
	string name;
	unsigned long telephone_nr;

public:
	Person();
	Person(string n, unsigned long t_nr);
	~Person();

	//setters
	void setName(string n);
	void setTelNr(unsigned long t_nr);

	//getters
	string getName() const;
	unsigned long getTelNr() const;
};

class RegPerson: public Person
{
private:
	string password;
	string username;
	bool hasVehicle;
	float billing;
public:
	RegPerson();
	RegPerson(string n, unsigned long t_nr, string passw, string uname, bool v, float bill);
	~RegPerson();
};
