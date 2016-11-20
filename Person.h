#ifndef PERSON_H_
#define PERSON_H_

#include "includes.h"
#include "Vehicle.h"

using namespace std;

class Person
{
private:
	string name;
	unsigned long telephone_nr;
	float billing;

public:
	Person();
	Person(string n, unsigned long t_nr);
	virtual ~Person();

	//setters
	void setName(string n);
	void setTelNr(unsigned long t_nr);
	void setBilling(float f);

	//getters
	string getName() const;
	unsigned long getTelNr() const;
	float getBilling() const;

	//billing
	virtual void addBill(float bill,string fee, float triplength);
	void payBilling();
};

class RegPerson: public Person
{
private:
	string password;
	string username;
	vector <const RegPerson*> buddies;
	vector <Vehicle *> vehicles;
public:
	RegPerson();
	RegPerson(string n, unsigned long t_nr, string passw, string uname);
	~RegPerson();

	//setters
	void setPassw(string pw);
	void setUsern(string usrn);



	//getters
	string getPassw() const;
	string getUsern() const;
	bool getHasVehicle() const;
	vector<const RegPerson*> getBuddies() const;
	vector<Vehicle *> getVehicles() const;

	//crud
	void insertBuddy(RegPerson* other_person);
	void removeBuddy(RegPerson* other_person);
	bool areBuddies(const RegPerson* other_person) const;
	void addVehicle(Vehicle* v);
	void removeVehicle(Vehicle *v);
	void addBill(float bill,string fee, float triplength);
};

class UnregPerson: public Person
{
private:

public:
	UnregPerson();
	UnregPerson(string n, unsigned long t_nr);
	~UnregPerson();

	//crud
	void addBill(float bill, string fee, float triplength);
};

#endif //PERSON_H_
