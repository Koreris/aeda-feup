#ifndef PERSON_H_
#define PERSON_H_

#include "includes.h"

using namespace std;

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
	vector <const RegPerson*> buddies;
public:
	RegPerson();
	RegPerson(string n, unsigned long t_nr, string passw, string uname, bool v, float bill);
	~RegPerson();

	//setters
	void setPassw(string pw);
	void setUsern(string usrn);
	void setVehicle(bool b);
	void setBilling(float f);

	//getters
	string getPassw() const;
	string getUsern() const;
	bool getHasVehicle() const;
	float getBilling() const;
	vector<const RegPerson*> getBuddies() const;

	//misc
	void insertBuddy(RegPerson* other_person);
	void removeBuddy(RegPerson* other_person);
	bool areBuddies(const RegPerson* other_person) const;
};

#endif //PERSON_H_
